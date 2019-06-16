#pragma once
#include <org/segames/library/gl/texture/gl_physical_texture.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					A class handling regular uncompressed textures stored on the hard drive.
					
					* @author	Philip Rosberg
					* @since	2019-06-15
					* @edited	2019-06-15
				*/
				class SEG_API GLDiscTexture :
					public GLPhysicalTexture
				{
				protected:

					/*
						The stored texture data.
					*/
					void* m_data;

				public:

					/*
						Creates an empty disc texture.
					*/
					GLDiscTexture();

					/*
						Creates a new disc texture.
						* @param[in] path The path to the texture file
					*/
					explicit GLDiscTexture(const std::string& path);
					
					/*
						Copy constructor.
						* @param[in] obj The disc texture to copy
					*/
					explicit GLDiscTexture(const GLDiscTexture& obj);

					/*
						Destructor.
					*/
					virtual ~GLDiscTexture();

					/*
						Uploads the internally stored data.
					*/
					virtual void upload() override;

					/*
						Imports the data for the texture.
					*/
					virtual void importTexture() override;

					/*
						Imports the data for the texture.
						* @param[in] forceChannel The amount of channels to force, or 0 to not force
					*/
					virtual void importTexture(const int forceChannel);

					/*
						Imports the data for the texture.
						* @param[in] path The path to the texture file
					*/
					virtual void importTexture(const std::string& path);

					/*
						Imports the data for the texture.
						* @param[in] path The path to the texture file
						* @param[in] forceChannel The amount of channels to force, or 0 to not force
					*/
					virtual void importTexture(const std::string& path, const int forceChannel);

				};

			}

		}

	}

}