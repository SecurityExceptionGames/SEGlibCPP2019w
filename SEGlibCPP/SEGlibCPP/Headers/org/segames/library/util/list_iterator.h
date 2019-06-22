#pragma once
#include <org/segames/library/util/list.h>
#include <org/segames/library/util/iterator.h>
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An iterator for one directional lists.

				* @author	Philip Rosberg
				* @since	2019-03-21
				* @edited	2019-03-21
			*/
			template<typename T, typename PosType_ = size_t>
			class ListIterator :
				public Iterator<T>
			{
			protected:

				/*
					Reference to the list.
				*/
				const List<T, PosType_>& m_list;

				/*
					The iterator position.
				*/
				PosType_ m_pos;

			public:

				/*
					Creates a list iterator of the given position.
					* @param[in] list The list to iterate through
					* @param[in] pos The iterator position to start at
				*/
				explicit ListIterator(const List<T, PosType_>& list, PosType_ pos) :
					m_list(list),
					m_pos(pos)
				{}

				/*
					Returns true if the iterator has more steps.
				*/
				virtual bool hasNext() const override
				{
					return !m_list.isEnd(m_pos);
				}

				/*
					Moves the iterator "forward" one step.
				*/
				virtual void next() override
				{
					m_pos = m_list.next(m_pos);
				}

				/*
					Returns a reference to the value at the iterator's position.
				*/
				virtual const T& get() const override
				{
					return m_list.get(m_pos);
				}

			};

		}

	}

}
