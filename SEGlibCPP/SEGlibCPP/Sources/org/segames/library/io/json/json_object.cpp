#include <org/segames/library/io/json/json_object.h>
#include <org/segames/library/io/json/json_array.h>
#include <org/segames/library/io/json/json_boolean.h>
#include <org/segames/library/io/json/json_number.h>
#include <org/segames/library/io/json/json_string.h>
#include <org/segames/library/io/io_exception.h>

#include <cctype>
#include <sstream>

namespace org
{

	namespace segames
	{

		namespace library
		{
			
			JSONObject::ConstructionSaftey::ConstructionSaftey(std::unordered_map<std::string, JSONElement*>* ptr) :
				m_ptr(ptr)
			{}

			JSONObject::ConstructionSaftey::~ConstructionSaftey()
			{
				if (m_ptr)
					for (auto itr = m_ptr->begin(); itr != m_ptr->end(); itr++)
						if (itr->second)
							delete itr->second;
			}

			void JSONObject::ConstructionSaftey::release()
			{
				m_ptr = nullptr;
			}

			JSONObject::JSONObject()
			{}

			JSONObject::JSONObject(std::istream& input, int& line, int& lineChar)
			{
				bool expectingMore = false;
				int c, state = 0;
				std::string name;
				JSONElement* element;
				ConstructionSaftey saftey(&m_elements);
				while ((c = input.peek()) != '}')
				{
					if(c == EOF)
						throw IOException("EOF reached while evaluating json object.", __FILE__, __LINE__);

					lineChar++;
					if (c == '\n' || c == '\r')
					{
						lineChar = 0;
						line++;
					}

					switch (state)
					{
					case 0: // Parse element name
						input.get();
						if (c == '\"')
						{
							name = JSONString::readJSONString(input, line, lineChar);
							state = 1;
							expectingMore = true;
						}
						else if (!std::isspace(c))
							throw IOException("Unexpected token while evaluating json object at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ", expected '\"'.", __FILE__, __LINE__);
						break;
					case 1: // Check colon
						if (c == ':')
							state = 2;
						else if(!std::isspace(c))
							throw IOException("Unexpected token while evaluating json object at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ", expected ':'.", __FILE__, __LINE__);
						input.get();
						break;
					case 2: // Parse element
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
							m_elements.insert(std::pair<std::string, JSONElement*>(name, element));
							state = 3;
							expectingMore = false;
						}
						break;
					case 3: // Check comma
						if (c == ',')
						{
							state = 0;
							expectingMore = true;
						}
						else if(!std::isspace(c))
							throw IOException("Unexpected token while evaluating json object at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ", expected ',' or end of object.", __FILE__, __LINE__);
						input.get();
						break;
					default:
						break;
					}

				}

				if (expectingMore)
					throw IOException("Unexpected end of object while evaluating json object at line " + std::to_string(line) + ":" + std::to_string(lineChar) + ".", __FILE__, __LINE__);
				input.get(); // Remove '}'
				saftey.release();
			}

			JSONObject::JSONObject(const JSONObject& obj)
			{
				m_elements.reserve(obj.m_elements.size());
				for (auto itr = obj.m_elements.begin(); itr != obj.m_elements.end(); itr++)
					switch (itr->second->getType())
					{
					case OBJECT:
						m_elements.insert(std::pair<std::string, JSONElement*>(itr->first, new JSONObject(*dynamic_cast<JSONObject*>(itr->second))));
						break;
					case ARRAY:
						m_elements.insert(std::pair<std::string, JSONElement*>(itr->first, new JSONArray(*dynamic_cast<JSONArray*>(itr->second))));
						break;
					case STRING:
						m_elements.insert(std::pair<std::string, JSONElement*>(itr->first, new JSONString(*dynamic_cast<JSONString*>(itr->second))));
						break;
					case NUMBER:
						m_elements.insert(std::pair<std::string, JSONElement*>(itr->first, new JSONNumber(*dynamic_cast<JSONNumber*>(itr->second))));
						break;
					case BOOLEAN:
						m_elements.insert(std::pair<std::string, JSONElement*>(itr->first, new JSONBoolean(*dynamic_cast<JSONBoolean*>(itr->second))));
						break;
					default:
						break;
					}
			}

			JSONObject::~JSONObject()
			{
				for (auto itr = m_elements.begin(); itr != m_elements.end(); itr++)
					if (itr->second)
						delete itr->second;
			}

			JSONElementType JSONObject::getType() const
			{
				return OBJECT;
			}

			JSONElement* JSONObject::get(const std::string& name) const
			{
				auto itr = m_elements.find(name);
				if (itr != m_elements.end())
					return itr->second;
				else
					return nullptr;
			}

			template<>
			JSONArray* JSONObject::get(const std::string& name) const
			{
				JSONElement* element = get(name);
				if (element)
					return (element->getType() == ARRAY ? dynamic_cast<JSONArray*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONBoolean* JSONObject::get(const std::string& name) const
			{
				JSONElement* element = get(name);
				if (element)
					return (element->getType() == BOOLEAN ? dynamic_cast<JSONBoolean*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONNumber* JSONObject::get(const std::string& name) const
			{
				JSONElement* element = get(name);
				if (element)
					return (element->getType() == NUMBER ? dynamic_cast<JSONNumber*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONObject* JSONObject::get(const std::string& name) const
			{
				JSONElement* element = get(name);
				if (element)
					return (element->getType() == OBJECT ? dynamic_cast<JSONObject*>(element) : nullptr);
				else
					return nullptr;
			}

			template<>
			JSONString* JSONObject::get(const std::string& name) const
			{
				JSONElement* element = get(name);
				if (element)
					return (element->getType() == STRING ? dynamic_cast<JSONString*>(element) : nullptr);
				else
					return nullptr;
			}

			std::unordered_map<std::string, JSONElement*>& JSONObject::getElements()
			{
				return m_elements;
			}

			void JSONObject::write(const int tabs, std::ostream& output) const
			{
				int written = 0;
				output << "{\n";
				for (auto itr = m_elements.begin(); itr != m_elements.end(); itr++)
				{
					if (itr->second)
					{
						for (int t = 0; t < tabs + 1; t++)
							output << '\t';

						output << '\"' << itr->first << "\": ";
						itr->second->write(tabs + 1, output);

						if (written < static_cast<int>(m_elements.size()) - 1)
							output << ',';
						output << '\n';
					}
					written++;
				}
				for (int t = 0; t < tabs; t++)
					output << '\t';
				output << '}';
			}

			bool JSONObject::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
				{
					const JSONObject& ref = dynamic_cast<const JSONObject&>(obj);
					
					if (ref.m_elements.size() != m_elements.size())
						return false;

					for (auto itr = m_elements.begin(); itr != m_elements.end(); itr++)
					{
						JSONElement* refElement = ref.get(itr->first);
						if ((itr->second == nullptr) != (refElement == nullptr))
							return false;

						if (itr->second != nullptr)
							if (*itr->second != *refElement)
								return false;
					}

					return true;
				}

			}

		}

	}

}