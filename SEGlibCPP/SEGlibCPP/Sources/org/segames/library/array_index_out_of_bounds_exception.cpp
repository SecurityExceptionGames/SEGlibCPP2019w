#include <org/segames/library/array_index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException() :
				IndexOutOfBoundsException("")
			{}

			ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const size_t index) :
				IndexOutOfBoundsException("Array index out of range: " + std::to_string(index))
			{}

			ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const size_t index, const char* file, const int line) :
				IndexOutOfBoundsException("Array index out of range: " + std::to_string(index), file, line)
			{}

		}

	}

}