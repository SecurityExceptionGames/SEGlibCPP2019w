#pragma once
#include <org/segames/library/gl/text/gl_font_alignment.h>
#include <org/segames/library/gl/text/gl_font_glyph.h>
#include <org/segames/library/gl/texture/gl_texture.h>
#include <org/segames/library/gl/gl_backed_buffer.h>
#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/util/array_list.h>
#include <org/segames/library/util/utf8_iterator.h>

#include <fstream>
#include <memory>
#include <unordered_map>

namespace org
{

	namespace segames
	{

		namespace library
		{
				
			/*
				A class describing a font for OpenGL rendering.

				* @author	Philip Rosberg
				* @since	2019-06-18
				* @edited	2019-06-18
			*/
			class SEG_API GLFont :
				public Object
			{
			private:

				/*
					Vertex pointer information.
				*/
				static GLPointerInf VERTEX_POINTER_INF;

				/*
					Texture coordinate pointer information.
				*/
				static GLPointerInf TEX_COORD_POINTER_INF;

				/*
					The default font shader.
				*/
				static GLShader DEFAULT_SHADER;
					
			protected:

				/*
					The size of the font.
				*/
				float m_height;

				/*
					The font descent.
				*/
				float m_descent;

				/*
					The atlas size.
				*/
				int m_atlasSize;

				/*
					Reference pointer to the font shader.
				*/
				const GLShader* m_shader;

				/*
					Variable keeping track of line lengths during rendering.
				*/
				ArrayList<float> m_lineLengths;

				/*
					The font geometry.
				*/
				std::unique_ptr<GLFloatBuffer> m_geometry;

				/*
					The texture with mapped glyphs.
				*/
				std::unique_ptr<GLTexture> m_atlas;

				/*
					The atlas data with the grayscale.
				*/
				std::unique_ptr<unsigned char[]> m_atlasData;

				/*
					The mapped glyphs.
				*/
				std::unordered_map<unsigned int, GLFontGlyph> m_glyphs;

				/*
					Computes the size of the atlas texture.
					* @param[in] scale The font scale from stb
					* @param[in] oversampling The oversampling
					* @param[in] info The font info
					* @param[in] chars A pointer to the first element in an array of UTF8 character code-points
					* @param[in] numChars The amount of elements the the char array
				*/
				virtual int computeAtlasSize(const float scale, const unsigned int oversampling, stbtt_fontinfo* info, const unsigned int* chars, const int numChars);

				/*
					Builds the font atlas.
					* @param[in] oversampling The oversampling
					* @param[in] info The font info
					* @param[in] ttfData The raw truetype font data
					* @param[in] chars A pointer to the first element in an array of UTF8 character code-points
					* @param[in] numChars The amount of elements the the char array
					* @param[out] packedChars An array of character information from the creation of the atlas
				*/
				virtual void buildAtlas(const unsigned int oversampling, stbtt_fontinfo* info, unsigned char* ttfData, const unsigned int* chars, const int numChars, stbtt_packedchar* packedChars);

				/*
					Retrieves various character information for the font.
					* @param[in] scale The font scale from stb
					* @param[in] info The font info
					* @param[in] chars A pointer to the first element in an array of UTF8 character code-points
					* @param[in] numChars The amount of elements the the char array
					* @param[in] packedChars An array of character information from the creation of the atlas
				*/
				virtual void computeInfo(const float scale, stbtt_fontinfo* info, const unsigned int* chars, const int numChars, stbtt_packedchar* packedChars);

				/*
					Creates the font geometry.
					* @param[in] chars A pointer to the first element in an array of UTF8 character code-points
					* @param[in] numChars The amount of elements the the char array
				*/
				virtual void createGeometry(const unsigned int* chars, const int numChars);

			public:

				/*
					Creates and imports a new font.
					* @param[in] size The size/height of a standard character
					* @param[in] oversampling How many times larger the characters should be rendered in the atlas for better quality, 1 (no extra) or 2 usually works fine
					* @param[in] path The path to the TTF file of the font
					* @param[in] shader A reference pointer to a shader that should be used for text rendering, this pointer is NOT deallocated by this instance
					* @param[in] chars An array containing UTF8 character codes to render to the atlas
					* @param[in] numChars The amount of characters in the "chars" array
				*/
				explicit GLFont(const float size, const unsigned int oversampling, const std::string& path, const GLShader* shader, const unsigned int* chars, const int numChars);

				/*
					Returns the size/height of the font.
				*/
				float getHeight() const;

				/*
					Returns the descent of the font.
				*/
				float getDescent() const;

				/*
					Returns a pointer to the internal atlas texture.
				*/
				GLTexture* getAtlas() const;

				/*
					Returns the glyph with the given UTF8 code, return GLFontGlyph::EMPTY if the glyph cannot be found.
					* @param[in] code The UTF8 code of the glyph
				*/
				const GLFontGlyph& getGlyph(const unsigned int code) const;

				/*
					Returns a reference to the map of glyphs of the font.
				*/
				const std::unordered_map<unsigned int, GLFontGlyph>& getGlyphs() const;

				/*
					Uploads the data of the font.
				*/
				virtual void upload();

			public:

				/*
					Renders the text from the given iterators with left alignment.
					* @param[in] x The x position of the text
					* @param[in] y The y position of the text
					* @param[in] beg The begining iterator
					* @param[in] end The ending iterator
				*/
				virtual void renderSimple(const float x, const float y, const UTF8Iterator& beg, const UTF8Iterator& end);
					
				/*
					Renders the text from the given iterators with adjusted (center or right) alignment.
					* @param[in] x The x position of the text
					* @param[in] y The y position of the text
					* @param[in] beg The begining iterator
					* @param[in] end The ending iterator
					* @param[in] adjustment The adjustment, line pushback factor
				*/
				virtual void renderAdjusted(const float x, const float y, const UTF8Iterator& beg, const UTF8Iterator& end, const float adjustment);

			public:

			};

		}

	}

}