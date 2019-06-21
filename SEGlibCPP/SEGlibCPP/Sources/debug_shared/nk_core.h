#pragma once
#include <dllmain.h>

#include "..\..\io\file.h"
#include "..\..\geometry.h"
#include <stb\stb_truetype.h>
#include <istream>

#include "..\gl_core.h"
#include "..\gl_buffer.h"
#include "..\gl_vertex_array.h"
#include "..\shader.h"

#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#include "nuklear\nuklear.h"

#ifndef SEG_NK_MAX_VERTEX_BUFFER
#define SEG_NK_MAX_VERTEX_BUFFER 524288
#endif

#ifndef SEG_NK_MAX_ELEMENT_BUFFER
#define SEG_NK_MAX_ELEMENT_BUFFER 131072
#endif

#ifndef SEG_NK_STANDARD_VERTEX_SHADER_SRC
#define SEG_NK_STANDARD_VERTEX_SHADER_SRC "#version 120\nattribute vec2 position;\nattribute vec2 tex_coord;\nattribute vec4 color;\nvoid main() {gl_FrontColor = color;gl_TexCoord[0].xy = tex_coord;gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 0, 1);\n}"
#endif

#ifndef SEG_NK_STANDARD_FRAGMENT_SHADER_SRC
#define SEG_NK_STANDARD_FRAGMENT_SHADER_SRC "#version 120\nuniform sampler2D texture_img;\nvoid main() {\n/*gl_FragColor = vec4(gl_TexCoord[0].xy * 10, 0, 1.0);*/gl_FragColor = gl_Color * texture2D(texture_img, gl_TexCoord[0].xy);\n}"
#endif

#ifndef SEG_ASCII_GLYPH_RANGE //Nr. 32 is space. Do not forget!
#define SEG_ASCII_GLYPH_RANGE ArrayList<Point>() << Point(32, 126)
#endif

#ifndef SEG_ASCII_EXT_GLYPH_RANGE
#define SEG_ASCII_EXT_GLYPH_RANGE ArrayList<Point>() << Point(32, 254)
#endif

#ifndef SEG_JPN_GLYPH_RANGE
#define SEG_JPN_GLYPH_RANGE ArrayList<Point>() << Point(32, 32) << Point(12353, 12432) << Point(13312, 19893) << Point(19968, 40934)
#endif

#ifndef SEG_CHN_GLYPH_RANGE
#define SEG_CHN_GLYPH_RANGE ArrayList<Point>() << Point(32, 32) << Point(13312, 19893) << Point(19968, 40934)
#endif

namespace segames
{
	namespace library
	{
		namespace gl
		{
			/*
				Namespace for nuklear gui
			*/
			namespace nk
			{
				/*
					A class for handling nuklear fonts

					@author Philip R
					@since 2017-11-26
				*/
				class SEG_API NkFont
				{
				private:
					bool nkf_built = false; //True if the font has been built
					const unsigned int nkf_size; //The font size
					const nk_user_font* nkf_font = new nk_user_font(); //The font
					unsigned char* nkf_ttf_data = nullptr; //The font ttf data

					float nkf_font_descent = 0; //The font descent
					float nkf_font_scale = 1; //The font scale
					Dimension nkf_map_size; //The font map size
					stbtt_fontinfo* nkf_font_info = nullptr; //The font info
					stbtt_packedchar* nkf_cdata = nullptr; //The font data
					std::unordered_map<int, int> nkf_glyph_map; //The glyph render mapping

				public:
					/*
						The constructor
						* @param[in] size The size of the font
					*/
					NkFont(unsigned int size);

					/*
						Destructor
					*/
					~NkFont();

					/*
						(Private) mehtod used to determine font width
					*/
					float nkf_font_width(nk_handle, float, const char*, int) const;

					/*
						(Private) method used to query glyphs or something
					*/
					void nkf_glyph_query(nk_handle, float, struct nk_user_font_glyph*, nk_rune, nk_rune);

					/*
						Returns true if the font has been built
					*/
					bool isBuilt() const;

					/*
						Returns the gl texture id
					*/
					GLuint getTextureId() const;

					/*
						Returns the font size
					*/
					unsigned int getSize() const;

					/*
						Returns the data
					*/
					unsigned char* begin() const;

					/*
						Returns the nk_user_font
					*/
					const nk_user_font* getUserFont() const;

					/*
						Imports the ttf data
						* @param[in] ttf The TTF-file
					*/
					NkFont& importTTF(const io::File& ttf);

					/*
						Imports the ttf data
						* @param[in] len The data length
						* @param[in] src The source input stream
					*/
					NkFont& importTTF(size_t len, std::istream& src);

					/*
						Builds the font, with ASCII range and over-sampling at 2
					*/
					NkFont& build();

					/*
						Builds the font with over-sampling at 2
						* @param[in] glyphRanges The glyph ranges, filled with Point(lower glyph id, higher glyph id), uses unicode
					*/
					NkFont& build(const ArrayList<Point>& glyphRanges);

