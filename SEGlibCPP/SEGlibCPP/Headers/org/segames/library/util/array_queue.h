#pragma once
#include <org/segames/library/util/array_list.h>
#include <org/segames/library/util/queue.h>
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
					Implementation of an array backed queue.
					All operations run on average in constant time, ie. O(1), if not noted otherwise.

					THREADING INFO: This implementation is not synchronized.

					* @author	Philip Rosberg
					* @since	2019-03-16
					* @edited	2019-03-16
				*/
				template<typename T>
				class ArrayQueue :
					public Object,
					public ArrayBacked<T, typename ArrayList<T>::PosType>,
					public Queue<T>
				{
				protected:

					/*
						The backing array list
					*/
					ArrayList<T> m_list;

				public:

					/*
						Creates a standard array queue.
					*/
					ArrayQueue()
					{}

					/*
						Creates an array queue of the given starting capacity.
						* @param[in] capacity The starting capacity of the queue
					*/
					ArrayQueue(const typename ArrayList<T>::PosType capacity) :
						m_list(capacity)
					{}

					/*
						Copies the given array backed object's data into this one.
						* @param[in] obj The array backed object whose data to copy into this queue.
					*/
					ArrayQueue(const ArrayBacked<T, typename ArrayList<T>::PosType>& obj) :
						m_list(obj)
					{}

					/*
						Returns true if the queue is empty.
					*/
					virtual bool isEmpty() const
					{
						return m_list.isEmpty();
					}

					/*
						Returns the size/amount of values in the queue.
					*/
					virtual typename ArrayList<T>::PosType size() const
					{
						return m_list.size();
					}

					/*
						Returns the first value in the queue.
					*/
					virtual T& peek() const
					{
						return m_list.get(0);
					}

					/*
						Returns the pointer to the first element of the relevant part of the backing array.
					*/
					virtual T* pointer() const
					{
						return m_list.pointer();
					}

					/*
						Removes the first element in the queue and returns the value.
					*/
					virtual T dequeue()
					{
						return m_list.remove(0);
					}

					/*
						Adds the given value to the queue
					*/
					virtual void enqueue(const T& value)
					{
						m_list.add(value);
					}

					/*
						Removes all content from the queue.
					*/
					virtual void clear()
					{
						m_list.clear();
					}

					/*
						Ensures that the queue has atleast the given size amount of slots in the backing array.
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
						The time complexity is O(n), where n is the amount of values in the queue.
					*/
					virtual void compact()
					{
						m_list.compact();
					}

					/*
						Returns true if the the given object is equal to this queue.
						Time complexity is at worst O(n).
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const
					{
						if (typeid(obj) == typeid(*this))
						{
							ArrayQueue<T>& arr = (ArrayQueue<T>&)obj;

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
						Returns a string representation of the queue.
					*/
					virtual std::string toString() const
					{
						std::string out = "[ ";
						if (size() > 0)
							out += std::to_string(pointer()[0]);

						for (typename ArrayList<T>::PosType i = 1; i < size(); i++)
							out += ", " + std::to_string(pointer()[i]);

						return out + " ]";
					}

				};

			}

		}

	}

}
