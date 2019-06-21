#include "nk_core.h"
#include <unordered_map>
#include <fstream>

using namespace std;
using namespace segames::library;
using namespace segames::library::io;
using namespace segames::library::gl;
using namespace segames::library::gl::nk;

/*
	===============================================
	================== Global =====================
	===============================================
*/
int nk_created_fonts__ = 0; //Number of created fonts, used as handle mapping
std::unordered_map<int, NkFont*> nk_boundFonts__; //Fonts bound to a handle
int nk_created_instances__ = 0; //Number of created instances, used as handle mapping
std::unordered_map<int, NkInstanceConfig*> nk_instanceConfigs__; //Configs bound to a handle

float nk_width__(nk_handle handle, float h, const char* c, int len)
{
	return nk_boundFonts__.at(handle.id)->nkf_font_width(handle, h, c, len);
}

void nk_query_glyph__(nk_handle handle, float font_height, struct nk_user_font_glyph *glyph, nk_rune codepoint, nk_rune next_codepoint)
{
	nk_boundFonts__.at(handle.id)->nkf_glyph_query(handle, font_height, glyph, codepoint, next_codepoint);
}

void* nk_plugin_alloc__(nk_handle handle, void *old, nk_size size)
{
	if (old != NULL)
	{
		realloc(old, size);
		return old;
	}

	return malloc(size);
}

void nk_plugin_free__(nk_handle handle, void *old)
{
	free(old);
}

void nk_plugin_paste__(nk_handle handle, struct nk_text_edit* edit)
{
	nk_instanceConfigs__.at(handle.id)->paste(handle, edit);
}

void nk_plugin_copy__(nk_handle handle, const char* text, int len)
{
	nk_instanceConfigs__.at(handle.id)->copy(handle, text, len);
}

bool stbtt_font_has_my_glyph(const stbtt_fontinfo* font, int codepoint)
{
	return stbtt_FindGlyphIndex(font, codepoint) != NULL;
}

bool check_font_map_size(int border, int glyphHeight, int oversampling, size_t map_size, float font_scale, const stbtt_fontinfo* font, const ArrayList<Point>& glyphs)
{
	Point pos(0, glyphHeight);
	for (auto itr = glyphs.begin(); itr != glyphs.end(); itr++)
	{
		int size = (itr->y - itr->x);
		for (int i = 0; i < size; i++)
		{
			int glyph_unicode = itr->x + i;
			
			int advance_v, leftside_v;
			stbtt_GetCodepointHMetrics(font, glyph_unicode, &advance_v, &leftside_v);
			int width = (int)((advance_v - leftside_v) * font_scale * oversampling) + border;

			if (pos.x + width > map_size)
			{
				pos.y += glyphHeight + border;
				if (pos.y > map_size)
					return false;
				pos.x = 0;
			}
			pos.x += width;
		}

	}

	return true;
}

/*
	===============================================
	================== NkFont =====================
	===============================================
*/
float NkFont::nkf_font_width(nk_handle handle, float h, const char* c, int len) const
{
	float text_width = 0;
	nk_rune unicode;

	int glyph_len = nk_utf_decode(c, &unicode, len);
	int text_len = glyph_len;

	if (glyph_len == 0)
		return 0;

	int advance_v = 0;
	while (text_len <= len && glyph_len != 0)
	{
		if (unicode == NK_UTF_INVALID)
			break;

		stbtt_GetCodepointHMetrics(nkf_font_info, unicode, &advance_v, NULL);
		text_width += advance_v * nkf_font_scale;

		glyph_len = nk_utf_decode(c, &unicode, len - text_len);
		text_len += glyph_len;
	}

	return text_width;
}

