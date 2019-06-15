#pragma once
#include <org/segames/library/gl/texture/gl_physical_texture.h>
#include <org/segames/library/math/dimension_2.h>

#include <memory>
#include <istream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					A class handling S3 compressed textures stored on the hard drive.
					The first mipmap level is the same as the regular texture level 0.

					* @author	Philip Rosberg
					* @since	2019-06-15
					* @edited	2019-06-15
				*/
				class SEG_API GLS3TCTexture :
					public GLPhysicalTexture
				{
				protected:

					/*
						The number of mipmap levels.
					*/
					int m_mipmapLevels;

					/*
						The sizes of the mipmap levels.
					*/
					std::unique_ptr<math::Dimension2i[]> m_mipmapSizes;

					/*
						The data of the mipmap levels.
					*/
					std::unique_ptr<std::unique_ptr<char[]>[]> m_mipmapData;

					/*
						Returns the four CC code as a OpenGL format.
						* @param[in] fourCC The four CC code from the dds file
					*/
					static GLenum asGLFormat(const int fourCC);

				public:

					/*
						Creates a new S3TC texture.
						* @param[in] path The path to the texture file
					*/
					GLS3TCTexture(const std::string& path);

					/*
						Copy constructor.
						* @param[in] obj The texture to copy
					*/
					GLS3TCTexture(const GLS3TCTexture& obj);

					/*
						Returns the number of mipmap/texture levels.
					*/
					virtual int getNumMipmaps() const;

					/*
						Returns an array of mipmap sizes.
					*/
					virtual const math::Dimension2i* getMipmapSizes() const;

					/*
						Uploads the internally stored data.
					*/
					virtual void upload() override;

					/*
						Imports the data for the texture.
					*/
					virtual void importTexture();

					/*
						Imports the data for the texture.
						* @param[in] path The path to the texture file
					*/
					virtual void importTexture(const std::string& path);

					/*
						Imports the data for the texture.
						* @param[in] input The input stream with texture data
					*/
					virtual void importTexture(std::istream& input);

				};

			}

		}

	}

}