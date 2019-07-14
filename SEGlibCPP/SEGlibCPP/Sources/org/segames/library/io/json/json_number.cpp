#include <org/segames/library/io/json/json_number.h>
#include <org/segames/library/io/io_exception.h>

#include <cctype>

namespace org
{

	namespace segames
	{

		namespace library
		{

			bool JSONNumber::checkChar(const bool hex, const int c)
			{
				switch (c)
				{
				case EOF:
					throw IOException("EOF reached while evaluating json number.", __FILE__, __LINE__);
				case '+':
				case '-':
				case 'x':
				case 'X':
				case 'e':
				case 'E':
				case '.':
					return true;
				case 'a':
				case 'A':
				case 'b':
				case 'B':
				case 'c':
				case 'C':
				case 'd':
				case 'D':
				case 'f':
				case 'F':
					return hex;
				default:
					if (c >= '0' && c <= '9')
						return true;
					else if (std::isspace(c))
						return true;
					return false;
				}

			}

			JSONNumber::JSONNumber()
			{}

			JSONNumber::JSONNumber(const long long val) :
				m_float(static_cast<double>(val)),
				m_int(val)
			{}

			JSONNumber::JSONNumber(const double val) :
				m_float(val),
				m_int(static_cast<long long>(val))
			{}

			JSONNumber::JSONNumber(std::istream& input, int& line, int& lineChar)
			{
				int c;
				bool isFloat = false, ended = false, hex = false;
				std::string num = "";
				while ((c = input.peek()) != ',' && c != '}' && c != ']')
				{
					bool space;
					lineChar++;
					if (!checkChar(hex, c))
						throw IOException("Unexpected token while evaluating json number at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);
					
					space = std::isspace(c);
					if (space)
						ended = true;
					else if(ended)
						throw IOException("Unexpected token while evaluating json number at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);

					switch (c)
					{
					case '\n':
					case '\r':
						lineChar = 0;
						line++;
						break;
					case 'e':
					case 'E':
					case '.':
						isFloat = true;
						break;
					case 'x':
					case 'X':
						hex = true;
						break;
					default:
						break;
					}

					if (!space)
						num += static_cast<unsigned char>(input.get());
					else
						input.get();
				}

				if (isFloat)
				{
					m_float = std::stod(num);
					m_int = static_cast<long long>(m_float);
				}
				else
				{
					m_int = std::stoll(num);
					m_float = static_cast<double>(m_int);
				}

			}

			JSONElementType JSONNumber::getType() const
			{
				return NUMBER;
			}

			const double& JSONNumber::getNumberf() const
			{
				return m_float;
			}

			const long long& JSONNumber::getNumberi() const
			{
				return m_int;
			}

			void JSONNumber::setNumber(const double val)
			{
				m_float = val;
				m_int = static_cast<long long>(m_float);
			}

			void JSONNumber::setNumber(const long long val)
			{
				m_int = val;
				m_float = static_cast<double>(m_int);
			}

			void JSONNumber::write(const int tabs, std::ostream& output) const
			{
				if (m_float - static_cast<double>(m_int) != 0.0)
					output << std::to_string(m_float);
				else
					output << std::to_string(m_int);
			}

			size_t JSONNumber::hashCode() const
			{
				return *reinterpret_cast<const size_t*>(&m_float);
			}

			bool JSONNumber::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
					return dynamic_cast<const JSONNumber&>(obj).m_float == m_float;
			}

		}

	}

}