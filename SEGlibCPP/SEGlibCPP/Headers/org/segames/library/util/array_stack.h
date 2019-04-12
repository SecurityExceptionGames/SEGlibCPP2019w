#pragma once
#include <org/segames/library/util/array_list.h>
#include <org/segames/library/util/stack.h>
#include <org/segames/library/util/array_backed.h>
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Implementation of an array backed stack.
					All operations run on average in constant time, ie. O(1), if not noted otherwise.

					THREADING INFO: This implementation is not synchronized.

					* @author	Philip Rosberg
					* @since	2019-03-17
					* @edited	2019-03-17
				*/
				template<typename T>
				class ArrayStack :
					public Object,
					public ArrayBacked<T, typename ArrayList<T>::PosType>,
					public Stack<T>
				{
				protected:

					/*
						The backing array list
					*/
					ArrayList<T> m_list;

				public:

					/*
						Creates a standard array stack.
					*/
					ArrayStack()
					{}

					/*
						Creates an array queue of the given starting capacity.
						* @param[in] capacity The starting capacity of the stack
					*/
					ArrayStack(const typename ArrayList<T>::PosType capacity) :
						m_list(capacity)
					{}

					/*
						Copies the given array backed object's data into this one.
						* @param[in] obj The array backed object whose data to copy into this stack.
					*/
					ArrayStack(const ArrayBacked<T, typename ArrayList<T>::PosType>& obj) :
						m_list(obj)
					{}

					/*
						Returns true if the stack is empty.
					*/
					virtual bool isEmpty() const
					{
						return m_list.isEmpty();
					}

					/*
						Returns the size/amount of values in the stack.
					*/
					virtual typename ArrayList<T>::PosType size() const
					{
						return m_list.size();
					}

					/*
						Returns the top value in the stack.
					*/
					virtual T& peek() const
					{
						return m_list.get(m_list.size() - 1);
					}

					/*
						Returns the pointer to the first element of the relevant part of the backing array.
					*/
					virtual T* pointer() const
					{
						return m_list.pointer();
					}

					/*
						Removes and returns the top value in the stack.
					*/
					virtual T pop()
					{
						return m_list.remove(m_list.size() - 1);
					}

					/*
						Adds the given value to the top of the stack.
						* @param[in] value The value to add
					*/
					virtual void push(const T& value)
					{
						m_list.add(value);
					}

					/*
						Removes all content from the stack.
					*/
					virtual void clear()
					{
						m_list.clear();
					}

					/*
						Ensures that the stack has atleast the given size amount of slots in the backing array.
						If size is smaller than the current capacity nothing is done.
						On resize the time complexity is O(n), where n is the amount of values in the array.
						* @param[in] size The size to ensure that the backing array has
					*/
					virtual void reserve(const typename ArrayList<T>::PosType size)
					{
						m_list.reserve(size);
					}

					/*
						Compacts the backing array to the size of the data.
						The time complexity is O(n), where n is the amount of values in the stack.
					*/
					virtual void compact()
					{
						m_list.compact();
					}

					/*
						Returns true if the the given object is equal to this stack.
						Time complexity is at worst O(n).
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const
					{
						if (typeid(obj) == typeid(*this))
						{
							ArrayStack<T>& stack = (ArrayStack<T>&)obj;

							if (m_list.size() != stack.m_list.size())
								return false;

							for (int i = 0; i < m_list.size(); i++)
								if (m_list.get(i) != stack.m_list.get(i))
									return false;

							return true;
						}
						return false;
					}
					
					/*
						Returns a string representation of the stack.
					*/
					virtual std::string toString() const
					{
						return m_list.toString();
					}

				};

			}

		}

	}

}