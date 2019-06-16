#pragma once
#include <org/segames/library/gl/texture/gl_physical_texture.h>

#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					A texture class capable of detecting physical texture type and using the proper loading.

					* @author	Philip Rosberg
					* @since	2019-06-16
					* @edited	2019-06-16
				*/
				class SEG_API GLPhysicalTextureWrapper :
					public GLPhysicalTexture
				{
				public:

					/*
						The detected texture type.
					*/
					enum TextureType
					{
						DISC_TEXTURE,
						S3TC_TEXTURE
					};

				protected:

					/*
						The texture type being used.
					*/
					TextureType m_texType;

					/*
						The texture.
					*/
					std::unique_ptr<GLPhysicalTexture> m_texture;

					/*
						Returns the type of texture from the given path.
						* @param[in] path The path to the texture file
					*/
					static TextureType determineTypeFrom(const std::string& path);

				public:

					/*
						Creates an empty texture wrapper.
					*/
					GLPhysicalTextureWrapper();

					/*
						Creates a texture wrapper with the given path.
						* @param[in] path The path to the texture file
					*/
					explicit GLPhysicalTextureWrapper(const std::string& path);

					/*
						Copy constructor.
						* @param[in] obj The texture to copy
					*/
					explicit GLPhysicalTextureWrapper(const GLPhysicalTextureWrapper& obj);

					/*
						Returns the type of texture being used.
					*/
					virtual TextureType getTextureType() const;

					/*
						Returns the backing texture.
					*/
					virtual GLPhysicalTexture* getTexture() const;

					/*
						Sets the path to the texture file.
						* @param[in] path The path to the texture file
					*/
					virtual void setPath(const std::string& path) override;

					/*
						Binds this texture.
					*/
					virtual const GLPhysicalTextureWrapper& bind() const override;

					/*
						Releases this texture.
					*/
					virtual const GLPhysicalTextureWrapper& release() const override;

					/*
						Uploads the texture data.
					*/
					virtual void upload() override;

					/*
						Imports the data for the texture.
					*/
					virtual void importTexture() override;

					/*
						Imports the data for the texture.
						* @param[in] path The path to the texture file
					*/
					virtual void importTexture(const std::string& path);

				};

			}

		}

	}

}