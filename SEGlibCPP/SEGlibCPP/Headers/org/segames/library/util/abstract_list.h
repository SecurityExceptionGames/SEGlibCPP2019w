#pragma once
#include <org/segames/library/util/list.h>
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
					Abstract super-class for various lists.

					* @author	Philip Rosberg
					* @since	2019-03-16
					* @edited	2019-03-16
				*/
				template<typename T, typename PosType_ = size_t>
				class AbstractList :
					public Object,
					public List<T, PosType_>
				{
				public:
					using typename List<T, PosType_>::PosType;

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
						Removes the element at the given position.
						* @param[in] pos The position in the list
					*/
					virtual T remove(const PosType pos) = 0;

					/*
						Removes all content from the list.
					*/
					virtual void clear() = 0;

					/*
						Returns true if the the given object is equal to this list.
						Time complexity is at worst O(n).
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const
					{
						if (typeid(obj) == typeid(*this))
						{
							PosType pos, listPos;
							AbstractList<T, PosType>& list = (AbstractList<T, PosType>&)obj;

							pos = first();
							listPos = list.first();

							while (!isEnd(pos) && !list.isEnd(listPos))
							{
								if (get(pos) != list.get(listPos))
									return false;

								pos = next(pos);
								listPos = list.next(listPos);
							}

							if (!isEnd(pos))
								return false;
							else if (!list.isEnd(listPos))
								return false;

							return true;
						}
						return false;
					}

					/*
						Returns a string representation of the list.
					*/
					virtual std::string toString() const
					{
						std::string out = "[ ";
						PosType pos = first();

						if (!isEnd(pos))
						{
							out += std::to_string(get(pos));
							pos = next(pos);
						}

						while (!isEnd(pos))
						{
							out += ", " + std::to_string(get(pos));
							pos = next(pos);
						}

						return out + " ]";
					}

				};

			}

		}

	}

}