void NkFont::nkf_glyph_query(nk_handle handle, float font_height, struct nk_user_font_glyph *glyph, nk_rune codepoint, nk_rune next_codepoint)
{
	float fntx = 0, fnty = 0;
	stbtt_aligned_quad q;
	int advance_v;

	stbtt_GetCodepointHMetrics(nkf_font_info, codepoint, &advance_v, NULL);
	glyph->xadvance = advance_v * nkf_font_scale;

	auto glyph_c = nkf_glyph_map.find(codepoint);
	if (glyph_c == nkf_glyph_map.end())
	{
		glyph->uv[0].x = 0; glyph->uv[0].y = 0;
		glyph->uv[1].x = 0; glyph->uv[1].y = 0;
		return;
	}
	stbtt_GetPackedQuad(nkf_cdata, nkf_map_size.width, nkf_map_size.height, glyph_c->second, &fntx, &fnty, &q, false);
	
	glyph->width = q.x1 - q.x0;
	glyph->height = q.y1 - q.y0;
	glyph->offset.x = q.x0;
	glyph->offset.y = q.y0 + getSize() + nkf_font_descent;

	glyph->uv[0].x = q.s0; glyph->uv[0].y = q.t0;
	glyph->uv[1].x = q.s1; glyph->uv[1].y = q.t1;
}

NkFont::NkFont(unsigned int size) : nkf_size(size)
{
	this->nkf_font_info = (stbtt_fontinfo*)malloc(sizeof(stbtt_fontinfo));
}

NkFont::~NkFont()
{
	if (nkf_ttf_data != nullptr)
		free(nkf_ttf_data);
	this->nkf_ttf_data = nullptr;
	
	if (nkf_font != nullptr)
	{
		nk_boundFonts__.erase(nkf_font->userdata.id);
		delete nkf_font;
	}
	this->nkf_font = nullptr;

	if (nkf_font_info != nullptr)
		free(nkf_font_info);
	this->nkf_font_info = nullptr;

	if (nkf_cdata != nullptr)
		free(nkf_cdata);
	this->nkf_cdata = nullptr;
}

bool NkFont::isBuilt() const
{
	return nkf_built;
}

GLuint NkFont::getTextureId() const
{
	return (GLuint)nkf_font->texture.id;
}

unsigned int NkFont::getSize() const
{
	return nkf_size;
}

unsigned char* NkFont::begin() const
{
	return nkf_ttf_data;
}

const nk_user_font* NkFont::getUserFont() const
{
	return nkf_font;
}

NkFont& NkFont::importTTF(const File& ttf)
{
	if (!ttf.exists())
		throw std::exception(("File not found: " + ttf.getPath()).c_str());

	ifstream input(ttf.getPath(), ios::binary);
	importTTF(ttf.length(), input);
	input.close();
	return (NkFont&)*this;
}

NkFont& NkFont::importTTF(size_t len, std::istream& src)
{
	if (nkf_ttf_data != nullptr)
		free(nkf_ttf_data);
	this->nkf_ttf_data = (unsigned char*)malloc(len);
	src.read((char*)nkf_ttf_data, len);
	return (NkFont&)*this;
}

NkFont& NkFont::build()
{
	return build(2, SEG_ASCII_GLYPH_RANGE);
}

NkFont& NkFont::build(const ArrayList<Point>& glyphRanges)
{
	return build(2, glyphRanges);
}

