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

			Exception::Exception(const std::string& message) :
				m_hasMessage(message.length() != 0),
				m_message(message)
			{}

			Exception::Exception(const std::string& message, const char* file, const int line) :
				Exception(message + "\n\tat " + file + ":" + std::to_string(line))
			{}

			const char* Exception::what() const noexcept
			{
				if (m_hasMessage)
					return m_message.c_str();
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
				//23 is a magical number, or something
				if (m_hasMessage)
					return std::string(typeid(*this).name() + 23) + ": " + what();
				return std::string(typeid(*this).name() + 23);
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