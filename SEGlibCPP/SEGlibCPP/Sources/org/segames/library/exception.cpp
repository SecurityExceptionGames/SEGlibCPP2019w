#include <org/segames/library/exception.h>

#include <org/segames/library/core.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			Exception::Exception() :
				Exception("")
			{}

			Exception::Exception(const std::string& message_) :
				hasMessage(message_.length() != 0),
				message(message_)
			{}

			const char* Exception::what() const noexcept
			{
				if (hasMessage)
					return message.c_str();
				return nullptr;
			}

			void Exception::print() const
			{
				print(Core::getErr());
			}

			void Exception::print(const std::ostream& stream) const
			{
				((std::ostream&)stream) << toString() << std::endl;
			}

			std::string Exception::toString() const
			{
				if (hasMessage)
					return std::string(typeid(*this).name() + 6) + ": " + what();
				return std::string(typeid(*this).name() + 6);
			}

			bool Exception::equals(const Object& obj) const
			{
				if (typeid(obj) == typeid(*this))
					return std::string(((Exception&)obj).what()) == what();
				return Object::equals(obj);
			}

		}

	}

}