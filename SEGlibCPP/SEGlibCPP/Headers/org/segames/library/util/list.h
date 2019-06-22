#pragma once
#include <cstddef>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Interface for a generic list type.

				* @author	Philip Rosberg
				* @since	2019-03-15
				* @edited	2019-03-15
			*/
			template<typename T, typename PosType_ = size_t>
			class List
			{
			public:
				typedef PosType_ PosType;

				/*
					Returns true if the list is empty.
				*/
				virtual bool isEmpty() const = 0;

				/*
					Returns true if the given position is at the end of the list.
					* @param[in] pos The position in the list
				*/
				virtual bool isEnd(const PosType pos) const = 0;

				/*
					Returns a reference to the value at the given position.
					* @param[in] pos The position in the list
				*/
				virtual T& get(const PosType pos) const = 0;

				/*
					Returns the first position for iteration in the list.
				*/
				virtual PosType first() const = 0;

				/*
					Returns the next position in the list.
					* @param[in] pos The position in the list
				*/
				virtual PosType next(const PosType pos) const = 0;

				/*
					Adds the given value to the list.
					* @param[in] value The value to add
				*/
				virtual PosType add(const T& value) = 0;

				/*
					Inserts the given value at the given position.
					* @param[in] pos The position to insert at
					* @param[in] value The value to insert
				*/
				virtual PosType insert(const PosType pos, const T& value) = 0;

				/*
					Sets the value of the element at the given position.
					Returns the value that previously existed at that position.
					* @param[in] pos The position to set the value at
					* @param[in] value The value to set
				*/
				virtual T set(const PosType pos, const T& value) = 0;

				/*
					Removes the element at the given position.
					* @param[in] pos The position in the list
				*/
				virtual T remove(const PosType pos) = 0;

				/*
					Removes all content from the list.
				*/
				virtual void clear() = 0;

			};

		}

	}

}
