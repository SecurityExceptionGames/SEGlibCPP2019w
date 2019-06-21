#pragma once
#include <org/segames/library/dllmain.h>

#include <iostream>

#ifdef ERROR
#undef ERROR
#ifndef WIN_ERROR
#define WIN_ERROR 0
#endif
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Field storing library core variables and functions.

				* @author	Philip Rosberg
				* @since	2018-10-26
				* @edited	2018-10-26
			*/
			class SEG_API Core final
			{
			public:

				/*
					The enum of labels to write at the start of the print.

					* @author	Philip Rosberg
					* @since	2018-10-27
					* @edited	2018-10-27
				*/
				enum class PrintLabel
				{
					NONE = -1,
					INFO = 0,
					WARNING = 1,
					ERROR = 2,
					NOTIFICATION = 3
				};

			private:
				/*
					True if the time should be printed.
				*/
				static bool printTime;

				/*
					The standard input stream.
				*/
				static std::istream* in;

				/*
					The standard output stream for errors.
				*/
				static std::ostream* err;

				/*
					The standard output stream for warnings.
				*/
				static std::ostream* warn;

				/*
					The standard output stream.
				*/
				static std::ostream* out;

				/*
					The message labels.
				*/
				static const std::string* const labels;

				/*
					Prints the given message with the given label to the given stream.
					* @param[in] label The label to print
					* @param[in] message The message to print
					* @param[in] stream The stream to print to
				*/
				static void printlnInternal(const PrintLabel label, const std::string& message, std::ostream& stream);

			public:

				/*
					Returns a reference to the standard input stream.
				*/
				static std::istream& getIn();

				/*
					Returns a reference to the standard output stream for errors.
				*/
				static std::ostream& getErr();

				/*
					Returns a reference to the standard output stream for warnings.
				*/
				static std::ostream& getWarn();

				/*
					Returns a reference to the standard output stream.
				*/
				static std::ostream& getOut();

				/*
					Sets the standard input stream.
					* @param[in] in The standard input stream
				*/
				static void setIn(std::istream& in);

				/*
					Sets the standard error output stream.
					* @param[in] err The standard error output stream
				*/
				static void setErr(std::ostream& err);

				/*
					Sets the standard warning output stream.
					* @param[in] warn The standard warning output stream
				*/
				static void setWarn(std::ostream& warn);

				/*
					Sets the standard output stream.
					* @param[in] out The standard output stream
				*/
				static void setOut(std::ostream& out);

				/*
					Sets the output stream for errors, warnings and standard output.
					* @param[in] out The output stream for errors, warnings and standard output
				*/
				static void setAllOut(std::ostream& out);

				/*
					Sets if the time should be printed.
					* @param[in] flag True if the time should be printed
				*/
				static void setPrintTime(const bool flag);

				/*
					Prints the given message with the INFO label.
					* @param[in] message The message to print
				*/
				static void println(const std::string& message);

				/*
					Prints the given message with the given label.
					* @param[in] label The label to print
					* @param[in] message The message to print
				*/
				static void println(const PrintLabel label, const std::string& message);
				
				/*
					Prints the stack trace to the given output stream.
					* @param[in] out The stream to write the stack trace to
					* @param[in] offset The offset level of the start of the stack trace, defaults to 1
				*/
				static void getStackTrace(std::ostream& out, const int offset);

			};

		}

	}

}