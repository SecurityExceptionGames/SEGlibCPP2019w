#pragma once
#include <org/segames/library/io/json/json_element.h>
#include <org/segames/library/util/array_list.h>

#include <iostream>


namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Class for a JSON array/list element.

				* @author	Philip Rosberg
				* @since	2019-07-12
				* @edited	2019-07-13
			*/
			class SEG_API JSONArray :
				public JSONElement
			{
			protected:

				/*
					A class used to ensure no memory leaks during a 
					failed construction of a json array.

					* @author	Philip Rosberg
					* @since	2019-07-14
					* @edited	2019-07-14
				*/
				class ConstructionSaftey
				{
				protected:

					/*
						Reference to the array/list of elements.
					*/
					ArrayList<JSONElement*>* m_ptr;

				public:

					/*
						Creates a new construction saftey.
						* @param[in] ptr A reference pointer to the elements
					*/
					ConstructionSaftey(ArrayList<JSONElement*>* ptr);

					/*
						Destructor, also frees data in the referenced pointer.
					*/
					~ConstructionSaftey();

					/*
						Releases the saftey without freeing the data.
					*/
					void release();

				};

			protected:

				/*
					The backing array.
				*/
				ArrayList<JSONElement*> m_elements;

			public:

				/*
					Creates an empty json array.
				*/
				JSONArray();

				/*
					Creates a json array from the input stream.
					* @param[in] input The input stream to read from
					* @param[in/out] line The line number
					* @param[in/out] lineChar The character number on a line
				*/
				explicit JSONArray(std::istream& input, int& line, int& lineChar);

				/*
					Copies the given json array (deep copy).
					* @param[in] obj The json array to copy
				*/
				JSONArray(const JSONArray& obj);

				/*
					Destructor.
				*/
				virtual ~JSONArray();

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;

				/*
					Returns the size of the json array.
				*/
				virtual int size() const;

				/*
					Returns the json element with the given index.
					* @param[in] index The index in the array of the element
				*/
				virtual JSONElement* get(const int index) const;

				/*
					Returns the json element of the given type with the given index, or null if 
					the element with that name is not of the given type.
					* @param[in] index The index in the array of the element
				*/
				template<typename T>
				T* get(const int index) const;
				
				/*
					Returns the backing arraylist of elements.
				*/
				virtual ArrayList<JSONElement*>& getElements();

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