NkFont& NkFont::build(int oversample, const ArrayList<Point>& glyphRanges)
{
	int FONT_HEIGHT = getSize();
	GLuint fontTexID; 
	if (nkf_font->texture.id == NULL)
		glGenTextures(1, &fontTexID);
	else
		fontTexID = nkf_font->texture.id;

	/*
		============= Font data load =============
	*/
	stbtt_InitFont(nkf_font_info, nkf_ttf_data, 0);
	this->nkf_font_scale = stbtt_ScaleForPixelHeight(nkf_font_info, (float)FONT_HEIGHT);

	int temp_dec;
	stbtt_GetFontVMetrics(nkf_font_info, NULL, &temp_dec, NULL);
	nkf_font_descent = temp_dec * nkf_font_scale;

	/*
		============== Glyphs setup ==============
	*/
	ArrayList<Point> butcheredGlyphRanges;
	for (auto itr = glyphRanges.begin(); itr != glyphRanges.end(); itr++)
	{
		Point currentRange;
		bool state = false; //false: New range, true: Currently adding
		int size = (itr->y - itr->x);
		for (int i = 0; i <= size; i++)
		{
			int glyph_unicode = itr->x + i;
			if (stbtt_font_has_my_glyph(nkf_font_info, glyph_unicode))
			{
				if (state)
					currentRange.y = glyph_unicode + 1;
				else
				{
					currentRange.x = glyph_unicode;
					currentRange.y = glyph_unicode + 1;
					state = true;
				}

			}
			else if(state)
			{
				butcheredGlyphRanges.add(currentRange);
				currentRange.y = NULL;
				state = false;
			}

		}
		if(currentRange.y != NULL)
			butcheredGlyphRanges.add(currentRange);
	}

	/*
		============= Map & data size ============
	*/
	size_t totWidth = 0;
	int numGlyphs = 0;
	nkf_glyph_map.clear();
	for (auto itr = butcheredGlyphRanges.begin(); itr != butcheredGlyphRanges.end(); itr++)
	{
		int size = (itr->y - itr->x);
		for (int i = 0; i < size; i++)
		{
			int glyph_unicode = itr->x + i;
			nkf_glyph_map.insert(pair<int, int>(glyph_unicode, numGlyphs + i));

			int advance_v, leftside_v;
			stbtt_GetCodepointHMetrics(nkf_font_info, glyph_unicode, &advance_v, &leftside_v);
			totWidth += (size_t)((advance_v - leftside_v) * nkf_font_scale) + 1;
		}

		numGlyphs += size;
	}

	//Characters
	if (nkf_cdata != nullptr)
		free(nkf_cdata);
	this->nkf_cdata = (stbtt_packedchar*)malloc(sizeof(stbtt_packedchar) * numGlyphs);

	//Map size
	int maxHeight = getSize() * oversample;
	size_t wi = (size_t)sqrt(maxHeight * totWidth);

	if (wi % maxHeight != 0)
		wi = (size_t)(((wi / maxHeight) + 1) * maxHeight);

	while (!check_font_map_size(2, maxHeight, oversample, wi, nkf_font_scale, nkf_font_info, butcheredGlyphRanges))
		wi += maxHeight;

	nkf_map_size.width = (int)wi;
	nkf_map_size.height = (int)wi;

	/*
		=========== Font package stuff ===========
	*/
	const size_t bitmap_capacity = nkf_map_size.width * nkf_map_size.height;
	unsigned char* bitmap__ = (unsigned char*)malloc(bitmap_capacity);
	int* texture__ = (int*)malloc(bitmap_capacity * sizeof(int));

	stbtt_pack_context pc;
	stbtt_PackBegin(&pc, (unsigned char*)bitmap__, nkf_map_size.width, nkf_map_size.height, 0, 1, NULL);
	stbtt_PackSetOversampling(&pc, oversample, oversample);
	
	int writeHead = 0;
	for (auto itr = butcheredGlyphRanges.begin(); itr != butcheredGlyphRanges.end(); itr++)
	{
		int size = itr->y - itr->x;
		stbtt_PackFontRange(&pc, nkf_ttf_data, 0, (float)FONT_HEIGHT, itr->x, size, nkf_cdata + writeHead);
		writeHead += size;
	}

	stbtt_PackEnd(&pc);

	//Convert R8 to RGBA8
	int* texture_ptr = (int*)texture__;
	for (int i = 0; i < bitmap_capacity; i++, texture_ptr++)
		*texture_ptr = (bitmap__[i] << 24) | 0x00FFFFFF;

	glBindTexture(GL_TEXTURE_2D, fontTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nkf_map_size.width, nkf_map_size.height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, texture__);
	
	free(texture__);
	free(bitmap__);

	/*
		=========== Nuklear Font setup ===========
	*/
	if (nkf_font->userdata.id == 0)
	{
		(int&)(nkf_font->userdata.id) = ++nk_created_fonts__;
		nk_boundFonts__.insert(pair<int, NkFont*>(nkf_font->userdata.id, this));

		(nk_text_width_f&)(nkf_font->width) = (nk_text_width_f)nk_width__;
		(float&)nkf_font->height = (float)FONT_HEIGHT;
		(nk_query_font_glyph_f&)(nkf_font->query) = (nk_query_font_glyph_f)nk_query_glyph__;
		(int&)(nkf_font->texture.id) = (int)fontTexID;
	}

	this->nkf_built = true;
	return (NkFont&)*this;
}

/*
	===============================================
	================ NkInterface ==================
	===============================================
*/
void NkInterface::updateInternal(nk_context* ctx)
{
	if (!nki_initialized)
		this->nki_initialized = initialize(ctx);
	if(nki_initialized)
		layout(ctx);
}

