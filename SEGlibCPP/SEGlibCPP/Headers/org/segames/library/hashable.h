#pragma once
#include <org/segames/library/dllmain.h>

#include <string>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Interface for all things hashable.

				* @author	Philip Rosberg
				* @since	2019-03-17
				* @edited	2019-03-17
			*/
			class SEG_API Hashable
			{
			public:

				/*
					Returns a hash code representation of the object.
				*/
				virtual size_t hashCode() const = 0;

				/*
					Calculates a hash code representation of the given hashable object.
					* @param[in] obj The hashable object to calculate the hash from
				*/
				static size_t hashCode(const Hashable& obj);
			
				/*
					Calculates a hash code representation of the given string.
					* @param[in] str The null terminated c-string to calculate a hash from
				*/
				static size_t hashCode(const char* str);

				/*
					Calculates a hash code representation of the given string.
					* @param[in] str The string to calculate a hash from
				*/
				static size_t hashCode(const std::string& str);

				/*
					Calculates a hash code representation of the given variable.
					This is just a pass-through function to allow most standard types
					such as int, short etc. to just use their regular value as a hash.
					* @param[in] var The variable to "calculate a hash from"
				*/
				template<typename T>
				static size_t hashCode(const T& var)
				{
					return (size_t)var;
				}

			};

		}

	}

}