#include <org/segames/library/gl/texture/gl_disc_texture.h>
#include <org/segames/library/io/file_not_found_exception.h>
#include <org/segames/library/io/file.h>

#include <stb/stb_image.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLDiscTexture::GLDiscTexture() :
				GLPhysicalTexture(),
				m_data(nullptr)
			{}
				
			GLDiscTexture::GLDiscTexture(const std::string& path) :
				GLPhysicalTexture(),
				m_data(nullptr)
			{
				GLPhysicalTexture::setPath(path);
			}

			GLDiscTexture::GLDiscTexture(const GLDiscTexture& obj) :
				GLPhysicalTexture(obj),
				m_data(nullptr)
			{
				GLPhysicalTexture::setPath(obj.m_path);
			}

			GLDiscTexture::~GLDiscTexture()
			{
				if (m_data)
					stbi_image_free(m_data);
			}

			void GLDiscTexture::upload()
			{
				GLTexture::upload(GL_UNSIGNED_BYTE, m_data);
				if (m_data)
				{
					stbi_image_free(m_data);
					m_data = nullptr;
				}

			}

			void GLDiscTexture::importTexture()
			{
				importTexture(0);
			}

			void GLDiscTexture::importTexture(const int forceChannel)
			{
				importTexture(m_path, forceChannel);
			}

			void GLDiscTexture::importTexture(const std::string& path)
			{
				importTexture(path, 0);
			}

			void GLDiscTexture::importTexture(const std::string& path, const int forceChannel)
			{
				File file(path);
				if (!file.exists())
					throw FileNotFoundException(path, __FILE__, __LINE__);

				int x, y, c;
				stbi_uc* data = stbi_load(path.c_str(), &x, &y, &c, forceChannel);
				if (data)
				{
					if(m_data)
						stbi_image_free(m_data);
					m_data = data;
					m_size = Dimension3i(x, y, 1);
						
					const int channels = forceChannel ? forceChannel : c;
					switch (channels)
					{
					case 1:
						m_internalFormat = GL_R8;
						break;
					case 2:
						m_internalFormat = GL_RG8;
						break;
					case 3:
						m_internalFormat = GL_RGB8;
						break;
					default:
						m_internalFormat = GL_RGBA8;
						break;
					}

					m_format = GLTexture::formatFromInternalFormat(m_internalFormat);
					m_type = GL_TEXTURE_2D;
				}

			}

		}

	}

}