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
				A class for a JSON number element.

				* @author	Philip Rosberg
				* @since	2019-07-03
				* @edited	2019-07-03
			*/
			class SEG_API JSONNumber :
				public JSONElement
			{
			protected:

				/*
					Floating point value of the number.
				*/
				double m_float;

				/*
					Integer value of the number.
				*/
				long long m_int;

				/*
					Checks if the given character is allowed in a number.
					* @param[in] c The character to check
				*/
				static bool checkChar(const int c);

			public:

				/*
					Creates an empty json number.
				*/
				JSONNumber();

				/*
					Creates a json number with the given value.
					* @param[in] val The value of the json number
				*/
				explicit JSONNumber(const long long val);

				/*
					Creates a json number with the given value.
					* @param[in] val The value of the json number
				*/
				explicit JSONNumber(const double val);

				/*
					Creates a json number from the input stream.
					* @param[in] input The input stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				explicit JSONNumber(std::istream& input, int& line, int& lineChar);

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;

				/*
					Returns a reference to the contained floating point value.
				*/
				virtual const double& getNumberf() const;
				
				/*
					Returns a reference to the contained integer value.
				*/
				virtual const long long& getNumberi() const;

				/*
					Sets the json number.
					* @param[in] val The value to set
				*/
				virtual void setNumber(const double val);

				/*
					Sets the json number.
					* @param[in] val The value to set
				*/
				virtual void setNumber(const long long val);

				/*
					Wrties the json number using the proper decoration.
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

			};

		}

	}

}