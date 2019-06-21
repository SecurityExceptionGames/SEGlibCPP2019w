#pragma once
#include <org/segames/library/gl/text/gl_font_glyph.h>
#include <org/segames/library/gl/texture/gl_texture.h>
#include <org/segames/library/gl/gl_backed_buffer.h>
#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/util/array_list.h>

#include <fstream>
#include <memory>
#include <unordered_map>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				class SEG_API GLFont :
					public Object
				{
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
						The font shader.
					*/
					std::unique_ptr<GLShader> m_shader;

					/*
						The font geometry information.
					*/
					std::unique_ptr<GLPointerInf[]> m_geometryInf;

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

					explicit GLFont(const float size, const unsigned int oversampling, const std::string& path, const unsigned int* chars, const int numChars);

					GLTexture* getTexture();

					/*
						Uploads the data of the font.
					*/
					virtual void upload();

					virtual void render(const float x, const float y, const std::string& str);

				};

			}

		}

	}

}