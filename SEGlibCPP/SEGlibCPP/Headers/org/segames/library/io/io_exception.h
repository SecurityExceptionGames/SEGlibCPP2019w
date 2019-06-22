#pragma once
#include <org/segames/library/exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Super-class for various exceptions during io operations.

				* @author	Philip Rosberg
				* @since	2018-06-08
				* @edited	2018-06-08
			*/
			class SEG_API IOException :
				public Exception
			{
			public:

				/*
					Creates an io-exception exception with message
					* @param[in] message The message to use for the exception
				*/
				explicit IOException(const std::string& message);

				/*
					Creates an io-exception with the given message
					* @param[in] message The message to use for the exception
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				explicit IOException(const std::string& message, const char* file, const int line);

			};

		}

	}

}