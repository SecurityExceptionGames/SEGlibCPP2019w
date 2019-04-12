#pragma once
#include <org/segames/library/util/abstract_list.h>
#include <org/segames/library/null_pointer_exception.h>

#include <memory>

#include <org/segames/library/util/iterator.h>
#include <org/segames/library/util/iterable.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				template<typename T>
				class LinkedList;

				/*
					Linked list node struct.

					* @author	Philip Rosberg
					* @since	2019-03-15
					* @edited	2019-03-15
				*/
				template<typename T>
				struct LinkedListNode
				{
					T value;
					LinkedListNode* previous = nullptr;
					LinkedListNode* next = nullptr;
				};

				template<typename T>
				class LLItr :
					public Iterator<T>
				{
				private:
					const LinkedList<T>& m_list;
					LinkedListNode<T>* m_pos;

				public:

					LLItr(const LinkedList<T>& list, LinkedListNode<T>* pos) :
						m_list(list),
						m_pos(pos)
					{}

					virtual bool hasNext() const
					{
						return !m_list.isEnd(m_pos);
					}

					virtual void next()
					{
						m_pos = m_pos->next;
					}

					virtual const T& get() const
					{
						return m_pos->value;
					}

				};
				
				/*
					Implementation of a dual-linked list.
					It is generally advised to use the list interface to interact with the list and to not edit the returned position nodes.
					All operations run in constant time, O(1), but with a rather large constant. The only exception to this being the clear()
					method.

					THREADING INFO: This implementation is not synchronized.

					* @author	Philip Rosberg
					* @since	2019-03-15
					* @edited	2019-03-16
				*/
				template<typename T>
				class LinkedList :
					public AbstractList<T, LinkedListNode<T>*>,
					public Iterable<T, LLItr<T>>
				{
				public:
					using typename AbstractList<T, LinkedListNode<T>*>::PosType;

				protected:

					/*
						The first node in the list.
					*/
					PosType m_first;

					/*
						The last node in the list.
					*/
					PosType m_last;

				public:

					//================================
					//            Test code
					//================================

					LLItr<T> begin() const
					{
						return LLItr<T>(*this, m_first);
					}

					//================================
					//          EOTestCode
					//================================


				public:

					/*
						Creates a new linked list.
					*/
					LinkedList() :
						m_first(new LinkedListNode<T>()),
						m_last(m_first)
					{}

					/*
						Copies the given list into this one.
						* @param[in] list The list whose content to copy into this one
					*/
					LinkedList(const LinkedList<T>& list) :
						LinkedList()
					{
						PosType pos = list.first();
						while (!list.isEnd(pos))
						{
							add(list.get(pos));
							pos = list.next(pos);
						}

					}
					
					/*
						Destructor.
					*/
					virtual ~LinkedList()
					{
						clear();
						delete first();
					}

					/*
						Returns true if the list is empty.
					*/
					virtual bool isEmpty() const
					{
						return m_first->next == nullptr;
					}

					/*
						Returns true if the given position is at the begining of the list.
						* @param[in] pos The position in the list
					*/
					virtual bool isBegin(const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						return pos->previous == nullptr;
					}

					/*
						Returns true if the given position is at the end of the list.
						* @param[in] pos The position in the list
					*/
					virtual bool isEnd(const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						return pos->next == nullptr;
					}

					/*
						Returns a reference to the value at the given position.
						* @param[in] pos The position in the list
					*/
					virtual T& get(const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						return pos->value;
					}

					/*
						Returns the first position for iteration in the list.
					*/
					virtual PosType first() const
					{
						return m_first;
					}

					/*
						Returns the last position for iteration in the list. 
						In this implementation the position is actually after the last element.
					*/
					virtual PosType last() const
					{
						return m_last;
					}

					/*
						Returns the next position in the list.
						* @param[in] pos The position in the list
					*/
					virtual PosType next(const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						return pos->next;
					}

					/*
						Returns the previous position in the list.
						* @param[in] pos The position in the list
					*/
					virtual PosType previous(const PosType pos) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						return pos->previous;
					}

					/*
						Adds the given value to the end of the list.
						* @param[in] value The value to add
					*/
					virtual PosType add(const T& value)
					{
						return insert(last(), value);
					}

					/*
						Inserts the given value at the given position.
						* @param[in] pos The position to insert at
						* @param[in] value The value to insert
					*/
					virtual PosType insert(const PosType pos, const T& value)
					{
						PosType newPos = new LinkedListNode<T>();
						newPos->value = value;

#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif

						if (!isBegin(pos))
						{
							pos->previous->next = newPos;
							newPos->previous = pos->previous;
						}
						else
							m_first = newPos;

						newPos->next = pos;
						pos->previous = newPos;
						return newPos;
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
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						T outVal = value;
						std::swap(outVal, pos->value);
						return outVal;
					}

					/*
						Removes the element at the given position.
						* @param[in] pos The position in the list
					*/
					virtual T remove(const PosType pos)
					{
#ifdef SEG_API_DEBUG_THROW
						if (pos == nullptr)
							throw NullPointerException("Linked list node was null.", __FILE__, __LINE__);
#endif
						T value;
						std::swap(value, pos->value);

						if (!isBegin(pos))
							pos->previous->next = pos->next;
						else
							m_first = pos->next;

						if (!isEnd(pos))
							pos->next->previous = pos->previous;
						else
							m_last = pos->previous;

						delete pos;
						return value;
					}

					/*
						Removes all content from the list.
					*/
					virtual void clear()
					{
						while (!isEmpty())
							remove(first());
					}

					/*
						Set operator override.
						* @param[in] list The list to copy from.
					*/
					virtual LinkedList<T>& operator=(const LinkedList<T>& list)
					{
						clear();

						PosType pos = list.first();
						while (!list.isEnd(pos))
						{
							add(list.get(pos));
							pos = list.next(pos);
						}

						return *this;
					}

				};

			}

		}

	}

}
