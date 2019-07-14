#include <org/segames/library/gl/text/gl_font.h>
#include <org/segames/library/io/file.h>
#include <org/segames/library/math/math.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			ArrayList<unsigned int> GLFont::ASCII_CHARACTERS = GLFont::getASCIICharacters();

			ArrayList<unsigned int> GLFont::getASCIICharacters()
			{
				ArrayList<unsigned int> chars;
				for (unsigned int i = 32; i < 128; i++)
					chars.add(i);
				return chars;
			}

			GLPointerInf GLFont::VERTEX_POINTER_INF = GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 4, 0);
			GLPointerInf GLFont::TEX_COORD_POINTER_INF = GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 4, sizeof(GLfloat) * 2);
			GLShader GLFont::DEFAULT_SHADER = GLShader();

			int GLFont::computeAtlasSize(const float scale, const unsigned int oversampling, stbtt_fontinfo* info, const unsigned int* chars, const int numChars)
			{
				double totalW = 0;
				for (int i = 0; i < numChars; i++)
				{
					int advance, leftSide;
					stbtt_GetCodepointHMetrics(info, chars[i], &advance, &leftSide);
					totalW += (advance - leftSide) * scale;
				}
				double side = sqrt(totalW) * sqrt(m_height) * oversampling;
				return Math::min((int)exp2(ceil(log2(side))), GLTexture::glMaxTextureSize());
			}

			void GLFont::buildAtlas(const unsigned int oversampling, stbtt_fontinfo* info, unsigned char* ttfData, const unsigned int* chars, const int numChars, stbtt_packedchar* packedChars)
			{
				m_atlasData.reset(new unsigned char[m_atlasSize * m_atlasSize]);

				// Pack chars into atlas
				stbtt_pack_context pc;
				stbtt_PackBegin(&pc, m_atlasData.get(), m_atlasSize, m_atlasSize, 0, 1, nullptr);
				stbtt_PackSetOversampling(&pc, oversampling, oversampling);
				for (int i = 0; i < numChars; i++)
					stbtt_PackFontRange(&pc, ttfData, 0, m_height, chars[i], 1, &(packedChars[i]));
				stbtt_PackEnd(&pc);

				// Create atlas texture
				m_atlas.reset(new GLTexture(GL_R8, Dimension3i(m_atlasSize, m_atlasSize, 1)));
			}

			void GLFont::computeInfo(const float scale, stbtt_fontinfo* info, const unsigned int* chars, const int numChars, stbtt_packedchar* packedChars)
			{
				for (int i = 0; i < numChars; i++)
				{
					int advance, leftSide;
					float x, y;
					stbtt_aligned_quad quad;

					stbtt_GetPackedQuad(&packedChars[i], m_atlasSize, m_atlasSize, 0, &x, &y, &quad, false);
					stbtt_GetCodepointHMetrics(info, chars[i], &advance, &leftSide);

					m_glyphs.insert(std::pair<unsigned int, GLFontGlyph>(chars[i], GLFontGlyph(
						i,
						advance * scale,
						quad.x1 - quad.x0,
						quad.y1 - quad.y0,
						leftSide * scale,
						quad.y0 + m_height + m_descent,
						quad
					)));
				}

			}

			void GLFont::createGeometry(const unsigned int* chars, const int numChars)
			{
				m_geometry.reset(new GLFloatBuffer());
				m_geometry->setPointerBinding(GLDataType::VERTEX, VERTEX_POINTER_INF);
				m_geometry->setPointerBinding(GLDataType::TEX_COORD, TEX_COORD_POINTER_INF);

				for (int i = 0; i < numChars; i++)
				{
					GLFontGlyph& g = m_glyphs.find(chars[i])->second;
					const stbtt_aligned_quad& q = g.getQuad();

					m_geometry->push(g.getXOffset()).push(g.getYOffset());
					m_geometry->push(q.s0).push(q.t0);

					m_geometry->push(g.getWidth() + g.getXOffset()).push(g.getYOffset());
					m_geometry->push(q.s1).push(q.t0);

					m_geometry->push(g.getWidth() + g.getXOffset()).push(g.getHeight() + g.getYOffset());
					m_geometry->push(q.s1).push(q.t1);

					m_geometry->push(g.getXOffset()).push(g.getHeight() + g.getYOffset());
					m_geometry->push(q.s0).push(q.t1);
				}

			}

			GLFont::GLFont()
			{}

			GLFont::GLFont(const float size, const unsigned int oversampling, const std::string& path, const ArrayList<unsigned int>& chars) :
				GLFont(size, oversampling, path, nullptr, chars)
			{}

			GLFont::GLFont(const float size, const unsigned int oversampling, const std::string& path, const GLShader* shader, const ArrayList<unsigned int>& chars) :
				GLFont(size, oversampling, path, shader, chars.pointer(), chars.size())
			{}

			GLFont::GLFont(const float size, const unsigned int oversampling, const std::string& path, const GLShader* shader, const unsigned int* chars, const int numChars) :
				m_height(size),
				m_shader(shader ? shader : &DEFAULT_SHADER)
			{
				File file(path);
				std::ifstream input(file.openInputBin());
				std::unique_ptr<unsigned char[]> ttfData(new unsigned char[file.length()]);

				input.read(reinterpret_cast<char*>(ttfData.get()), file.length());
				input.close();

				// Initialize font
				stbtt_fontinfo info;
				stbtt_InitFont(&info, ttfData.get(), 0);
				float scale = stbtt_ScaleForPixelHeight(&info, m_height);

				int desc;
				stbtt_GetFontVMetrics(&info, nullptr, &desc, nullptr);
				m_descent = desc * scale;

				// Create atlas and character information
				std::unique_ptr<stbtt_packedchar[]> packedChars(new stbtt_packedchar[numChars]);
				m_atlasSize = computeAtlasSize(scale, oversampling, &info, chars, numChars);
				buildAtlas(oversampling, &info, ttfData.get(), chars, numChars, packedChars.get());
				computeInfo(scale, &info, chars, numChars, packedChars.get());
				createGeometry(chars, numChars);
			}

			GLFont::~GLFont()
			{}

			float GLFont::getHeight() const
			{
				return m_height;
			}

			float GLFont::getDescent() const
			{
				return m_descent;
			}

			GLTexture* GLFont::getAtlas() const
			{
				return m_atlas.get();
			}

			const GLFontGlyph& GLFont::getGlyph(const unsigned int code) const
			{
				auto itr = m_glyphs.find(code);
				if (itr == m_glyphs.end())
					return GLFontGlyph::EMPTY;
				return itr->second;
			}

			const std::unordered_map<unsigned int, GLFontGlyph>& GLFont::getGlyphs() const
			{
				return m_glyphs;
			}

			void GLFont::upload()
			{
				m_atlas->upload(GL_UNSIGNED_BYTE, m_atlasData.get());
				m_atlas->bind().setParameters(GL_REPEAT, GL_LINEAR, GL_LINEAR).release();
				m_atlasData.reset();

				m_geometry->upload(GL_STATIC_DRAW);
				m_geometry->compact();

				if (m_shader == &DEFAULT_SHADER && DEFAULT_SHADER.getID() == 0)
				{
					DEFAULT_SHADER.setVertexData("#version 120\nuniform vec2 pos;\nuniform vec4 color;\n\nvoid main() {\nvec4 vertex = gl_Vertex;\nvertex.xy += pos;\ngl_Position = gl_ModelViewProjectionMatrix * vertex;\ngl_TexCoord[0] = gl_MultiTexCoord0;\ngl_FrontColor = color;\n}");
					DEFAULT_SHADER.setFragmentData("#version 120\nuniform sampler2D atlas;\n\nvoid main() {\ngl_FragColor = vec4(gl_Color.r, gl_Color.g, gl_Color.b, gl_Color.a * texture2D(atlas, gl_TexCoord[0].xy).r);\n}");
					DEFAULT_SHADER.upload("GLFont::DEFAULT_SHADER");
				}

			}

			void GLFont::renderSimple(const float x, const float y, const UTF8Iterator& beg, const UTF8Iterator& end, const Color& color)
			{
				if (beg != end)
				{
					UTF8Iterator itr(beg);
					m_shader->bind();
					m_atlas->bind();
					m_geometry->bind().setPointerInf();

					glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);

					glUniform1i(glGetUniformLocation(m_shader->getID(), "atlas"), 0);
					glUniform4f(glGetUniformLocation(m_shader->getID(), "color"), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
					const GLint loc = glGetUniformLocation(m_shader->getID(), "pos");

					float xp = x, yp = y;
					while (itr != end)
					{
						unsigned int c = *itr;
						if (c == '\n' || c == '\r')
						{
							xp = x;
							yp += m_height;
						}
						else
						{
							auto res = m_glyphs.find(c);
							if (res != m_glyphs.end())
							{
								glUniform2f(loc, xp, yp);
								glDrawArrays(GL_QUADS, res->second.getIndex() * 4, 4);
								xp += res->second.getAdvance();
							}

						}

						++itr;
					}

					glDisableClientState(GL_VERTEX_ARRAY);
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);

					m_geometry->release();
					m_atlas->release();
					m_shader->release();
				}

			}

			void GLFont::renderAdjusted(const float x, const float y, const UTF8Iterator& beg, const UTF8Iterator& end, const Color& color, const float adjustment)
			{
				if (beg != end)
				{
					// Count line length
					UTF8Iterator counter(beg);
					m_lineLengths.clear();

					float lineLength = 0;
					while (counter != end)
					{
						unsigned int c = *counter;
						if (c == '\n' || c == '\r')
						{
							m_lineLengths.add(lineLength);
							lineLength = 0;
						}
						else
						{
							auto res = m_glyphs.find(c);
							if (res != m_glyphs.end())
								lineLength += res->second.getAdvance();
						}

						++counter;
					}
					m_lineLengths.add(lineLength);

					// Render characters
					UTF8Iterator itr(beg);
					m_shader->bind();
					m_atlas->bind();
					m_geometry->bind().setPointerInf();

					glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);

					glUniform1i(glGetUniformLocation(m_shader->getID(), "atlas"), 0);
					glUniform4f(glGetUniformLocation(m_shader->getID(), "color"), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
					const GLint loc = glGetUniformLocation(m_shader->getID(), "pos");

					int lineNr = 0;
					float xp = x - m_lineLengths.get(lineNr) * adjustment, yp = y;
					while (itr != end)
					{
						unsigned int c = *itr;
						if (c == '\n' || c == '\r')
						{
							lineNr++;
							xp = x - m_lineLengths.get(lineNr) * adjustment;
							yp += m_height;
						}
						else
						{
							auto res = m_glyphs.find(c);
							if (res != m_glyphs.end())
							{
								glUniform2f(loc, xp, yp);
								glDrawArrays(GL_QUADS, res->second.getIndex() * 4, 4);
								xp += res->second.getAdvance();
							}

						}

						++itr;
					}

					glDisableClientState(GL_VERTEX_ARRAY);
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);

					m_geometry->release();
					m_atlas->release();
					m_shader->release();
				}

			}

			void GLFont::render(const float x, const float y, const std::string& str)
			{
				render(x, y, str, Color::WHITE);
			}

			void GLFont::render(const float x, const float y, const std::string& str, const Color& color)
			{
				render(x, y, GLFontAlignment::LEFT, str, color);
			}

			void GLFont::render(const float x, const float y, const GLFontAlignment alignment, const std::string& str)
			{
				render(x, y, alignment, str, Color::WHITE);
			}

			void GLFont::render(const float x, const float y, const GLFontAlignment alignment, const std::string& str, const Color& color)
			{
				render(x, y, alignment, UTF8Iterator(str.begin()), UTF8Iterator(str.end()), color);
			}

			void GLFont::render(const float x, const float y, const GLFontAlignment alignment, const UTF8Iterator& beg, const UTF8Iterator& end, const Color& color)
			{
				switch (alignment)
				{
				case CENTER:
					renderAdjusted(x, y, beg, end, color, 0.5f);
					break;
				case RIGHT:
					renderAdjusted(x, y, beg, end, color, 1.f);
					break;
				default:
					renderSimple(x, y, beg, end, color);
					break;
				}

			}

		}

	}

}
