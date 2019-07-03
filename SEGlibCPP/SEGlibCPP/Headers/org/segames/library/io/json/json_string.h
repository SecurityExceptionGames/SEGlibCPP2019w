#pragma once
#include <org/segames/library/io/json/json_element.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class for a JSON string element.

				* @author	Philip Rosberg
				* @since	2019-07-02
				* @edited	2019-07-02
			*/
			class SEG_API JSONString :
				public JSONElement
			{
			protected:

				/*
					The wrapped string.
				*/
				std::string m_string;

				/*
					Reads the escape sequence from the stream and adds it to the string.
					* @param[in] input The stream to read from
					* @param[out] str The string to write to
				*/
				static void evalEscapeSequence(std::istream& input, std::string& str);

			public:

				/*
					Creates an empty json string.
				*/
				JSONString();

				/*
					Creates a json string from the given string.
					* @param[in] str The string to store
				*/
				explicit JSONString(const std::string& str);

				/*
					Creates a json string by reading from the given stream.
					* @param[in] input The stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				explicit JSONString(std::istream& input, int& line, int& lineChar);

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;
				
				/*
					Returns a reference to the contained string.
				*/
				virtual const std::string& getString() const;

				/*
					Sets the stored string.
					* @param[in] str The string to set the stored one to
				*/
				virtual void setString(const std::string& str);

				/*
					Wrties the json string using the proper decoration.
					* @param[in] output The output stream to write to
				*/
				virtual void write(std::ostream& output);

				/*
					Returns a hash-code for the object.
				*/
				virtual size_t hashCode() const override;

				/*
					Returns a string representation of the object.
				*/
				virtual std::string toString() const;

				/*
					Returns true if the the given object is equal to this one.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const;

				/*
					Reads a json string by reading from the given stream.
					* @param[in] input The stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				static std::string readJSONString(std::istream& input, int& line, int& lineChar);

			};

		}

	}

}