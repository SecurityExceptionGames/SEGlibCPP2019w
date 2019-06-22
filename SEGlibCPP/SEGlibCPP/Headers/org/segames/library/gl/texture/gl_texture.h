#pragma once
#include <org/segames/library/gl/gl_bindable.h>
#include <org/segames/library/math/dimension_3.h>
#include <org/segames/library/object.h>

#include <glad/glad.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A super class for OpenGL textures.

				* @author	Philip Rosberg
				* @since	2019-06-13
				* @edited	2019-06-13
			*/
			class SEG_API GLTexture :
				public GLBindable,
				public Object
			{
			private:

				/*
					The OpenGL max texture size.s
				*/
				static int m_glMaxTextureSize;

			protected:

				/*
					The texture id.
				*/
				GLuint m_id;

				/*
					The texture type, GL_TEXTURE_2D, etc.
				*/
				GLenum m_type;

				/*
					The internal OpenGL format.
				*/
				GLenum m_internalFormat;

				/*
					The texture format.
				*/
				GLenum m_format;

				/*
					The size of the texture.
				*/
				Dimension3i m_size;

				/*
					Returns a format approximation of the given internal format.
					* @param[in] internalFormat The internal OpenGL format
				*/
				static GLenum formatFromInternalFormat(const GLenum internalFormat);

			public:

				/*
					Creates an empty texture.
				*/
				GLTexture();

				/*
					Creates a 2D and RGBA texture object of the given size.
					* @param[in] size The size of the texture
				*/
				explicit GLTexture(const Dimension3i& size);

				/*
					Creates a 2D texture object with the given attributes.
					* @param[in] internalFormat The internal OpenGL format
					* @param[in] size The size of the texture
				*/
				explicit GLTexture(const GLenum internalFormat, const Dimension3i& size);

				/*
					Creates a texture object with the given attributes.
					* @param[in] type The type of the texture, GL_TEXTURE_2D, etc.
					* @param[in] internalFormat The internal OpenGL format
					* @param[in] format The texture format
					* @param[in] size The size of the texture
				*/
				explicit GLTexture(const GLenum type, const GLenum internalFormat, const GLenum format, const Dimension3i& size);
					
				/*
					Destructor.
					Handles release of OpenGL resources.
				*/
				virtual ~GLTexture();

				/*
					Returns the texture id.
				*/
				virtual GLuint getID() const;

				/*
					Returns the texture type.
				*/
				virtual GLenum getType() const;

				/*
					Returns the OpenGL internal texture format.
				*/
				virtual GLenum getInternalFormat() const;

				/*
					Returns the texture format.
				*/
				virtual GLenum getFormat() const;

				/*
					Returns the size of the texture.
				*/
				virtual const Dimension3i& getSize() const;

				/*
					Sets the internally stored size of the texture.
					NOTE! This does not change the texture stored on the graphics card and should therefore be used with caution.
					* @param[in] size The new size of the texture object
				*/
				virtual void setSize(const Dimension3i& size);

				/*
					Binds this texture.
				*/
				virtual const GLTexture& bind() const override;

				/*
					Releases this texture.
				*/
				virtual const GLTexture& release() const override;

				/*
					Generates mipmap levels for the texture.
					NOTE! This feature uses OpenGL 3.0.
				*/
				virtual const GLTexture& generateMipMap() const;

				/*
					Sets the OpenGL usage parameters of the texture.
					* @param[in] wrapping The texture lookup wrapping, GL_REPEAT, GL_CLAMP etc.
					* @param[in] minFilter The minifying filter GL_LINEAR, GL_NEAREST etc.
					* @param[in] magFilter The magnifying filter GL_LINEAR, GL_NEAREST etc.
				*/
				virtual const GLTexture& setParameters(const GLenum wrapping, const GLenum minFilter, const GLenum magFilter) const;

				/*
					Uploads the given data.
					* @param[in] storage The storage format, GL_UNSIGNED_BYTE etc.
					* @param[in] data The texture data to upload
				*/
				virtual void upload(const GLenum storage, const void* data);

				/*
					Returns the OpenGL maximum texture size.
					Loads the size from OpenGL on first call.
				*/
				static int glMaxTextureSize();

			};

		}

	}

}