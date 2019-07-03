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
				* @edited	2019-07-02
			*/
			class JSONElement :
				public Object
			{
			public:

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const = 0;

			};

		}

	}

}