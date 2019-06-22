#pragma once
#include <org/segames/library/util/iterator.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An interface for classes that can return iterators.

				* @author	Philip Rosberg
				* @since	2019-03-23
				* @edited	2019-03-23
			*/
			template<typename T, typename Itr>
			class Iterable
			{
			public:

				/*
					Returns an iterator on its first step.
				*/
				virtual Itr begin() const = 0;

				/*
					Marker method to make for(x:y)-loops work.
				*/
				virtual Itr end() const
				{
					return begin();
				}

			};

		}

	}

}