/*
	===============================================
	================= NkInstance ==================
	===============================================
*/
const nk_allocator* makeAllocator()
{
	nk_allocator* all = new nk_allocator();
	all->alloc = nk_plugin_alloc__;
	all->free = nk_plugin_free__;
	return all;
}

const nk_draw_vertex_layout_element* makeLayoutElementBuffer()
{
	nk_draw_vertex_layout_element* ele = new nk_draw_vertex_layout_element[4];
	ele[0] = { NK_VERTEX_POSITION , NK_FORMAT_FLOAT , 0};
	ele[1] = { NK_VERTEX_TEXCOORD , NK_FORMAT_FLOAT , 8 };
	ele[2] = { NK_VERTEX_COLOR , NK_FORMAT_R8G8B8A8 , 16 };
	ele[3] = { NK_VERTEX_LAYOUT_END };
	return ele;
}

const Shader NkInstance::NK_STANDARD_SHADER = Shader().setData(SEG_NK_STANDARD_VERTEX_SHADER_SRC, SEG_NK_STANDARD_FRAGMENT_SHADER_SRC);
const NkFont NkInstance::NK_STANDARD_FONT = NkFont(12);
const nk_draw_null_texture* NkInstance::NK_STANDARD_DRAW_NULL_TEXTURE = new nk_draw_null_texture();
const nk_allocator* NkInstance::NK_STANDARD_ALLOCATOR = makeAllocator();
const nk_draw_vertex_layout_element* NkInstance::NK_STANDARD_VERTEX_LAYOUT = makeLayoutElementBuffer();

