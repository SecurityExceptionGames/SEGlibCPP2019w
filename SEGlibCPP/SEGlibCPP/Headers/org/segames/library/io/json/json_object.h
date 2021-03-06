#pragma once
#include <org/segames/library/io/json/json_element.h>

#include <unordered_map>
#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{
			
			/*
				Class for a JSON object element.

				* @author	Philip Rosberg
				* @since	2019-07-12
				* @edited	2019-07-13
			*/
			class SEG_API JSONObject :
				public JSONElement
			{
			protected:

				/*
					A class used to ensure no memory leaks during a
					failed construction of a json object.

					* @author	Philip Rosberg
					* @since	2019-07-14
					* @edited	2019-07-14
				*/
				class ConstructionSaftey
				{
				protected:

					/*
						Reference to the map of elements.
					*/
					std::unordered_map<std::string, JSONElement*>* m_ptr;

				public:

					/*
						Creates a new construction saftey.
						* @param[in] ptr A reference pointer to the elements
					*/
					ConstructionSaftey(std::unordered_map<std::string, JSONElement*>* ptr);

					/*
						Destructor, also frees data in the referenced pointer.
					*/
					~ConstructionSaftey();

					/*
						Releases the saftey without freeing the data.
					*/
					void release();

				};

				/*
					The elements in the object.
				*/
				std::unordered_map<std::string, JSONElement*> m_elements;

			public:

				/*
					Creates an empty json object.
				*/
				JSONObject();

				/*
					Creates a json object from the input stream.
					* @param[in] input The input stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				explicit JSONObject(std::istream& input, int& line, int& lineChar);

				/*
					Copies the given object (deep copy).
					* @param[in] obj The json object to copy
				*/
				JSONObject(const JSONObject& obj);

				/*
					Destructor.
				*/
				virtual ~JSONObject();

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;

				/*
					Returns the json element with the given name, or null if no such element exists.
					* @param[in] name The identifier name of the element
				*/
				virtual JSONElement* get(const std::string& name) const;

				/*
					Returns the json element of the given type with the given name, or null if no 
					such element exists or if the element with that name is not of the given type.
					* @param[in] name The identifier name of the json element
				*/
				template<typename T>
				T* get(const std::string& name) const;

				/*
					Returns a reference to the mapped elements in the json object.
				*/
				virtual std::unordered_map<std::string, JSONElement*>& getElements();

				/*
					Wrties the json object using the proper decoration.
					* @param[in] tabs The number of tabs to insert at the front
					* @param[in] output The output stream to write to
				*/
				virtual void write(const int tabs, std::ostream& output) const override;

				/*
					Returns true if the the given object is equal to this one.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override;

			};

		}

	}

}