#pragma once
#include <org/segames/library/util/abstract_list.h>
#include <org/segames/library/util/array_backed.h>
#include <org/segames/library/math/math.h>
#include <org/segames/library/array_index_out_of_bounds_exception.h>

#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Implementation of an array-backed scaling list.

				THREADING INFO: This implementation is not synchronized.

				* @author	Philip Rosberg
				* @since	2019-03-15
				* @edited	2019-03-17
			*/
			template<typename T>
			class ArrayList :
				public AbstractList<T, int>,
				public ArrayBacked<T, typename AbstractList<T, int>::PosType>
			{
			public:
				using typename AbstractList<T, int>::PosType;

			protected:

				/*
					The lower write position.
				*/
				PosType m_lower;

				/*
					The upper write position (after the last element).
				*/
				PosType m_upper;

				/*
					Capacity of the backing array.
				*/
				PosType m_capacity;

				/*
					The backing array
				*/
				std::unique_ptr<T[]> m_array;

				/*
					Resizes the backing array to the given size and copies the old elements.
					Elements outside the range will be discarded.
					* @param[in] newSize The new size of the backing array.
				*/
				virtual void resizeArray(const PosType newSize)
				{
					PosType minSize = Math::min(newSize, m_upper - m_lower);
					std::unique_ptr<T[]> newArray = std::unique_ptr<T[]>(new T[newSize]);

					for (PosType i = 0; i < minSize; i++)
						std::swap(newArray.get()[i], m_array.get()[i + m_lower]);

					m_lower = 0;
					m_upper = minSize;
					m_capacity = newSize;
					std::swap(m_array, newArray);
				}

			public:

				/*
					Creates an array list of the given starting capacity.
					* @param[in] capacity The starting capacity of the list
				*/
				explicit ArrayList(const PosType capacity) :
					m_lower(0),
					m_upper(m_lower),
					m_capacity(capacity),
					m_array(new T[capacity])
				{}

				/*
					Creates an array list of standard starting capacity.
				*/
				ArrayList() :
					ArrayList(2)
				{}

				/*
					Copies the given list into this one.
					* @param[in] list The list whose content to copy into this one
				*/
				ArrayList(const ArrayList<T>& list) :
					ArrayList((ArrayBacked<T, PosType>&)list)
				{}

				/*
					Copies the given array backed object's data into this one.
					* @param[in] obj The array backed object whose data to copy into this list.
				*/
				explicit ArrayList(const ArrayBacked<T, PosType>& obj) :
					ArrayList(obj.size())
				{
					std::copy(obj.pointer(), obj.pointer() + obj.size(), this->pointer());
					m_upper = (PosType)obj.size();
				}

				/*
					Returns true if the list is empty.
				*/
				virtual bool isEmpty() const override
				{
					return m_lower == m_upper;
				}

				/*
					Returns true if the given position is at the end of the list.
					* @param[in] pos The position in the list
				*/
				virtual bool isEnd(const PosType pos) const override
				{
					return pos == size();
				}

				/*
					Returns a reference to the value at the given position.
					* @param[in] pos The position in the list
				*/
				virtual T& get(const PosType pos) const override
				{
#ifdef SEG_API_DEBUG_THROW
					if (pos < 0 || pos >= size())
						throw ArrayIndexOutOfBoundsException(pos, __FILE__, __LINE__);
#endif
					return m_array[pos + m_lower];
				}

				/*
					Returns the size/amount of values in the list.
				*/
				virtual PosType size() const
				{
					return m_upper - m_lower;
				}

				/*
					Returns the first position for iteration in the list.
				*/
				virtual PosType first() const override
				{
					return 0;
				}

				/*
					Returns the pointer to the first element of the relevant part of the backing array.
				*/
				virtual T* pointer() const override
				{
					return m_array.get() + m_lower;
				}

				/*
					Returns the next position in the list.
					* @param[in] pos The position in the list
				*/
				virtual PosType next(const PosType pos) const override
				{
					return pos + 1;
				}

				/*
					Adds the given value to the end of the list.
					The time complexity of this method is constant, ie. O(1).
					* @param[in] value The value to add
				*/
				virtual PosType add(const T& value) override
				{
					if (m_upper == m_capacity)
					{
						if (size() > m_capacity * 3 / 4)
							resizeArray(m_capacity * 2);
						else
							resizeArray(m_capacity);
					}
					m_array[m_upper++] = value;
					return m_upper - 1 - m_lower;
				}

				/*
					Inserts the given value at the given position moving all current items one step forwards.
					The time complexity of this method is on average O(n - p) where n is the amount of values in the array and p is the
					position.
					* @param[in] pos The position to insert at
					* @param[in] value The value to insert
				*/
				virtual PosType insert(const PosType pos, const T& value) override
				{
#ifdef SEG_API_DEBUG_THROW
					if (pos < 0 || pos >= size() + 1)
						throw ArrayIndexOutOfBoundsException(pos, __FILE__, __LINE__);
#endif
					PosType posInArray = pos + m_lower;

					if (posInArray == m_upper)
						return add(value);
					else if (pos == 0)
						if (m_lower > 0)
						{
							--m_lower;
							m_array[m_lower] = value;
							return 0;
						}

					if (m_upper == m_capacity)
						resizeArray(m_capacity * 2);

					for (PosType i = m_upper; i > posInArray; i--)
						std::swap(m_array[i - 1], m_array[i]);
					++m_upper;

					m_array[posInArray] = value;
					return pos;
				}

				/*
					Sets the value of the element at the given position.
					Returns the value that previously existed at that position.
					* @param[in] pos The position to set the value at
					* @param[in] value The value to set
				*/
				virtual T set(const PosType pos, const T& value)
				{
#ifdef SEG_API_DEBUG_THROW
					if (pos < 0 || pos >= size())
						throw ArrayIndexOutOfBoundsException(pos, __FILE__, __LINE__);
#endif
					T outVal = value;
					std::swap(outVal, m_array[m_lower + pos]);
					return outVal;
				}

				/*
					Removes the element at the given position.
					The time complexity of this method is on average O(n - p) where n is the amount of values in the array and p is the
					position. Removing the first or the last item is O(1).
					* @param[in] pos The position in the list
				*/
				virtual T remove(const PosType pos) override
				{
#ifdef SEG_API_DEBUG_THROW
					if (pos < 0 || pos >= size())
						throw ArrayIndexOutOfBoundsException(pos, __FILE__, __LINE__);
#endif
					T value = T();
					PosType posInArray = pos + m_lower;
					std::swap(value, m_array[posInArray]);

					if (posInArray == m_upper - 1)
						--m_upper;
					else if (pos == 0)
						++m_lower;
					else if (pos > (m_upper - m_lower) / 2)
					{
						for (PosType i = posInArray; i < m_upper; i++)
							std::swap(m_array[i], m_array[i + 1]);
						--m_upper;
					}
					else
					{
						for (PosType i = posInArray; i > m_lower; i--)
							std::swap(m_array[i - 1], m_array[i]);
						++m_lower;
					}

					return value;
				}

				/*
					Seemingly removes all content from the list.
					The time complexity is constant, ie. O(1).
				*/
				virtual void clear() override
				{
					m_upper = m_lower;
				}

				/*
					Ensures that the list has atleast the given size amount of slots in the backing array.
					If size is smaller than the current capacity nothing is done. If the given size is equal
					to the current capacity the call to this method compacts the existing data towards the end.
					On resize the time complexity is O(n), where n is the amount of values in the array.
					* @param[in] size The size to ensure that the backing array has
				*/
				virtual void reserve(const PosType size)
				{
					if (size >= m_capacity)
						resizeArray(size);
				}

				/*
					Compacts the backing array to the size of the data.
					The time complexity is O(n), where n is the amount of values in the list.
				*/
				virtual void compact()
				{
					resizeArray(m_upper - m_lower);
				}

				/*
					Set operator override.
					* @param[in] list The list to copy from.
				*/
				virtual ArrayList<T>& operator=(const ArrayList<T>& list)
				{
					clear();
					reserve(list.size());
					std::copy(list.pointer(), list.pointer() + list.size(), pointer());
					m_upper = list.size();
					return *this;
				}

			};

		}

	}

}
