#pragma once
#include <org/segames/library/exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Exception thrown for indices out of bounds

				* @author	Philip Rosberg
				* @since	2018-05-11
				* @edited	2018-05-11
			*/
			class SEG_API IndexOutOfBoundsException :
				public Exception
			{
			public:

				/*
					Creates an index out of bounds exception with no message
				*/
				IndexOutOfBoundsException();

				/*
					Creates an index out of bounds exception with the given message
					* @param[in] message The message to use for the exception
				*/
				IndexOutOfBoundsException(const std::string& message);

			};

		}

	}

}