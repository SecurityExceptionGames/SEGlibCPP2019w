#include <org/segames/library/io/io_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			IOException::IOException(const std::string& message) :
				Exception(message)
			{}

			IOException::IOException(const std::string& message, const char* file, const int line) :
				Exception(message, file, line)
			{}

		}

	}

}
