#pragma once
#include <org/segames/library/io/json/json_element.h>
#include <org/segames/library/io/file.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A class/namespace for reading and writing json.

				* @author	Philip Rosberg
				* @since	2019-07-12
				* @edited	2019-07-12
			*/
			class SEG_API JSONUtil final
			{
			private:

				/*
					Ensure no instance of the class.
				*/
				JSONUtil();

			public:

				/*
					Parses json from the given file, returns null if no json was found.
					* @param[in] file The file to read from
				*/
				static JSONElement* read(const File& file);

				/*
					Parses json from the given stream, returns null if no json was found.
					* @param[in] input The stream to read from
				*/
				static JSONElement* read(std::istream& input);

				/*
					Writes the json element (and all sub elements) to the given file.
					NOTE! The file must exist or this method will throw a file not found exception.
					* @param[in] element The json element to write to the file
					* @param[in] file The file to write to
				*/
				static void write(const JSONElement& element, const File& file);

				/*
					Writes the json element (and all sub elements) to the given stream.
					* @param[in] element The json element to write to the stream
					* @param[in] output The output stream to write to
				*/
				static void write(const JSONElement& element, std::ostream& output);

			};

		}

	}

}