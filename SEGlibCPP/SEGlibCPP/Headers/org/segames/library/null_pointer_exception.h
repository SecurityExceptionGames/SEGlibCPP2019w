#pragma once
#include <org/segames/library/exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An exception for null pointers, ie. NULL or nullptr, where a non-null pointer is expected

				* @author	Philip Rosberg
				* @since	2018-05-11
				* @edited	2018-05-11
			*/
			class SEG_API NullPointerException :
				public Exception
			{
			public:

				/*
					Creates a null pointer exception with no message
				*/
				NullPointerException();

				/*
					Creates a null pointer exception with message
					* @param[in] message The message to use for the exception
				*/
				explicit NullPointerException(const std::string& message);

				/*
					Creates a null pointer exception with the given message
					* @param[in] message The message to use for the exception
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				explicit NullPointerException(const std::string& message, const char* file, const int line);

			};

		}

	}

}