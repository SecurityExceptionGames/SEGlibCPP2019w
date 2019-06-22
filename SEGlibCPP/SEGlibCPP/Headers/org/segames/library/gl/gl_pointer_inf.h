#pragma once
#include <org/segames/library/object.h>

#include <glad/glad.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A storage type for specifying data pointer information.

				* @author	Philip Rosberg
				* @since	2019-06-03
				* @edited	2019-06-03
			*/
			class SEG_API GLPointerInf :
				public Object
			{
			private:

				/*
					True if the values should be normalized before access (only attributes)
				*/
				GLboolean m_normalized;

				/*
					The type of the data, GL_FLOAT, GL_INTEGER etc.
				*/
				GLenum m_type;

				/*
					Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				*/
				GLint m_size;

				/*
					Specifies the byte offset between consecutive vertices. If stride is 0, the vertices are understood to be tightly packed in the array.
				*/
				GLint m_stride;

				/*
					The offset of the first piece of data in the buffer.
				*/
				size_t m_offset;

			public:

				/*
					Creates an empty/zeroed information.
				*/
				GLPointerInf();

				/*
					Creates a new pointer information object.
					* @param[in] type The type of data, GL_FLOAT, GL_INTEGER etc.
					* @param[in] size Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
					* @param[in] stride Specifies the byte offset between consecutive vertices. If stride is 0, the vertices are understood to be tightly packed in the array.
					* @param[in] offset The offset of the first piece of data in the buffer
				*/
				explicit GLPointerInf(const GLenum type, const GLint size, const GLint stride, const size_t offset);

				/*
					Creates a new pointer information object for a vertex attribute.
					* @param[in] normalized True if the values should be normalized before access
					* @param[in] type The type of data, GL_FLOAT, GL_INTEGER etc.
					* @param[in] size Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
					* @param[in] stride Specifies the byte offset between consecutive vertices. If stride is 0, the vertices are understood to be tightly packed in the array.
					* @param[in] offset The offset of the first piece of data in the buffer
				*/
				explicit GLPointerInf(const GLboolean normalized, const GLenum type, const GLint size, const GLint stride, const size_t offset);

				/*
					Returns true if the values should be normalized before access (only attributes)
				*/
				virtual GLboolean normalized() const;

				/*
					Returns the type of data, GL_FLOAT, GL_INTEGER etc.
				*/
				virtual GLenum getType() const;

				/*
					Returns the the number of components per generic vertex attribute.
				*/
				virtual GLint getSize() const;

				/*
					Returns the byte offset between consecutive vertices. If stride is 0, the vertices are understood to be tightly packed in the array.
				*/
				virtual GLint getStride() const;

				/*
					Returns the offset of the first piece of data in the buffer.
				*/
				virtual GLint getOffset() const;

				/*
					Sets the OpenGL vertex pointer information.
				*/
				virtual void setVertexPointer() const;

				/*
					Sets the OpenGL normal pointer information.
				*/
				virtual void setNormalPointer() const;

				/*
					Sets the OpenGL color pointer information.
				*/
				virtual void setColorPointer() const;

				/*
					Sets the OpenGL texture coordinate pointer information.
				*/
				virtual void setTexCoordPointer() const;

				/*
					Sets the OpenGL vertex attribute pointer information.
					* @param[in] location The location id of the vertex attribute
				*/
				virtual void setAttribPointer(const GLuint location) const;

				/*
					Sets the OpenGL index pointer information.
				*/
				virtual void setIndexPointer() const;

				/*
					Sets the OpenGL edge flag pointer information.
				*/
				virtual void setEdgeFlagPointer() const;

				/*
					Returns true if the the given object is equal to this one.
					* @param[in] obj The object to check
				*/
				virtual bool equals(const Object& obj) const override;

			public:

				/*
					Standard configuration for a 1D float array.
				*/
				static GLPointerInf ONE_FLOAT_POINTER;

				/*
					Standard configuration for a 2D float array.
				*/
				static GLPointerInf TWO_FLOAT_POINTER;

				/*
					Standard configuration for a 3D float array.
				*/
				static GLPointerInf THREE_FLOAT_POINTER;

				/*
					Standard configuration for a 4D float array.
				*/
				static GLPointerInf FOUR_FLOAT_POINTER;

				/*
					Standard configuration for a 1D integer array.
				*/
				static GLPointerInf ONE_INT_POINTER;

				/*
					Standard configuration for a 2D integer array.
				*/
				static GLPointerInf TWO_INT_POINTER;

				/*
					Standard configuration for a 3D integer array.
				*/
				static GLPointerInf THREE_INT_POINTER;

				/*
					Standard configuration for a 4D integer array.
				*/
				static GLPointerInf FOUR_INT_POINTER;

			};

		}

	}

}