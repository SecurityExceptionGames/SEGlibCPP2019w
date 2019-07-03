#include <org/segames/library/io/json/json_string.h>
#include <org/segames/library/io/io_exception.h>
#include <org/segames/library/util/utf8_iterator.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void JSONString::evalEscapeSequence(std::istream& input, std::string& str)
			{
				int c = input.get();
				unsigned int unicode = 0;
				if (c == EOF)
					throw IOException("EOF reached while evaluating an escape sequence in a JSON string/name.", __FILE__, __LINE__);

				switch (c)
				{
				case '"':
					str += '\"';
					break;
				case '\\':
					str += '\\';
					break;
				case '/':
					str += '/';
					break;
				case 'b':
					str += '\b';
					break;
				case 'f':
					str += '\f';
					break;
				case 'n':
					str += '\n';
					break;
				case 'r':
					str += '\r';
					break;
				case 't':
					str += '\t';
					break;
				case 'u':
					for (int i = 0; i < 4; i++)
					{
						c = input.get();
						if (c == EOF)
							throw IOException("EOF reached while evaluating an escape sequence in a JSON string/name.", __FILE__, __LINE__);
						
						if (c >= '0' && c <= '9')
							unicode |= ((c - '0') << i * 16);
						else if (c >= 'A' && c <= 'F')
							unicode |= ((c - 'A' + 10) << i * 16);
					}
					UTF8Iterator::codepointToString(unicode, str);
					break;
				default:
					break;
				}

			}

			JSONString::JSONString()
			{}

			JSONString::JSONString(const std::string& str) :
				m_string(str)
			{}

			JSONString::JSONString(std::istream& input, int& line, int& lineChar) :
				m_string(readJSONString(input, line, lineChar))
			{}

			JSONElementType JSONString::getType() const
			{
				return STRING;
			}

			const std::string& JSONString::getString() const
			{
				return m_string;
			}

			void JSONString::setString(const std::string& str)
			{
				m_string = str;
			}

			void JSONString::write(std::ostream& output)
			{
				output << "\"" << m_string << "\"";
			}

			size_t JSONString::hashCode() const
			{
				return Hashable::hashCode(m_string);
			}

			std::string JSONString::toString() const
			{
				return "\"" + m_string + "\"";
			}

			bool JSONString::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
					return dynamic_cast<const JSONString&>(obj).m_string == m_string;
			}

			std::string JSONString::readJSONString(std::istream& input, int& line, int& lineChar)
			{
				int c;
				std::string str = "";
				while ((c = input.get()) != '\"')
				{
					lineChar++;
					switch (c)
					{
					case EOF:
						throw IOException("EOF reached while evaluating JSON string.", __FILE__, __LINE__);
					case '\\':
						evalEscapeSequence(input, str);
						break;
					case '\b':
					case '\f':
					case '\t':
						break;
					case '\n':
					case '\r':
						lineChar = 0;
						line++;
						break;
					default:
						str += static_cast<unsigned char>(c);
						break;
					}

				}

				return str;
			}

		}

	}

}