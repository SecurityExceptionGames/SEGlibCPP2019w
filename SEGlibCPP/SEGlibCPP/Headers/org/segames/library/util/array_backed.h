#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Interface for operations common to array backed types.

				* @author	Philip Rosberg
				* @since	2019-03-17
				* @edited	2019-03-17
			*/
			template<typename T, typename PosType_>
			class ArrayBacked
			{
			public:
				typedef PosType_ PosType;

				/*
					Returns the size of the avaliable part of the backing array.
				*/
				virtual PosType size() const = 0;

				/*
					Returns the pointer to the first element in the avaliable part of the backing array.
				*/
				virtual T* pointer() const = 0;

			};

		}

	}

}