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
				explicit IndexOutOfBoundsException(const std::string& message);

				/*
					Creates an index out of bounds exception with the given message
					* @param[in] message The message to use for the exception
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				explicit IndexOutOfBoundsException(const std::string& message, const char* file, const int line);

			};

		}

	}

}