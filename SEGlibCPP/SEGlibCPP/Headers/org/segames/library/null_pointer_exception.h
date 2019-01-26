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
					Creates a null pointer exception with no message
					* @param[in] message The message to use for the exception
				*/
				NullPointerException(const std::string& message);

			};

		}

	}

}