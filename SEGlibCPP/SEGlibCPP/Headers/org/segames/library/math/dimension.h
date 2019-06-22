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
				A generic class destribing a n-dimensional hypercube.

				* @author	Philip Rosberg
				* @since	2019-06-13
				* @edited	2019-06-13
			*/
			template<typename T, int dim>
			class Dimension :
				public Object
			{
			protected:

				/*
					The dimension values.
				*/
				T m_data[dim];
					
			public:

				/*
					Creates a zeroed dimension.
				*/
				Dimension()
				{}

				/*
					Creates a dimension with the given values.
					* @param[in] items The dimensional sizes
				*/
				template<typename... T2>
				explicit Dimension(const T2... items)
				{
#ifdef SEG_API_DEBUG_THROW
					if (sizeof...(items) != dim)
						throw InvalidValueException("Number of elements in parameter pack (" + std::to_string(sizeof...(items)) + ") is not equal to the dimensions (" + std::to_string(dim) + ").");
#endif
					T list[sizeof...(items)] = { (T)items... };
					for (int i = 0; i < dim; i++)
						m_data[i] = list[i];
				}
					
				/*
					Copy/conversion constructor.
					* @param[in] obj The dimension object to copy.
				*/
				template<typename T2>
				explicit Dimension(const Dimension<T2, dim>& obj)
				{
					for (int i = 0; i < dim; i++)
						m_data[i] = (T)obj[i];
				}

				/*
					Returns the size of the dimension.
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
						throw IndexOutOfBoundsException("The given dimension element is not in the dimension: " + std::to_string(n));
#endif
					return m_data[n];
				}

				/*
					Returns true if the given object is equal to this dimension.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override
				{
					if (typeid(obj) == typeid(*this))
					{
						const Dimension<T, dim>& ref = dynamic_cast<const Dimension<T, dim>&>(obj);
						for (int i = 0; i < dim; i++)
							if (ref.m_data[i] != m_data[i])
								return false;
						return true;
					}
					else
						return false;
				}

				/*
					Returns a string representation of the dimension.
				*/
				virtual std::string toString() const override
				{
					std::string out = "Dimension(";
					for (int i = 0; i < dim-1; i++)
						(out += std::to_string(m_data[i])) += ", ";
					(out += std::to_string(m_data[dim - 1])) += ")";
					return out;
				}

			};

		}

	}

}