void NkInstance::nkSetup()
{
	if (NK_STANDARD_DRAW_NULL_TEXTURE->texture.id <= 0)
	{
		GLuint nullTexId;
		glGenTextures(1, &nullTexId);
		((int&)NK_STANDARD_DRAW_NULL_TEXTURE->texture.id) = nullTexId;
		((float&)NK_STANDARD_DRAW_NULL_TEXTURE->uv.x) = .5f;
		((float&)NK_STANDARD_DRAW_NULL_TEXTURE->uv.y) = .5f;

		glBindTexture(GL_TEXTURE_2D, NK_STANDARD_DRAW_NULL_TEXTURE->texture.id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		unsigned int data = 0xFFFFFFFF;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, &data);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	this->nki_nk_context = new nk_context();
	nk_init_default(nki_nk_context, NULL);

	if (nki_instance_config != nullptr)
	{
		nki_nk_context->clip.userdata.id = ++nk_created_instances__;
		nk_instanceConfigs__.insert(pair<int, NkInstanceConfig*>(nki_nk_context->clip.userdata.id, nki_instance_config));

		((nk_plugin_copy&)nki_nk_context->clip.copy) = nk_plugin_copy__;
		((nk_plugin_paste&)nki_nk_context->clip.paste) = nk_plugin_paste__;
	}
	
	nk_buffer_init_default(nki_nk_cmd);

	if (!NK_STANDARD_FONT.isBuilt())
		if (NK_STANDARD_FONT.begin() == nullptr)
		{
#ifdef _WIN32
			File font_f("C:/Windows/Fonts/lucon.ttf");
			if (!font_f.exists())
			{
				Array<File> listFiles = findFilesOfTypeInPath(File("C:/Windows/fonts"), ".ttf");
				font_f = listFiles[(int)(listFiles.length() * rand() / RAND_MAX)];
			}
#elif __APPLE__
			Array<File> listFiles = findFilesOfTypeInPath(File("/System/Library/Fonts/"), ".ttf");
			font_f = listFiles[(int)(listFiles.length() * rand() / RAND_MAX)];
#endif
			((NkFont&)NK_STANDARD_FONT).importTTF(font_f).build(SEG_ASCII_EXT_GLYPH_RANGE);
		}
		else
			((NkFont&)NK_STANDARD_FONT).build();
	nk_style_set_font(nki_nk_context, NK_STANDARD_FONT.getUserFont());
	
	nki_shader.bind().bindAttributes();
	glUniform1i(glGetUniformLocation(nki_shader.getId(), "texture"), 0);
	nki_shader.releaseAttributes().release();
}

NkInstance::NkInstance(NkInstanceConfig* config) : NkInstance(NK_STANDARD_SHADER, config) {}

NkInstance::NkInstance(const Shader& shader, NkInstanceConfig* config)
{
	this->nki_shader = shader;
	this->nki_instance_config = config;
}

Point& NkInstance::getMousePos() const
{
	return (Point&)nki_mouse_pos;
}

nk_context* NkInstance::getNkContext()
{
	return nki_nk_context;
}

ArrayList<NkInterface*>& NkInstance::getNkInterfaces() const
{
	return (ArrayList<NkInterface*>&)nki_interfaces;
}

NkInstance& NkInstance::setFont(const NkFont& font)
{
	nk_style_set_font(nki_nk_context, font.getUserFont());
	return (NkInstance&)*this;
}

NkInstance& NkInstance::setup()
{
	nki_vao.create();
	nki_vbo.upload(GL_STREAM_DRAW, SEG_NK_MAX_VERTEX_BUFFER, NULL);
	nki_ebo.upload(GL_STREAM_DRAW, SEG_NK_MAX_ELEMENT_BUFFER, NULL);

	if (nki_shader.getId() == NULL)
		nki_shader.upload();
	nki_shader.getAttributes().put("position", &nki_vao);
	nki_shader.getAttributes().put("tex_coord", &nki_vbo);
	nki_shader.getAttributes().put("color", &nki_ebo);

	nkSetup();
	return (NkInstance&)*this;
}

NkInstance& NkInstance::update()
{
	nk_input_end(nki_nk_context);
	for (NkInterface** ptr = nki_interfaces.begin(); ptr != nki_interfaces.end(); ptr++)
		(*ptr)->updateInternal(nki_nk_context);
	
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	nki_shader.bindAttributes().bind();
	glUniform1i(glGetUniformLocation(nki_shader.getId(), "texture"), 0);
	{
		int windowHeight = 100;
		if (nki_instance_config != nullptr)
			windowHeight = nki_instance_config->getCanvasHeight();
		
		{
			//Allocate vertex and element buffer
			glBufferData(GL_ARRAY_BUFFER, SEG_NK_MAX_VERTEX_BUFFER, NULL, GL_STREAM_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, SEG_NK_MAX_ELEMENT_BUFFER, NULL, GL_STREAM_DRAW);

			// load draw vertices & elements directly into vertex + element buffer
			void* vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			void* elements = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

			// fill convert configuration
			nk_convert_config config;
			config.vertex_layout = NK_STANDARD_VERTEX_LAYOUT;
			config.vertex_size = 20;
			config.vertex_alignment = 4;
			config.null = *NK_STANDARD_DRAW_NULL_TEXTURE;
			config.circle_segment_count = 22;
			config.curve_segment_count = 22;
			config.arc_segment_count = 22;
			config.global_alpha = 1.0f;
			config.shape_AA = NK_ANTI_ALIASING_ON;
			config.line_AA = NK_ANTI_ALIASING_ON;

			// setup buffers to load vertices and elements
			nk_buffer vbuf, ebuf;
			nk_buffer_init_fixed(&vbuf, vertices, (nk_size)SEG_NK_MAX_VERTEX_BUFFER);
			nk_buffer_init_fixed(&ebuf, elements, (nk_size)SEG_NK_MAX_ELEMENT_BUFFER);
			nk_convert(nki_nk_context, nki_nk_cmd, &vbuf, &ebuf, &config);

			glUnmapBuffer(GL_ARRAY_BUFFER);
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}

		nk_draw_index* offset = NULL;
		const nk_draw_command* cmd;
		nk_draw_foreach(cmd, nki_nk_context, nki_nk_cmd)
		{
			if (!cmd->elem_count) continue;
			
			glBindTexture(GL_TEXTURE_2D, (GLuint)cmd->texture.id);
			glScissor(
				(GLint)(cmd->clip_rect.x),
				(GLint)(windowHeight - (cmd->clip_rect.y + cmd->clip_rect.h)),
				(GLint)(cmd->clip_rect.w),
				(GLint)(cmd->clip_rect.h)
			);

			glDrawElements(GL_TRIANGLES, (GLsizei)cmd->elem_count, GL_UNSIGNED_SHORT, offset);
			offset += cmd->elem_count;
		}
		nk_clear(nki_nk_context);
	}

	nki_shader.releaseAttributes().release();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_SCISSOR_TEST);

	nk_input_begin(nki_nk_context);
	return (NkInstance&)*this;
}