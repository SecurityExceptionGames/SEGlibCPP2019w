#pragma once
#include <org/segames/library/io/json/json_element.h>

#include <unordered_map>

namespace org
{

	namespace segames
	{

		namespace library
		{
			
			/*
				Class for a JSON object element.

				* @author	Philip Rosberg
				* @since	2019-07-02
				* @edited	2019-07-02
			*/
			class SEG_API JSONObject :
				public JSONElement
			{
			protected:

				/*
					The elements in the object.
				*/
				std::unordered_map<std::string, JSONElement*> m_elements;

			public:

				/*
					Returns the element type.
				*/
				virtual JSONElementType getType() const override;

			};

		}

	}

}