#pragma once
#include <org/segames/library/math/dimension.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class destribing a 2-dimensional dimension.

				* @author	Philip Rosberg
				* @since	2019-06-13
				* @edited	2019-06-13
			*/
			template<typename T>
			class Dimension2 :
				public Dimension<T, 2>
			{
			public:

				/*
					Creates an empty dimension.
				*/
				Dimension2() :
					Dimension<T, 2>::Dimension()
				{}

				/*
					Creates a dimension with the given values.
					* @param[in] width The width of the dimension
					* @param[in] height The height of the dimension
				*/
				template<typename T2>
				explicit Dimension2(const T2 width, const T2 height) :
					Dimension<T, 2>::Dimension(width, height)
				{}

				/*
					Returns the width.
				*/
				virtual T getWidth() const
				{
					return this->m_data[0];
				}

				/*
					Returns the height.
				*/
				virtual T getHeight() const
				{
					return this->m_data[1];
				}

				/*
					Sets the width.
					* @param[in] value The new value of the width
				*/
				virtual void setWidth(const T value)
				{
					this->m_data[0] = value;
				}

				/*
					Sets the height.
					* @param[in] value The new value of the height
				*/
				virtual void setHeight(const T value)
				{
					this->m_data[1] = value;
				}

			};

			using Dimension2i = Dimension2<int>;
			using Dimension2f = Dimension2<float>;
			using Dimension2d = Dimension2<double>;

		}

	}

}