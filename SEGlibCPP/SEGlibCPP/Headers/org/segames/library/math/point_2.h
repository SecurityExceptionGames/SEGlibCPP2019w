#pragma once
#include <org/segames/library/math/point.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class destribing a 2-dimensional point.

				* @author	Philip Rosberg
				* @since	2019-06-23
				* @edited	2019-06-23
			*/
			template<typename T>
			class Point2 :
				public Point<T, 2>
			{
			public:

				/*
					Creates an zeroed point.
				*/
				Point2() :
					Point<T, 2>::Point()
				{}

				/*
					Creates a point with the given values.
					* @param[in] x The x position of the point
					* @param[in] y The y position of the point
				*/
				template<typename T2>
				explicit Point2(const T2 x, const T2 y) :
					Point<T, 2>::Point(x, y)
				{}

				/*
					Returns the x position.
				*/
				virtual T getX() const
				{
					return this->m_data[0];
				}

				/*
					Returns the y position.
				*/
				virtual T getY() const
				{
					return this->m_data[1];
				}

				/*
					Sets the x position.
					* @param[in] value The new value of the x position
				*/
				virtual void setX(const T value)
				{
					this->m_data[0] = value;
				}

				/*
					Sets the y position.
					* @param[in] value The new value of the y position
				*/
				virtual void setY(const T value)
				{
					this->m_data[1] = value;
				}

			};

			using Point2i = Point2<int>;
			using Point2f = Point2<float>;
			using Point2d = Point2<double>;

		}

	}

}