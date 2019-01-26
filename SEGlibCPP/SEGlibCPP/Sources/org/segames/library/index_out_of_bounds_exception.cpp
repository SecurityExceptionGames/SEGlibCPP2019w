#include <org/segames/library/index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			IndexOutOfBoundsException::IndexOutOfBoundsException() :
				IndexOutOfBoundsException("")
			{}

			IndexOutOfBoundsException::IndexOutOfBoundsException(const std::string& message) :
				Exception(message.c_str())
			{}

		}

	}

}