#pragma once
#include <org/segames/library/gl/gl_pointer_inf.h>
#include <org/segames/library/gl/gl_data_type.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			typedef void(GLPointerInf::*InfActivateFun)() const;

			/*
				A class for storing the binding of one pointer information object.

				* @author	Philip Rosberg
				* @since	2019-06-10
				* @edited	2019-06-10
			*/
			class SEG_API GLPointerBinding :
				public Object
			{
			protected:

				/*
					The type of the binding.
				*/
				GLDataType m_type;

				/*
					The set[...]Pointer() mehtod from m_inf.
				*/
				InfActivateFun m_infSetMethod;

				/*
					The pointer information.
				*/
				GLPointerInf m_inf;

			public:

				/*
					Creates a new pointer binding.
				*/
				GLPointerBinding();

				/*
					Creates a new pointer information binding of the specified type and information.
					* @param[in] type The type of the binding
					* @param[in] inf The pointer information
				*/
				GLPointerBinding(const GLDataType type, const GLPointerInf& inf);

				/*
					Copy constructor.
					* @param[in] obj The pointer binding to copy
				*/
				GLPointerBinding(const GLPointerBinding& obj);

				/*
					Destructor.
				*/
				virtual ~GLPointerBinding();

				/*
					Returns the type of the binding.
				*/
				virtual GLDataType getType() const;

				/*
					Returns the pointer information.
				*/
				virtual const GLPointerInf& getInf() const;

				/*
					Sets the OpenGL context pointer to the data contained in this instance.
				*/
				virtual void setPointer() const;

				/*
					Sets the OpenGL context pointer to the data contained in this instance for attributes.
					* @param[in] location The location id of the vertex attribute
				*/
				virtual void setPointer(const GLuint location) const;

				/*
					Returns true if the two objects are equal.
					* @param[in] obj The object to compare this one two
				*/
				virtual bool equals(const Object& obj) const override;

			};

		}

	}

}