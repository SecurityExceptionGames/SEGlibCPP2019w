#include <org/segames/library/io/file_not_found_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			FileNotFoundException::FileNotFoundException(const std::string& path) :
				IOException("File \"" + path + "\" could not be found.")
			{}

			FileNotFoundException::FileNotFoundException(const std::string& path, const char* file, const int line) :
				IOException("File \"" + path + "\" could not be found.", file, line)
			{}

		}

	}

}