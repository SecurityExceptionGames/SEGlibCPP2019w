#pragma once
#include <org/segames/library/object.h>
#include <org/segames/library/invalid_value_exception.h>
#include <org/segames/library/index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A generic class destribing a n-dimensional point.

				* @author	Philip Rosberg
				* @since	2019-06-23
				* @edited	2019-06-23
			*/
			template<typename T, int dim>
			class Point :
				public Object
			{
			protected:

				/*
					The point values.
				*/
				T m_data[dim];

			public:

				/*
					Creates a zeroed point.
				*/
				Point()
				{}

				/*
					Creates a point with the given values.
					* @param[in] items The point values
				*/
				template<typename... T2>
				explicit Point(const T2... items)
				{
#ifdef SEG_API_DEBUG_THROW
					if (sizeof...(items) != dim)
						throw InvalidValueException("Number of elements in parameter pack (" + std::to_string(sizeof...(items)) + ") is not equal to the dimensions of the point (" + std::to_string(dim) + ").");
#endif
					T list[sizeof...(items)] = { (T)items... };
					for (int i = 0; i < dim; i++)
						m_data[i] = list[i];
				}

				/*
					Copy/conversion constructor.
					* @param[in] obj The point object to copy.
				*/
				template<typename T2>
				explicit Point(const Point<T2, dim>& obj)
				{
					for (int i = 0; i < dim; i++)
						m_data[i] = (T)obj[i];
				}

				/*
					Returns the number of dimensions of the point.
				*/
				inline virtual int dimensions() const
				{
					return dim;
				}

				/*
					Returns a reference to the element at the given position
					* @param[in] n The position of the element to return
				*/
				inline T& operator[](const int n)
				{
#ifdef SEG_API_DEBUG_THROW
					if (n < 0 || n >= dim)
						throw IndexOutOfBoundsException("The given point element is not in the point: " + std::to_string(n));
#endif
					return m_data[n];
				}

				/*
					Returns true if the given object is equal to this point.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override
				{
					if (typeid(obj) == typeid(*this))
					{
						const Point<T, dim>& ref = dynamic_cast<const Point<T, dim>&>(obj);
						for (int i = 0; i < dim; i++)
							if (ref.m_data[i] != m_data[i])
								return false;
						return true;
					}
					else
						return false;
				}

				/*
					Returns a string representation of the point.
				*/
				virtual std::string toString() const override
				{
					std::string out = "Point(";
					for (int i = 0; i < dim - 1; i++)
						(out += std::to_string(m_data[i])) += ", ";
					(out += std::to_string(m_data[dim - 1])) += ")";
					return out;
				}

			};

		}

	}

}