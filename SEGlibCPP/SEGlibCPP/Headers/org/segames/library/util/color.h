#pragma once
#include <org/segames/library/object.h>

namespace org
{
	
	namespace segames
	{
		
		namespace library
		{

			/*
				A class storing color information for a 32bit, 4 channel color.
				Channels are (rows):
					RGBA:		CMYK:			HSB:
					- Red		- Cyan			- Hue
					- Green		- Magenta		- Saturation
					- Blue		- Yellow		- Brightness
					- Alpha		- Black key		- Alpha

				* @author	Philip Rosberg
				* @since	2019-06-22
				* @edited	2019-06-22
			*/
			class SEG_API Color :
				public Object
			{
			protected:

				/*
					The red component.
				*/
				unsigned char m_red;

				/*
					The green component.
				*/
				unsigned char m_green;

				/*
					The blue component.
				*/
				unsigned char m_blue;

				/*
					The alpha component.
				*/
				unsigned char m_alpha;

			public:

				/*
					Creates a color without setting any information.
				*/
				Color();

				/*
					Creates an opaque color with the given values.
					* @param[in] red The red component
					* @param[in] green The green component
					* @param[in] blue The blue component
				*/
				explicit Color(unsigned char red, unsigned char green, unsigned char blue);

				/*
					Creates a color with the given values.
					* @param[in] red The red component
					* @param[in] green The green component
					* @param[in] blue The blue component
					* @param[in] alpha The alpha component
				*/
				explicit Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

				/*
					Creates an opaque color with the given values.
					* @param[in] red The red component
					* @param[in] green The green component
					* @param[in] blue The blue component
				*/
				explicit Color(float red, float green, float blue);

				/*
					Creates a color with the given values.
					* @param[in] red The red component
					* @param[in] green The green component
					* @param[in] blue The blue component
					* @param[in] alpha The alpha component
				*/
				explicit Color(float red, float green, float blue, float alpha);

				/*
					Creates a color with the given data value.
					* @param[in] data The data value of the color, eg. hexcode 0x00FF00FF
				*/
				explicit Color(unsigned int data);

				/*
					Returns the red value.
				*/
				virtual unsigned char red() const;

				/*
					Returns the green value.
				*/
				virtual unsigned char green() const;

				/*
					Returns the blue value.
				*/
				virtual unsigned char blue() const;

				/*
					Returns the alpha value.
				*/
				virtual unsigned char alpha() const;

				/*
					Returns the red value.
				*/
				virtual float getRed() const;

				/*
					Returns the green value.
				*/
				virtual float getGreen() const;

				/*
					Returns the blue value.
				*/
				virtual float getBlue() const;

				/*
					Returns the alpha value.
				*/
				virtual float getAlpha() const;

				/*
					Returns the color as an integer value.
				*/
				virtual unsigned int asInteger() const;

				/*
					Sets the red value.
					* @param[in] value The value
				*/
				virtual Color& setRed(const unsigned char value);

				/*
					Sets the green value.
					* @param[in] value The value
				*/
				virtual Color& setGreen(const unsigned char value);

				/*
					Sets the blue value.
					* @param[in] value The value
				*/
				virtual Color& setBlue(const unsigned char value);

				/*
					Sets the alpha value.
					* @param[in] value The value
				*/
				virtual Color& setAlpha(const unsigned char value);

				/*
					Sets the red value.
					* @param[in] value The value
				*/
				virtual Color& setRed(const float value);

				/*
					Sets the green value.
					* @param[in] value The value
				*/
				virtual Color& setGreen(const float value);

				/*
					Sets the blue value.
					* @param[in] value The value
				*/
				virtual Color& setBlue(const float value);

				/*
					Sets the alpha value.
					* @param[in] value The value
				*/
				virtual Color& setAlpha(const float value);

				/*
					Returns true if the given object is equal to this color.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override;

				/*
					Returns a string representation of the color.
				*/
				virtual std::string toString() const override;

				/*
					Converts the given RGB color to CMYK
					* @param[in] color The color to convert
				*/
				static Color RGBtoCMYK(const Color& color);

				/*
					Converts the given CMYK color to RGB
					* @param[in] color The color to convert
				*/
				static Color CMYKtoRGB(const Color& color);

				//RGB opaque colors

				static Color BLACK;
				static Color DARK_GRAY;
				static Color GRAY;
				static Color LIGHT_GRAY;
				static Color WHITE;
				static Color RED;
				static Color GREEN;
				static Color BLUE;
				static Color YELLOW;
				static Color CYAN;
				static Color MAGENTA;
				static Color MAROON;
				static Color OLIVE;
				static Color DARK_GREEN;
				static Color PURPLE;
				static Color TEAL;
				static Color NAVY_BLUE;
				static Color ORANGE;
				static Color BROWN;
				static Color PINK;

			};

		}

	}

}