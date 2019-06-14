#pragma once
#include <org/segames/library/gl/gl_buffer.h>
#include <org/segames/library/util/array_list.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					An OpenGL buffer object with a backing ArrayList.
					Any OpenGL resource is deallocated on deletion of this object.

					* @author	Philip Rosberg
					* @since	2019-06-10
					* @edited	2019-06-10
				*/
				template<typename T>
				class GLBackedBuffer :
					public GLBuffer,
					public util::ArrayList<T>
				{
				public:

					/*
						Creates a new backed buffer object.
					*/
					GLBackedBuffer() :
						GLBuffer(),
						util::ArrayList<T>()
					{}

					/*
						Creates a new backed buffer object with the given initial capacity.
						* @param[in] capacity The initial capacity of the backing ArrayList
					*/
					explicit GLBackedBuffer(const typename util::ArrayList<T>::PosType capacity) :
						GLBuffer(),
						util::ArrayList<T>(capacity)
					{}

					/*
						Creates a new backed buffer object with the given information.
						* @param[in] type The type of the buffer data, ie. how to use the buffer
						* @param[in] inf The pointer information
					*/
					explicit GLBackedBuffer(const GLDataType type, const GLPointerInf& inf) :
						GLBuffer(type, inf),
						util::ArrayList<T>()
					{}

					/*
						Creates a new backed buffer object with the given information and initial capacity.
						* @param[in] capacity The initial capacity of the backing ArrayList
						* @param[in] type The type of the buffer data, ie. how to use the buffer
						* @param[in] inf The pointer information
					*/
					explicit GLBackedBuffer(const typename util::ArrayList<T>::PosType capacity, const GLDataType type, const GLPointerInf& inf) :
						GLBuffer(type, inf),
						util::ArrayList<T>(capacity)
					{}

					/*
						Returns the number of elements uploaded in the last upload, 0 if no upload has occured.
					*/
					virtual GLsizeiptr getUploadCount() const
					{
						return getUploadLength() / sizeof(T);
					}

					/*
						Binds this buffer to the OpenGL context.
					*/
					virtual const GLBackedBuffer& bind() const override
					{
						GLBuffer::bind();
						return *this;
					}

					/*
						Releases this buffer (all buffers) from the OpenGL context.
					*/
					virtual const GLBackedBuffer& release() const override
					{
						GLBuffer::release();
						return *this;
					}

					/*
						Chainable add method. Adds the given value to the backing ArrayList.
						* @param[in] value The value to add
					*/
					virtual GLBackedBuffer& push(const T& value)
					{
						util::ArrayList<T>::add(value);
						return *this;
					}

					/*
						Uploads the internally stored data.
					*/
					virtual void upload()
					{
						upload(GL_STATIC_DRAW);
					}

					/*
						Uploads the internally stored data with the given buffer mode.
						* @param[in] mode The buffer mode, GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc.
					*/
					virtual void upload(const GLenum mode)
					{
						GLBuffer::upload(util::ArrayList<T>::size() * sizeof(T), util::ArrayList<T>::pointer(), mode);
						util::ArrayList<T>::clear();
					}

				};

#ifndef SEG_API_GL_NO_TYPEDEFS

				using GLDoubleBuffer = GLBackedBuffer<GLdouble>;
				using GLFloatBuffer = GLBackedBuffer<GLfloat>;
				using GLLongBuffer = GLBackedBuffer<GLint64>;
				using GLIntBuffer = GLBackedBuffer<GLint>;
				using GLShortBuffer = GLBackedBuffer<GLshort>;
				
#endif

			}

		}

	}

}