#include <org/segames/library/gl/text/gl_font.h>
#include <org/segames/library/io/file.h>
#include <org/segames/library/math/math.h>
#include <org/segames/library/util/utf8_iterator.h>

using org::segames::library::io::File;
using org::segames::library::math::Dimension3i;
using org::segames::library::util::ArrayList;
using org::segames::library::util::UTF8Iterator;
using org::segames::library::math::min;

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

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
					return min((int)exp2(ceil(log2(side))), GLTexture::glMaxTextureSize());
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
					m_geometryInf.reset(new GLPointerInf[2]);
					m_geometry.reset(new GLFloatBuffer());

					m_geometry->setPointerBinding(GLDataType::VERTEX, m_geometryInf[0] = GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 4, 0));
					m_geometry->setPointerBinding(GLDataType::TEX_COORD, m_geometryInf[1] = GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 4, sizeof(GLfloat) * 2));

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

				GLFont::GLFont(const float size, const unsigned int oversampling, const std::string& path, const unsigned int* chars, const int numChars) :
					m_height(size)
				{
					File file(path);
					std::ifstream input(file.openInput());
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

					//Load shader
					m_shader.reset(new GLShader());
					m_shader->loadVertexData("test/font.vert");
					m_shader->loadFragmentData("test/font.frag");
				}

				GLTexture* GLFont::getTexture()
				{
					return m_atlas.get();
				}

				void GLFont::upload()
				{
					m_atlas->upload(GL_UNSIGNED_BYTE, m_atlasData.get());
					m_atlas->bind().setParameters(GL_REPEAT, GL_LINEAR, GL_LINEAR).release();
					m_atlasData.reset();

					m_geometry->upload(GL_STATIC_DRAW);
					m_geometry->compact();

					m_shader->upload();
				}

				void GLFont::render(const float x, const float y, const std::string& str)
				{
					if (str.length() > 0)
					{
						UTF8Iterator itr(str);

						m_shader->bind();
						glUniform1i(glGetUniformLocation(m_shader->getID(), "atlas"), 0);
						
						m_atlas->bind();
						m_geometry->bind().setPointerInf();

						glEnableClientState(GL_VERTEX_ARRAY);
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);

						GLint loc = glGetUniformLocation(m_shader->getID(), "pos");
						float xp = x, yp = y;
						while (itr != str.end())
						{
							unsigned int c = *itr;
							if (c == '\n' || c == '\r' || xp >= 1920)
							{
								xp = x;
								yp += m_height;
								continue;
							}

							auto res = m_glyphs.find(c);
							if (res != m_glyphs.end())
							{
								glUniform2f(loc, xp, yp);
								glDrawArrays(GL_QUADS, res->second.getIndex() * 4, 4);
								xp += res->second.getAdvance();
							}

							itr++;
						}

						glDisableClientState(GL_VERTEX_ARRAY);
						glDisableClientState(GL_TEXTURE_COORD_ARRAY);

						m_geometry->release();
						m_atlas->release();
						m_shader->release();
					}

				}

			}

		}

	}

}