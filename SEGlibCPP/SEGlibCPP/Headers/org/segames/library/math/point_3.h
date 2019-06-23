#pragma once
#include <org/segames/library/math/point.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class destribing a 3-dimensional point.

				* @author	Philip Rosberg
				* @since	2019-06-23
				* @edited	2019-06-23
			*/
			template<typename T>
			class Point3 :
				public Point<T, 3>
			{
			public:

				/*
					Creates an zeroed point.
				*/
				Point3() :
					Point<T, 3>::Point()
				{}

				/*
					Creates a point with the given values.
					* @param[in] x The x position of the point
					* @param[in] y The y position of the point
					* @param[in] z The z position of the point
				*/
				template<typename T2>
				explicit Point3(const T2 x, const T2 y, const T2 z) :
					Point<T, 3>::Point(x, y, z)
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
					Returns the z position.
				*/
				virtual T getZ() const
				{
					return this->m_data[2];
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

				/*
					Sets the z position.
					* @param[in] value The new value of the z position
				*/
				virtual void setZ(const T value)
				{
					this->m_data[2] = value;
				}

			};

			using Point3i = Point3<int>;
			using Point3f = Point3<float>;
			using Point3d = Point3<double>;

		}

	}

}