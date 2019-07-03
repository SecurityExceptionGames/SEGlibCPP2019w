#include <org/segames/library/object.h>

#include <iostream>
#include <bitset>

namespace org
{

	namespace segames
	{

		namespace library
		{

			size_t Object::hashCode() const
			{
				return typeid(*this).hash_code();
			}

			std::string Object::toString() const
			{
				return std::string(typeid(*this).name()) + "#" + std::to_string(hashCode());
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

namespace std
{

	std::string to_string(const org::segames::library::Object& obj)
	{
		return obj.toString();
	}

}