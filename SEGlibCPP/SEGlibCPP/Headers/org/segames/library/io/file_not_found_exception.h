#pragma once
#include <org/segames/library/io/io_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An exception for missing files that should not be missing.

				* @author	Philip Rosberg
				* @since	2018-06-05
				* @edited	2018-06-08
			*/
			class SEG_API FileNotFoundException :
				public IOException
			{
			public:

				/*
					Creates a null pointer exception with no message.
					* @param[in] path The path to the file that could not be found
				*/
				explicit FileNotFoundException(const std::string& path);

				/*
					Creates a null pointer exception with the given message.
					* @param[in] path The path to the file that could not be found
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				explicit FileNotFoundException(const std::string& path, const char* file, const int line);

			};

		}

	}

}