#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					An interface for a standard iterator.

					* @author	Philip Rosberg
					* @since	2019-03-21
					* @edited	2019-03-21
				*/
				template<typename T>
				class Iterator
				{
				public:

					/*
						Returns true if the iterator has more steps.
					*/
					virtual bool hasNext() const = 0;

					/*
						Moves the iterator "forward" one step.
					*/
					virtual void next() = 0;

					/*
						Returns a reference to the value at the iterator's position.
					*/
					virtual const T& get() const = 0;

				public:

					/*
						Increment operator override
					*/
					virtual void operator++() final
					{
						next();
					}

					/*
						Second increment operator override
					*/
					virtual void operator++(int) final
					{
						next();
					}

					/*
						Dereference operator override
					*/
					virtual const T& operator*() const final
					{
						return get();
					}

				};

				/*
					Inequallity operator override
				*/
				template<typename T, typename V>
				inline bool operator!=(const Iterator<T>& a, const V& b)
				{
					return a.hasNext();
				}

			}

		}

	}

}