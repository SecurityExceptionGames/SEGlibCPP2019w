#pragma once
#include <org/segames/library/dllmain.h>
#include <org/segames/library/library.h>

#include <string>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Root object for the segames class hierarchy

				* @author	Philip Rosberg
				* @since	2018-05-08
				* @edited	2018-05-09
			*/
			class SEG_API Object
			{
			public:

				/*
					Returns a hash-code for the object
					If not overridden, default is determined from the object memory
				*/
				virtual size_t hashCode() const;

				/*
					Returns a string representation of the object
				*/
				virtual std::string toString() const;

				/*
					Returns true if the the given object is equal to this one
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const;

				/*
					Returns true if the the given object is equal to this one, calls the equals() method
					* @param[in] obj The object to check
				*/
				virtual bool operator==(const Object& obj) const;

				/*
					Returns true if the the given object is not equal to this one, inverse of operator==
					* @param[in] obj The object to check
				*/
				virtual bool operator!=(const Object& obj) const;

				/*
					Writes the string representation of this object to the given output stream
					* @param[in] out The output stream to write to
				*/
				virtual std::ostream& operator<<(std::ostream& out) const;

			};

			/*
				Writes the string representation of the given object to the given output stream
				* @param[in] out The output stream to write to
				* @param[in] object The object to print
			*/
			SEG_API std::ostream& operator<<(std::ostream& out, const Object& object);

		}

	}

}