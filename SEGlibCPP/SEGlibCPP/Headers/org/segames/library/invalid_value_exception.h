#pragma once
#include <org/segames/library/exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Exception for invalid values

				* @author	Philip Rosberg
				* @since	2018-06-08
				* @edited	2018-06-08
			*/
			class SEG_API InvalidValueException :
				public Exception
			{
			public:

				/*
					Creates an  invalid value exception with no message
				*/
				InvalidValueException();

				/*
					Creates an  invalid value exception with the given message
					* @param[in] message The message to use for the exception
				*/
				InvalidValueException(const std::string& message);

			};

		}

	}

}