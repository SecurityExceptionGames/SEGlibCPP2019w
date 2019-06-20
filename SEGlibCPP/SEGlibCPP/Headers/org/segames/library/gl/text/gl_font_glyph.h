#pragma once
#include <org/segames/library/object.h>

#include <stb/stb_truetype.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					A class storing information for one glyph.

					* @author	Philip Rosberg
					* @since	2019-06-18
					* @edited	2019-06-18
				*/
				class SEG_API GLFontGlyph :
					public Object
				{
				protected:

					/*
						The index of the character in eventual buffers.
					*/
					int m_index;

					/*
						The total width of the glyph including buffer zones.
					*/
					float m_advance;

					/*
						The width of the glyph.
					*/
					float m_width;

					/*
						The height of the glyph.
					*/
					float m_height;

					/*
						The offset distance from the left most edge to the start of the glyph.
					*/
					float m_xOff;

					/*
						The offset distance from the upper edge to the start of the glyph.
					*/
					float m_yOff;

					/*
						The backing stb quad.
					*/
					stbtt_aligned_quad m_quad;

				public:

					/*
						Creates an empty/zeroed glyph info.
					*/
					GLFontGlyph();

					/*
						Creates a glyph info from the given data.
						* @param[in] index The index of the glyph in eventual buffers
						* @param[in] advance The glyph advance
						* @param[in] width The glyph width
						* @param[in] height The glyph height
						* @param[in] xOff The glyph offset from the left
						* @param[in] yOff The glyph offset from the top
						* @param[in] quad The aligned quad from stb
					*/
					explicit GLFontGlyph(const int index, const float advance, const float width, const float height, const float xOff, const float yOff, const stbtt_aligned_quad& quad);

					/*
						Returns the index of the glyph.
					*/
					virtual int getIndex() const;

					/*
						Returns the advance of the glyph. Ie. total width of the glyph including buffer zones.
					*/
					virtual float getAdvance() const;

					/*
						Returns the width of the glyph.
					*/
					virtual float getWidth() const;

					/*
						Returns the height of the glyph.
					*/
					virtual float getHeight() const;

					/*
						Returns the offset distance from the left most edge to the start of the glyph.
					*/
					virtual float getXOffset() const;

					/*
						Returns the offset distance from the upper edge to the start of the glyph.
					*/
					virtual float getYOffset() const;

					/*
						Returns the stb aligned quad of the glyph.
					*/
					virtual const stbtt_aligned_quad& getQuad() const;

				};

			}

		}

	}

}