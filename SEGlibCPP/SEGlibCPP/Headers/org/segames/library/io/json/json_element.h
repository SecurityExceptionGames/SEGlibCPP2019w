#pragma once
#include <org/segames/library/object.h>
#include <org/segames/library/io/json/json_element_type.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Super class for JSON elements.

				* @author	Philip Rosberg
				* @since	2019-07-02
				* @edited	2019-07-13
			*/
			class JSONElement :
				public Object
			{
			public:

				/*
					Destructor.
				*/
				virtual ~JSONElement();

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const = 0;

				/*
					Wrties the json element using the proper decoration.
					* @param[in] tabs The number of tabs to insert at the front
					* @param[in] output The output stream to write to
				*/
				virtual void write(const int tabs, std::ostream& output) const = 0;

				/*
					Returns a string representation of the object.
				*/
				virtual std::string toString() const override;

			};

		}

	}

}