#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Interface for a generic set type.

					* @author	Philip Rosberg
					* @since	2019-03-17
					* @edited	2019-03-17
				*/
				template<typename T>
				class Set
				{
				public:

					/*
						Returns true if the set is empty
					*/
					virtual bool isEmpty() const = 0;


				};

			}

		}

	}

}
