#pragma once
#include <org/segames/library/array_index_out_of_bounds_exception.h>
#include <org/segames/library/util/array_backed.h>
#include <org/segames/library/object.h>

#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Implementation of a standard dynamically allocated array.

					THREADING INFO: This implementation is not synchronized.

					* @author	Philip Rosberg
					* @since	2019-03-17
					* @edited	2019-03-17
				*/
				template<typename T, typename PosType_ = int>
				class Array :
					public Object,
					public ArrayBacked<T, PosType_>
				{
				public:
					typedef PosType_ PosType;

				private:

					/*
						The size of the array.
					*/
					PosType m_size;

					/*
						The actual array data.
					*/
					std::unique_ptr<T[]> m_array;

				public:

					/*
						Creates an empty array.
					*/
					Array() :
						m_size(0),
						m_array(nullptr)
					{}

					/*
						Creates an array of the given size.
						* @param[in] size The size of the array
					*/
					explicit Array(const PosType size) :
						m_size(size),
						m_array(new T[size])
					{}

					/*
						Copies the given array's data into this one.
						* @param[in] obj The array backed object whose data to copy into this array.
					*/
					explicit Array(const Array<T, PosType>& obj) :
						Array((ArrayBacked<T, PosType>&)obj)
					{}

					/*
						Copies the given array backed object's data into this one.
						* @param[in] obj The array backed object whose data to copy into this array.
					*/
					explicit Array(const ArrayBacked<T, PosType>& obj) :
						Array(obj.size())
					{
						std::copy(obj.pointer(), obj.pointer() + obj.size(), pointer());
					}

					/*
						Returns the size of the array
					*/
					virtual PosType size() const override
					{
						return m_size;
					}

					/*
						Returns the pointer to the array memory.
					*/
					virtual T* pointer() const override
					{
						return m_array.get();
					}

					/*
						Returns a reference to the value at the given position:
						* @param[in] pos The position of the value
					*/
					virtual T& operator[](const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos < 0 || pos >= size())
							throw ArrayIndexOutOfBoundsException(pos, __FILE__, __LINE__);
#endif
						return m_array.get()[pos];
					}

					/*
						Set operator override.
						* @param[in] arr The array to copy from
					*/
					virtual Array<T, PosType>& operator=(const Array<T, PosType>& arr)
					{
						std::unique_ptr<T[]> newArray(new T[arr.size()]);

						m_size = arr.size();
						std::swap(m_array, newArray);

						std::copy(arr.pointer(), arr.pointer() + arr.size(), pointer());
						return *this;
					}

					/*
						Returns true if the the given object is equal to this array.
						Time complexity is at worst O(n).
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const override
					{
						if (typeid(obj) == typeid(*this))
						{
							Array<T, PosType>& arr = (Array<T, PosType>&)obj;

							if (size() != arr.size())
								return false;

							for (int i = 0; i < size(); i++)
								if (pointer()[i] != arr.pointer()[i])
									return false;

							return true;
						}
						return false;
					}

					/*
						Returns a string representation of the array.
					*/
					virtual std::string toString() const override
					{
						std::string out = "[ ";
						if (size() > 0)
							out += std::to_string(pointer()[0]);

						for (PosType i = 1; i < size(); i++)
							out += ", " + std::to_string(pointer()[i]);

						return out + " ]";
					}

				};

			}

		}

	}

}
