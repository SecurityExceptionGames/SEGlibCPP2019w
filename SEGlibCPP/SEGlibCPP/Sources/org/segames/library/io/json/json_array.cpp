#include <org/segames/library/io/json/json_array.h>
#include <org/segames/library/io/json/json_boolean.h>
#include <org/segames/library/io/json/json_number.h>
#include <org/segames/library/io/json/json_object.h>
#include <org/segames/library/io/json/json_string.h>
#include <org/segames/library/io/io_exception.h>

#include <cctype>

namespace org
{

	namespace segames
	{

		namespace library
		{

			JSONArray::ConstructionSaftey::ConstructionSaftey(ArrayList<JSONElement*>* ptr) :
				m_ptr(ptr)
			{}

			JSONArray::ConstructionSaftey::~ConstructionSaftey()
			{
				if (m_ptr)
					for (int i = 0; i < m_ptr->size(); i++)
						if (m_ptr->get(i))
							delete m_ptr->get(i);
			}

			void JSONArray::ConstructionSaftey::release()
			{
				m_ptr = nullptr;
			}

			JSONArray::JSONArray()
			{}

			JSONArray::JSONArray(std::istream& input, int& line, int& lineChar)
			{
				bool expectingMore = false;
				int c, state = 0;
				JSONElement* element = nullptr;
				ConstructionSaftey saftey(&m_elements);
				while ((c = input.peek()) != ']')
				{
					if (c == EOF)
						throw IOException("EOF reached while evaluating json array.", __FILE__, __LINE__);

					lineChar++;
					if (c == '\n' || c == '\r')
					{
						lineChar = 0;
						line++;
					}

					switch (state)
					{
					case 0: // Parse element
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
							{
								element = nullptr;
								input.get();
							}
							break;
						}

						if (element)
						{
							m_elements.add(element);
							state = 1;
							expectingMore = false;
						}
						break;
					case 1: // Check comma
						if (c == ',')
						{
							state = 0;
							expectingMore = true;
						}
						else if (!std::isspace(c))
							throw IOException("Unexpected token while evaluating json array at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ", expected ',' or end of array.", __FILE__, __LINE__);
						input.get();
						break;
					default:
						break;
					}

				}

				if (expectingMore)
					throw IOException("Unexpected end of array while evaluating json array at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);
				input.get(); // Remove ']'

				m_elements.compact();
				saftey.release();
			}

			JSONArray::JSONArray(const JSONArray& obj) :
				m_elements(obj.m_elements.size())
			{
				for (int i = 0; i < obj.m_elements.size(); i++)
					switch (obj.m_elements.get(i)->getType())
					{
					case OBJECT:
						m_elements.add(new JSONObject(*dynamic_cast<JSONObject*>(obj.m_elements.get(i))));
						break;
					case ARRAY:
						m_elements.add(new JSONArray(*dynamic_cast<JSONArray*>(obj.m_elements.get(i))));
						break;
					case STRING:
						m_elements.add(new JSONString(*dynamic_cast<JSONString*>(obj.m_elements.get(i))));
						break;
					case NUMBER:
						m_elements.add(new JSONNumber(*dynamic_cast<JSONNumber*>(obj.m_elements.get(i))));
						break;
					case BOOLEAN:
						m_elements.add(new JSONBoolean(*dynamic_cast<JSONBoolean*>(obj.m_elements.get(i))));
						break;
					default:
						break;
					}
			}

			JSONArray::~JSONArray()
			{
				for (int i = 0; i < m_elements.size(); i++)
					if (m_elements.get(i))
						delete m_elements.get(i);
			}

			JSONElementType JSONArray::getType() const
			{
				return ARRAY;
			}

			int JSONArray::size() const
			{
				return m_elements.size();
			}

			JSONElement* JSONArray::get(const int index) const
			{
				return m_elements.get(index);
			}
			
			template<>
			JSONArray* JSONArray::get(const int index) const
			{
				JSONElement* element = get(index);
				if (element)
					return (element->getType() == ARRAY ? dynamic_cast<JSONArray*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONBoolean* JSONArray::get(const int index) const
			{
				JSONElement* element = get(index);
				if (element)
					return (element->getType() == BOOLEAN ? dynamic_cast<JSONBoolean*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONNumber* JSONArray::get(const int index) const
			{
				JSONElement* element = get(index);
				if (element)
					return (element->getType() == NUMBER ? dynamic_cast<JSONNumber*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONObject* JSONArray::get(const int index) const
			{
				JSONElement* element = get(index);
				if (element)
					return (element->getType() == OBJECT ? dynamic_cast<JSONObject*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONString* JSONArray::get(const int index) const
			{
				JSONElement* element = get(index);
				if (element)
					return (element->getType() == STRING ? dynamic_cast<JSONString*>(element) : nullptr);
				else
					return nullptr;
			}

			ArrayList<JSONElement*>& JSONArray::getElements()
			{
				return m_elements;
			}
			
			void JSONArray::write(const int tabs, std::ostream& output) const
			{
				int written = 0;
				output << "[\n";
				for (int i = 0; i < m_elements.size(); i++)
				{
					if (m_elements.get(i))
					{
						for (int t = 0; t < tabs + 1; t++)
							output << '\t';

						m_elements.get(i)->write(tabs + 1, output);
						
						if (written < m_elements.size() - 1)
							output << ',';
						output << '\n';
					}
					written++;
				}
				for (int t = 0; t < tabs; t++)
					output << '\t';
				output << ']';
			}

			bool JSONArray::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
				{
					const JSONArray& ref = dynamic_cast<const JSONArray&>(obj);

					if (ref.m_elements.size() != m_elements.size())
						return false;

					for (int i = 0; i < m_elements.size(); i++)
					{
						JSONElement* element = get(i);
						JSONElement* refElement = ref.get(i);
						if ((element == nullptr) != (refElement == nullptr))
							return false;

						if (element != nullptr)
							if (*element != *refElement)
								return false;
					}

					return true;
				}

			}

		}

	}

}