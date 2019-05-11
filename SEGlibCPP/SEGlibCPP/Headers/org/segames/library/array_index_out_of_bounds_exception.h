#pragma once
#include <org/segames/library/index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Exception thrown for indices out of bounds in arrays

				* @author	Philip Rosberg
				* @since	2018-05-11
				* @edited	2019-03-17
			*/
			class SEG_API ArrayIndexOutOfBoundsException :
				public IndexOutOfBoundsException
			{
			public:

				/*
					Creates an array index out of bounds exception with no message
				*/
				ArrayIndexOutOfBoundsException();

				/*
					Creates an array index out of bounds exception displaying the given index as the one out of bounds
					* @param[in] index The index to display as out of bounds
				*/
				explicit ArrayIndexOutOfBoundsException(const size_t index);

				/*
					Creates a null pointer exception with the given message
					* @param[in] index The index to display as out of bounds
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				explicit ArrayIndexOutOfBoundsException(const size_t index, const char* file, const int line);

			};

		}

	}

}