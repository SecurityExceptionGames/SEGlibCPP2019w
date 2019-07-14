#include <org/segames/library/io/json/json_string.h>
#include <org/segames/library/io/io_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void JSONString::evalEscapeSequence(std::istream& input, std::string& str)
			{
				int c = input.get();
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

			void JSONString::write(const int tabs, std::ostream& output) const
			{
				output << '\"';
				for (auto itr = m_string.begin(); itr != m_string.end(); itr++)
				{
					char c = *itr;
					switch (c)
					{
					case '\"':
						output << "\\\"";
						break;
					case '\\':
						output << "\\\\";
						break;
					case '\b':
						output << "\\b";
						break;
					case '\f':
						output << "\\f";
						break;
					case '\n':
						output << "\\n";
						break;
					case '\r':
						output << "\\r";
						break;
					case '\t':
						output << "\\t";
						break;
					default:
						output << c;
						break;
					}

				}
				output << '\"';
			}

			size_t JSONString::hashCode() const
			{
				return Hashable::hashCode(m_string);
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
						str += static_cast<char>(static_cast<unsigned char>(c));
						break;
					}
					
				}

				return str;
			}

		}

	}

}