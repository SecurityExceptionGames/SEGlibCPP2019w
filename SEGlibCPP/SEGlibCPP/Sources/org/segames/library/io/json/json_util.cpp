#include <org/segames/library/io/json/json_util.h>
#include <org/segames/library/io/json/json_array.h>
#include <org/segames/library/io/json/json_boolean.h>
#include <org/segames/library/io/json/json_number.h>
#include <org/segames/library/io/json/json_object.h>
#include <org/segames/library/io/json/json_string.h>

#include <cctype>

namespace org
{

	namespace segames
	{

		namespace library
		{

			JSONElement* JSONUtil::read(const File& file)
			{
				std::ifstream input = file.openInputChar();
				return read(input);
			}

			JSONElement* JSONUtil::read(std::istream& input)
			{
				int c;
				int line = 1, lineChar = 1;
				JSONElement* element = nullptr;
				while (std::isspace(c = input.peek()))
				{
					lineChar++;
					if (c == '\n' || c == '\r')
					{
						lineChar = 1;
						line++;
					}
					input.get();
				}

				switch (c)
				{
				case '[':
					input.get();
					element = new JSONArray(input, line, lineChar);
					break; 
				case 'f':
				case 't':
				case 'F':
				case 'T':
					element = new JSONBoolean(input, line, lineChar);
					break;
				case '{':
					input.get();
					element = new JSONObject(input, line, lineChar);
					break;
				case '\"':
					input.get();
					element = new JSONString(input, line, lineChar);
					break;
				default:
					if (!std::isspace(c) && JSONNumber::checkChar(false, c))
						element = new JSONNumber(input, line, lineChar);
					else
						element = nullptr;
					break;
				}

				return element;
			}

			void JSONUtil::write(const JSONElement& element, const File& file)
			{
				std::ofstream output = file.openOutputChar();
				write(element, output);
			}

			void  JSONUtil::write(const JSONElement& element, std::ostream& output)
			{
				element.write(0, output);
			}

		}

	}

}