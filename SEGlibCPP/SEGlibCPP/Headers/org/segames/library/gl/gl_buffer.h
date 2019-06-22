#pragma once
#include <org/segames/library/gl/gl_bindable.h>
#include <org/segames/library/gl/gl_pointer_binding.h>
#include <org/segames/library/util/array_list.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A standard OpenGL buffer object.
				Any OpenGL resource is deallocated on deletion of this object.
				
				* @author	Philip Rosberg
				* @since	2019-06-10
				* @edited	2019-06-10
			*/
			class SEG_API GLBuffer :
				public GLBindable,
				public Object
			{
			protected:

				/*
					The id of the buffer.
				*/
				GLuint m_id;

				/*
					The buffer type.
				*/
				GLenum m_bufferType;

				/*
					The buffer upload length in bytes.
				*/
				GLsizeiptr m_uploadLength;

				/*
					The pointer information bindings.
				*/
				ArrayList<GLPointerBinding*> m_infBindings;

			public:

				/*
					Creates a new buffer object.
				*/
				GLBuffer();

				/*
					Creates a new buffer object with the given information.
					* @param[in] type The type of the buffer data, ie. how to use the buffer
					* @param[in] inf The pointer information
				*/
				GLBuffer(const GLDataType type, const GLPointerInf& inf);

				/*
					Destructor.
					Handles release of OpenGL resources.
				*/
				virtual ~GLBuffer();

				/*
					Returns the id of the buffer.
				*/
				virtual GLuint getID() const;

				/*
					Returns the type of the buffer.
				*/
				virtual GLenum getBufferType() const;

				/*
					Returns the length, in bytes, of the last uploaded version of the buffer, 0 if no upload has occured.
				*/
				virtual GLsizeiptr getUploadLength() const;

				/*
					Binds this buffer to the OpenGL context.
				*/
				virtual const GLBuffer& bind() const override;

				/*
					Releases this buffer (all buffers) from the OpenGL context.
				*/
				virtual const GLBuffer& release() const override;

				/*
					Sets the pointer information for OpenGL.
					This method will throw an exception if no pointer binding is set.
				*/
				virtual const GLBuffer& setPointerInf() const;

				/*
					Sets the pointer information for the given buffer data type.
					For attributes, use setPointerInf(const GLDataType, const GLPointerInf&, const GLuint).
					* @param[in] type The type of the buffer data, ie. how to use the buffer
					* @param[in] inf The pointer information
				*/
				virtual GLBuffer& setPointerBinding(const GLDataType type, const GLPointerInf& inf);

				/*
					Sets the pointer information for the given buffer data type. Attributes.
					* @param[in] type The type of the buffer data, ie. how to use the buffer
					* @param[in] inf The pointer information
					* @param[in] location The attribute location
				*/
				virtual GLBuffer& setPointerBinding(const GLDataType type, const GLPointerInf& inf, const GLuint location);

				/*
					Removes the pointer information of the given type.
					For attributes, use removePointerInf(const GLDataType, const GLuint).
					* @param[in] type The type of the buffer data, ie. how to use the buffer
				*/
				virtual GLBuffer& removePointerBinding(const GLDataType type);

				/*
					Removes the pointer information of the given type. Attributes.
					* @param[in] type The type of the buffer data, ie. how to use the buffer
					* @param[in] location The attribute location
				*/
				virtual GLBuffer& removePointerBinding(const GLDataType type, const GLuint location);

				/*
					Uploads the given data to the buffer.
					* @param[in] len the length of the data
					* @param[in] data Pointer to the block of data to upload
				*/
				virtual void upload(const GLsizeiptr len, const void* data);

				/*
					Uploads the given data to the buffer.
					* @param[in] len the length of the data
					* @param[in] data Pointer to the block of data to upload
					* @param[in] mode The buffer mode, GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc.
				*/
				virtual void upload(const GLsizeiptr len, const void* data, const GLenum mode);

				/*
					Returns true if the given object is equal to this buffer.
					* @param[in] obj The object to check if equal to this buffer
				*/
				virtual bool equals(const Object& obj) const override;

			};

		}

	}

}