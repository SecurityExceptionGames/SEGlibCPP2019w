#include <org/segames/library/io/json/json_boolean.h>
#include <org/segames/library/io/io_exception.h>

#include <cctype>

namespace org
{

	namespace segames
	{

		namespace library
		{

			bool JSONBoolean::checkChar(const int c)
			{
				switch (c)
				{
				case EOF:
					throw IOException("EOF reached while evaluating json boolean.", __FILE__, __LINE__);
				case 't':
				case 'T':
				case 'r':
				case 'R':
				case 'u':
				case 'U':
				case 'e':
				case 'E':
				case 'f':
				case 'F':
				case 'a':
				case 'A':
				case 'l':
				case 'L':
				case 's':
				case 'S':
					return true;
				default:
					if (std::isspace(c))
						return true;
					return false;
				}

			}

			JSONBoolean::JSONBoolean()
			{}

			JSONBoolean::JSONBoolean(const bool flag) :
				m_flag(flag)
			{}

			JSONBoolean::JSONBoolean(std::istream& input, int& line, int& lineChar)
			{
				int c;
				bool ended = false;
				std::string str = "";
				while ((c = input.peek()) != ',' || c != '}' || c != ']')
				{
					bool space;
					lineChar++;
					if (!checkChar(c))
						throw IOException("Unexpected token while evaluating json boolean at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);

					space = std::isspace(c);
					if (space)
						ended = true;
					else if (ended)
						throw IOException("Unexpected token while evaluating json boolean at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);

					switch (c)
					{
					case '\n':
					case '\r':
						lineChar = 0;
						line++;
						break;
					default:
						break;
					}

					if (!space)
						str += static_cast<unsigned char>(std::tolower(input.get()));
				}
				
				if (str == "true")
					m_flag = true;
				else
					m_flag = false;
			}

		}

	}

}