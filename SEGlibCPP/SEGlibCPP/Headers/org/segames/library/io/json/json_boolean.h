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
				A class for a JSON boolean element.

				* @author	Philip Rosberg
				* @since	2019-07-03
				* @edited	2019-07-13
			*/
			class SEG_API JSONBoolean :
				public JSONElement
			{
			protected:

				/*
					The boolean value.
				*/
				bool m_flag;

				/*
					Checks if the given character is allowed in a boolean.
					* @param[in] c The character to check
				*/
				static bool checkChar(const int c);

			public:

				/*
					Creates an empty json boolean.
				*/
				JSONBoolean();

				/*
					Sets the value of the json boolean.
					* @param[in] flag The boolean value to set
				*/
				explicit JSONBoolean(const bool flag);

				/*
					Creates a json boolean from the input stream.
					* @param[in] input The input stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				explicit JSONBoolean(std::istream& input, int& line, int& lineChar);

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;

				/*
					Returns the value of the json boolean.
				*/
				virtual bool getBoolean() const;

				/*
					Sets the boolean value.
					* @param[in] flag The boolean value
				*/
				virtual void setBoolean(const bool flag);
				
				/*
					Wrties the json boolean using the proper decoration.
					* @param[in] tabs The number of tabs to insert at the front
					* @param[in] output The output stream to write to
				*/
				virtual void write(const int tabs, std::ostream& output) const override;

				/*
					Returns a hash-code for the object.
				*/
				virtual size_t hashCode() const override;

				/*
					Returns true if the the given object is equal to this one.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override;

			};

		}

	}

}