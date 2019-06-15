#pragma once
#include <org/segames/library/gl/texture/gl_texture.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					A super class for textures that has a file on the hard drive.

					* @author	Philip Rosberg
					* @since	2019-06-15
					* @edited	2019-06-15
				*/
				class SEG_API GLPhysicalTexture :
					public GLTexture
				{
				protected:

					/*
						The path to the texture file.
					*/
					std::string m_path;

				public:

					/*
						Creates an empty texture.
					*/
					GLPhysicalTexture();

					/*
						Creates a 2D and RGBA texture object of the given size.
						* @param[in] size The size of the texture
					*/
					GLPhysicalTexture(const math::Dimension3i& size);

					/*
						Creates a 2D texture object with the given attributes.
						* @param[in] internalFormat The internal OpenGL format
						* @param[in] size The size of the texture
					*/
					GLPhysicalTexture(const GLenum internalFormat, const math::Dimension3i& size);

					/*
						Creates a texture object with the given attributes.
						* @param[in] type The type of the texture, GL_TEXTURE_2D, etc.
						* @param[in] internalFormat The internal OpenGL format
						* @param[in] format The texture format
						* @param[in] size The size of the texture
					*/
					GLPhysicalTexture(const GLenum type, const GLenum internalFormat, const GLenum format, const math::Dimension3i& size);

					/*
						Returns the path.
					*/
					virtual const std::string& getPath() const;

					/*
						Sets the path to the texture file.
						* @param[in] path The path to the texture file
					*/
					virtual void setPath(const std::string& path);

					/*
						Uploads the internally stored data.
					*/
					virtual void upload() = 0;

				};

			}

		}

	}

}