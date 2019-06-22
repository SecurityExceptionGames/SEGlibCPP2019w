#include <org/segames/library/util/Color.h>
#include <org/segames/library/math/math.h>

namespace org
{
	
	namespace segames
	{

		namespace library
		{

			Color::Color() :
				Color(0)
			{}

			Color::Color(unsigned char red, unsigned char green, unsigned char blue) :
				Color(red, green, blue, 255)
			{}

			Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
				m_red(red),
				m_green(green),
				m_blue(blue),
				m_alpha(alpha)
			{}

			Color::Color(float red, float green, float blue) :
				Color(red, green, blue, 1.0f)
			{}

			Color::Color(float red, float green, float blue, float alpha) :
				Color(
					static_cast<unsigned char>(red * 255),
					static_cast<unsigned char>(green * 255),
					static_cast<unsigned char>(blue * 255),
					static_cast<unsigned char>(alpha * 255)
				)
			{}

			Color::Color(unsigned int data) :
				Color(
					static_cast<unsigned char>(data & 0xFF000000 >> 24),
					static_cast<unsigned char>(data & 0x00FF0000 >> 16),
					static_cast<unsigned char>(data & 0x0000FF00 >> 8),
					static_cast<unsigned char>(data & 0x000000FF)
				)
			{}

			unsigned char Color::red() const
			{
				return m_red;
			}

			unsigned char Color::green() const
			{
				return m_green;
			}

			unsigned char Color::blue() const
			{
				return m_blue;
			}

			unsigned char Color::alpha() const
			{
				return m_alpha;
			}

			float Color::getRed() const
			{
				return m_red * 0.0039215686274509803921568627451f;
			}

			float Color::getGreen() const
			{
				return m_green * 0.0039215686274509803921568627451f;
			}

			float Color::getBlue() const
			{
				return m_blue * 0.0039215686274509803921568627451f;
			}

			float Color::getAlpha() const
			{
				return m_alpha * 0.0039215686274509803921568627451f;
			}

			unsigned int Color::asInteger() const
			{
				return
					m_red << 24 &
					m_green << 16 &
					m_blue << 8 &
					m_alpha;
			}

			Color& Color::setRed(const unsigned char value)
			{
				m_red = value;
				return *this;
			}

			Color& Color::setGreen(const unsigned char value)
			{
				m_green = value;
				return *this;
			}

			Color& Color::setBlue(const unsigned char value)
			{
				m_blue = value;
				return *this;
			}

			Color& Color::setAlpha(const unsigned char value)
			{
				m_alpha = value;
				return *this;
			}

			Color& Color::setRed(const float value)
			{
				return setRed(static_cast<unsigned char>(value * 255));
			}

			Color& Color::setGreen(const float value)
			{
				return setGreen(static_cast<unsigned char>(value * 255));
			}

			Color& Color::setBlue(const float value)
			{
				return setBlue(static_cast<unsigned char>(value * 255));
			}

			Color& Color::setAlpha(const float value)
			{
				return setAlpha(static_cast<unsigned char>(value * 255));
			}

			bool Color::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
				{
					const Color& ref = dynamic_cast<const Color&>(obj);

					if (ref.m_red != m_red)
						return false;
					else if (ref.m_green != m_green)
						return false;
					else if (ref.m_blue != m_blue)
						return false;
					else if (ref.m_alpha != m_alpha)
						return false;
					return true;
				}

			}

			std::string Color::toString() const
			{
				std::string out = "Color(";
				out += std::to_string((int)m_red) += ", ";
				out += std::to_string((int)m_green) += ", ";
				out += std::to_string((int)m_blue) += ", ";
				out += std::to_string((int)m_alpha) += ")";
				return out;
			}

			Color Color::RGBtoCMYK(const Color& color)
			{
				const float K = 1 - Math::max(color.getRed(), color.getGreen(), color.getBlue());
				return Color(
					(1 - color.getRed() - K) / (1 - K),
					(1 - color.getGreen() - K) / (1 - K),
					(1 - color.getBlue() - K) / (1 - K),
					K
				);
			}

			Color Color::CMYKtoRGB(const Color& color)
			{
				return Color(
					(1 - color.getRed()) * (1 - color.getAlpha()),
					(1 - color.getGreen()) * (1 - color.getAlpha()),
					(1 - color.getBlue()) * (1 - color.getAlpha()),
					1
				);
			}

			Color Color::BLACK			= Color(0, 0, 0, static_cast<unsigned char>(255));
			Color Color::DARK_GRAY		= Color(64, 64, 64, static_cast<unsigned char>(255));
			Color Color::GRAY			= Color(128, 128, 128, static_cast<unsigned char>(255));
			Color Color::LIGHT_GRAY		= Color(191, 191, 191, static_cast<unsigned char>(255));
			Color Color::WHITE			= Color(255, 255, 255, static_cast<unsigned char>(255));
			Color Color::RED			= Color(255, 0, 0, static_cast<unsigned char>(255));
			Color Color::GREEN			= Color(0, 255, 0, static_cast<unsigned char>(255));
			Color Color::BLUE			= Color(0, 0, 255, static_cast<unsigned char>(255));
			Color Color::YELLOW			= Color(255, 255, 0, static_cast<unsigned char>(255));
			Color Color::CYAN			= Color(0, 255, 255, static_cast<unsigned char>(255));
			Color Color::MAGENTA		= Color(255, 0, 255, static_cast<unsigned char>(255));
			Color Color::MAROON			= Color(128, 0, 0, static_cast<unsigned char>(255));
			Color Color::OLIVE			= Color(128, 128, 0, static_cast<unsigned char>(255));
			Color Color::DARK_GREEN		= Color(0, 128, 0, static_cast<unsigned char>(255));
			Color Color::PURPLE			= Color(128, 0, 128, static_cast<unsigned char>(255));
			Color Color::TEAL			= Color(0, 128, 128, static_cast<unsigned char>(255));
			Color Color::NAVY_BLUE		= Color(0, 0, 128, static_cast<unsigned char>(255));
			Color Color::ORANGE			= Color(255, 165, 0, static_cast<unsigned char>(255));
			Color Color::BROWN			= Color(150, 75, 0, static_cast<unsigned char>(255));
			Color Color::PINK			= Color(255, 192, 203, static_cast<unsigned char>(255));
		}

	}

}
