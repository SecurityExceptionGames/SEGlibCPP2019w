#include <org/segames/library/gl/text/gl_font_glyph.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLFontGlyph::GLFontGlyph() :
				m_index(-1),
				m_advance(0),
				m_width(0),
				m_height(0),
				m_xOff(0),
				m_yOff(0)
			{}

			GLFontGlyph::GLFontGlyph(const int index, const float advance, const float width, const float height, const float xOff, const float yOff, const stbtt_aligned_quad& quad) :
				m_index(index),
				m_advance(advance),
				m_width(width),
				m_height(height),
				m_xOff(xOff),
				m_yOff(yOff),
				m_quad(quad)
			{}

			int GLFontGlyph::getIndex() const
			{
				return m_index;
			}

			float GLFontGlyph::getAdvance() const
			{
				return m_advance;
			}

			float GLFontGlyph::getWidth() const
			{
				return m_width;
			}

			float GLFontGlyph::getHeight() const
			{
				return m_height;
			}

			float GLFontGlyph::getXOffset() const
			{
				return m_xOff;
			}

			float GLFontGlyph::getYOffset() const
			{
				return m_yOff;
			}

			const stbtt_aligned_quad& GLFontGlyph::getQuad() const
			{
				return m_quad;
			}

			bool GLFontGlyph::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
				{
					const GLFontGlyph& ref = dynamic_cast<const GLFontGlyph&>(obj);

					for (size_t i = 0; i < sizeof(*this); i++)
						if (reinterpret_cast<const char*>(&ref)[i] != reinterpret_cast<const char*>(this)[i])
							return false;
					return true;
				}

			}

			GLFontGlyph GLFontGlyph::EMPTY = GLFontGlyph();

		}

	}

}