					/*
						Builds the font
						* @param[in] oversample The amount of over-sampling used for the font eg. 1 is 1:1 size, larger numbers are higher resolution character rendering
						* @param[in] glyphRanges The glyph ranges, filled with Point(lower glyph id, higher glyph id), uses unicode
					*/
					NkFont& build(int oversample, const ArrayList<Point>& glyphRanges);

				};

				/*
					A class for handling an interface structure for nuklear
					
					@author Philip R
					@since 2017-11-27
				*/
				class SEG_API NkInterface
				{
				private:
					bool nki_initialized; //True if the nk interface 

				protected:
					/*
						The initialization method of the interface structure (if any needs to be done)
						Return true when finished initializing
						* @param[in] ctx The nuklear context pointer
					*/
					virtual bool initialize(nk_context* ctx) = 0;

					/*
						The update method of the interface structure, that builds the interface using nuklear methods
						* @param[in] ctx The nuklear context pointer
					*/
					virtual void layout(nk_context* ctx) = 0;

				public:
					/*
						The internal update method called from NkInstance
						* @param[in] ctx The nuklear context pointer
					*/
					void updateInternal(nk_context* ctx);

				};

				/*
					Configuration setup interface for NkInstance

					@author Philip R
					@since 2017-12-05
				*/
				class SEG_API NkInstanceConfig
				{
				public:
					/*
						Returns the ui canvas height for nuklear to use, eg. the window height for glfw
					*/
					virtual int getCanvasHeight() = 0;

					/*
						The copy callback for NkInstance
						* @param[in] handle The nuklear handle
						* @param[in] text The clipboard text
						* @param[in] len The text len
					*/
					virtual void copy(nk_handle handle, const char* text, int len) = 0;

					/*
						The paste callback for NkInstance
						* @param[in] handle The nuklear handle
						* @param[in] edit The clipboard edit, or something
					*/
					virtual void paste(nk_handle handle, struct nk_text_edit* edit) = 0;

				};

				/*
					A nuklear handler class
					
					@author Philip R
					@since 2017-11-28
				*/
				class SEG_API NkInstance
				{
				private:
					Point nki_mouse_pos; //The mouse position
					NkInstanceConfig* nki_instance_config = nullptr; //The instance configuration
					nk_context* nki_nk_context = nullptr; //The nuklear context
					nk_buffer* nki_nk_cmd = new nk_buffer(); //The nuklear what-the-fuck
					Shader nki_shader; //The nuklear shader
					GLVertexArray nki_vao = GLVertexArray(GLPointerInf(GL_FLOAT, 2, 20, 0)); //The vertex array buffer
					GLBuffer nki_vbo = GLBuffer(GLPointerInf(GL_FLOAT, 2, 20, 8)); //Vertex buffer object
					GLBuffer nki_ebo = GLBuffer(GLPointerInf(GL_TRUE, GL_UNSIGNED_BYTE, 4, 20, 16)).setBufferType(GL_ELEMENT_ARRAY_BUFFER); //Element array buffer object
					ArrayList<NkInterface*> nki_interfaces; //A list of interface structures

				protected:
					/*
						Sets up the nuklear related things
					*/
					void nkSetup();

				public:
					/*
						The standard nuklear shader
					*/
					const static Shader NK_STANDARD_SHADER;

					/*
						The standard font
					*/
					const static NkFont NK_STANDARD_FONT;

					/*
						The draw null texture
					*/
					const static nk_draw_null_texture* NK_STANDARD_DRAW_NULL_TEXTURE;

					/*
						The standard nuklear memory allocator
					*/
					const static nk_allocator* NK_STANDARD_ALLOCATOR;

					/*
						The nuklear vertex layout
					*/
					const static nk_draw_vertex_layout_element* NK_STANDARD_VERTEX_LAYOUT;

					/*
						Creates a new nuclear handler instance
						* @param[in] config This instance's configuration set
					*/
					NkInstance(NkInstanceConfig* config);

					/*
						Creates a new nuclear handler instance
						* @param[in] shader The nuklear shader
						* @param[in] config This instance's configuration set
					*/
					NkInstance(const Shader& shader, NkInstanceConfig* config);

					/*
						Returns the cursor pos storage point for this nk-istance
					*/
					Point& getMousePos() const;

					/*
						Returns the nuklear context
					*/
					nk_context* getNkContext();

					/*
						Returns the interface structures
					*/
					ArrayList<NkInterface*>& getNkInterfaces() const;

					/*
						Sets the font of the nuklear instance
						* @param[in] font The font to use
					*/
					NkInstance& setFont(const NkFont& font);

					/*
						Sets up the nuklear instance
					*/
					NkInstance& setup();

					/*
						Updates and renders the interface structures
					*/
					NkInstance& update();

				};

			}

		}

	}

}