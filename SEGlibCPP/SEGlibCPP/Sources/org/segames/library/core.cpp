#include <org/segames/library/core.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			bool Core::printTime = true;
			std::istream* Core::in = &std::cin;
			std::ostream* Core::err = &std::cerr;
			std::ostream* Core::warn = &std::cout;
			std::ostream* Core::out = &std::cout;
			const std::string* const Core::labels = new std::string[4]{
				" [Info]   ",
				"<Warning> ",
				"<<ERROR>> ",
				" *Note*   "
			};

			void Core::printlnInternal(const PrintLabel label, const std::string& message, std::ostream& stream)
			{
				if (label != PrintLabel::NONE)
					stream << labels[(size_t)label].c_str() << message.c_str() << std::endl;
				else
					stream << message.c_str() << std::endl;
			}

			std::istream& Core::getIn()
			{
				return *in;
			}

			std::ostream& Core::getErr()
			{
				return *err;
			}

			std::ostream& Core::getWarn()
			{
				return *warn;
			}

			std::ostream& Core::getOut()
			{
				return *out;
			}

			void Core::setIn(std::istream& in_)
			{
				in = &in_;
			}

			void Core::setErr(std::ostream& err_)
			{
				err = &err_;
			}

			void Core::setWarn(std::ostream& warn_)
			{
				warn = &warn_;
			}

			void Core::setOut(std::ostream& out_)
			{
				out = &out_;
			}

			void Core::setAllOut(std::ostream& out_)
			{
				setErr(out_);
				setWarn(out_);
				setOut(out_);
			}

			void Core::setPrintTime(const bool flag)
			{
				printTime = flag;
			}

			void Core::println(const std::string& message)
			{
				println(PrintLabel::NONE, message);
			}

			void Core::println(const PrintLabel label, const std::string& message)
			{
				switch (label)
				{
				case PrintLabel::WARNING:
					if (warn)
						printlnInternal(label, message, getWarn());
					else
						printlnInternal(label, message, getOut());
					break;
				case PrintLabel::ERROR:
					if (err)
						printlnInternal(label, message, getErr());
					else
						printlnInternal(label, message, getOut());
					break;
				default:
					printlnInternal(label, message, getOut());
					break;
				}

			}

		}

	}

}