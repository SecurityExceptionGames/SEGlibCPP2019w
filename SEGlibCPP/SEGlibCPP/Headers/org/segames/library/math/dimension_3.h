#pragma once
#include <org/segames/library/math/dimension.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class destribing a 3-dimensional dimension.

				* @author	Philip Rosberg
				* @since	2019-06-13
				* @edited	2019-06-13
			*/
			template<typename T>
			class Dimension3 :
				public Dimension<T, 3>
			{
			public:

				/*
					Creates an empty dimension.
				*/
				Dimension3() :
					Dimension<T, 3>::Dimension()
				{}

				/*
					Creates a dimension with the given values.
					* @param[in] width The width of the dimension
					* @param[in] height The height of the dimension
					* @param[in] depth The depth of the dimension
				*/
				template<typename T2>
				explicit Dimension3(const T2 width, const T2 height, const T2 depth) :
					Dimension<T, 3>::Dimension(width, height, depth)
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
					Returns the depth.
				*/
				virtual T getDepth() const
				{
					return this->m_data[2];
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

				/*
					Sets the depth.
					* @param[in] value The new value of the depth
				*/
				virtual void setDepth(const T value)
				{
					this->m_data[2] = value;
				}

			};

			using Dimension3i = Dimension3<int>;
			using Dimension3f = Dimension3<float>;
			using Dimension3d = Dimension3<double>;
			
		}

	}

}