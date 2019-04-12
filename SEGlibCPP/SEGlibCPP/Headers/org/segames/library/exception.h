#pragma once
#include <org\segames\library\object.h>

#include <exception>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Root class for exception type hierarchy

				* @author	Philip Rosberg
				* @since	2018-05-09
				* @edited	2019-03-17
			*/
			class SEG_API Exception :
				public Object,
				private std::exception
			{
			protected:

				/*
					True if the exception has a message to display
				*/
				bool m_hasMessage;

				/*
					The message of the exception
				*/
				std::string m_message;

			public:

				/*
					Creates an exception with no message
				*/
				Exception();

				/*
					Creates an exception with the given message
					* @param[in] message The message to use for the exception
				*/
				Exception(const std::string& message);

				/*
					Creates an exception with the given message
					* @param[in] message The message to use for the exception
					* @param[in] file The file in which the exception was thrown
					* @param[in] line The line at which the exception was thrown
				*/
				Exception(const std::string& message, const char* file, const int line);

				/*
					Returns the exception message
				*/
				virtual const char* what() const noexcept;

				/*
					Prints the exception to the std::cout stream
				*/
				virtual void print() const;

				/*
					Prints the exception to the given stream
					* @param[in] stream The stream to print the exception to
				*/
				virtual void print(const std::ostream& stream) const;

				/*
					Returns a string representation of the exception object
				*/
				virtual std::string toString() const;

				/*
					Returns true if the the given object is equal to this one
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const;

			};

		}

	}

}