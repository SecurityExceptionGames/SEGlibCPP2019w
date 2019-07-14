#include <org/segames/library/io/json/json_element.h>

#include <sstream>

namespace org
{

	namespace segames
	{

		namespace library
		{
			
			JSONElement::~JSONElement()
			{}

			std::string JSONElement::toString() const
			{
				std::stringstream output;
				write(0, output);
				return output.str();
			}

		}

	}

}