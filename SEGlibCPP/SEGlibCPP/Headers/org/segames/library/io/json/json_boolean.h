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
				* @edited	2019-07-03
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

			};

		}

	}

}