#include <org/segames/library/invalid_value_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			InvalidValueException::InvalidValueException() :
				Exception()
			{}

			InvalidValueException::InvalidValueException(const std::string& message) :
				Exception(message)
			{}

			InvalidValueException::InvalidValueException(const std::string& message, const char* file, const int line) :
				Exception(message, file, line)
			{}

		}

	}

}