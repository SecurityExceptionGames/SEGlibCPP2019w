#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			size_t Object::hashCode() const
			{
				size_t code = 0;
				char* ptr = (char*)this;
				for (int i = 0; i < (int)sizeof(*this); i++)
				{
					size_t addend = *ptr;
					for (int e = 0; e < i; e++)
						addend *= *ptr;
					code += addend;

					ptr++;
				}
				return code;
			}

			std::string Object::toString() const
			{
				return std::string(typeid(*this).name()) + "@" + std::to_string(hashCode());
			}

			bool Object::equals(const Object& obj) const
			{
				return typeid(obj) == typeid(*this);
			}

			bool Object::operator==(const Object& obj) const
			{
				return equals(obj);
			}

			bool Object::operator!=(const Object& obj) const
			{
				return !(*this == obj);
			}

			std::ostream& Object::operator<<(std::ostream& out) const
			{
				return (out << toString());
			}

			std::ostream& operator<<(std::ostream& out, const Object& object)
			{
				out << object.toString();
				return out;
			}

		}

	}

}