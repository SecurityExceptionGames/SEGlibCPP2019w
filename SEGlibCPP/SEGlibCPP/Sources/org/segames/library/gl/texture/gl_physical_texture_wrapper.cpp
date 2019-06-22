#include <org/segames/library/gl/texture/gl_physical_texture_wrapper.h>
#include <org/segames/library/gl/texture/gl_disc_texture.h>
#include <org/segames/library/gl/texture/gl_s3tc_texture.h>
#include <org/segames/library/util/string_util.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLPhysicalTextureWrapper::TextureType GLPhysicalTextureWrapper::determineTypeFrom(const std::string& path)
			{
				if (path.length() == 0)
					return TextureType::DISC_TEXTURE;
				else if (StringUtil::endsWith(path, ".dds"))
					return TextureType::S3TC_TEXTURE;
				else
					return TextureType::DISC_TEXTURE;
			}

			GLPhysicalTextureWrapper::GLPhysicalTextureWrapper() :
				GLPhysicalTextureWrapper("")
			{}

			GLPhysicalTextureWrapper::GLPhysicalTextureWrapper(const std::string& path) :
				GLPhysicalTexture(),
				m_texType(determineTypeFrom(path)),
				m_texture(nullptr)
			{
				GLPhysicalTexture::setPath(path);
			}

			GLPhysicalTextureWrapper::GLPhysicalTextureWrapper(const GLPhysicalTextureWrapper& obj) :
				GLPhysicalTexture(obj),
				m_texType(obj.m_texType),
				m_texture(nullptr)
			{}

			GLPhysicalTextureWrapper::TextureType GLPhysicalTextureWrapper::getTextureType() const
			{
				return m_texType;
			}

			GLPhysicalTexture* GLPhysicalTextureWrapper::getTexture() const
			{
				return m_texture.get();
			}

			void GLPhysicalTextureWrapper::setPath(const std::string& path)
			{
				GLPhysicalTexture::setPath(path);
				m_texType = determineTypeFrom(path);
			}

			const GLPhysicalTextureWrapper& GLPhysicalTextureWrapper::bind() const
			{
				if (m_texture)
					m_texture->bind();
				return *this;
			}

			const GLPhysicalTextureWrapper& GLPhysicalTextureWrapper::release() const
			{
				if (m_texture)
					m_texture->release();
				return *this;
			}

			void GLPhysicalTextureWrapper::upload()
			{
				if (m_texture)
				{
					m_texture->upload();
					m_id = m_texture->getID();
				}

			}

			void GLPhysicalTextureWrapper::importTexture()
			{
				importTexture(m_path);
			}

			void GLPhysicalTextureWrapper::importTexture(const std::string& path)
			{
				setPath(path);

				if (m_texType == TextureType::S3TC_TEXTURE)
				{
					GLS3TCTexture* ptr;
					std::unique_ptr<GLPhysicalTexture> temp(ptr = new GLS3TCTexture(path));
						
					ptr->importTexture();
					m_texture.swap(temp);
				}
				else
				{
					GLDiscTexture* ptr;
					std::unique_ptr<GLPhysicalTexture> temp(ptr = new GLDiscTexture(path));

					ptr->importTexture();
					m_texture.swap(temp);
				}
					
				if (m_texture)
				{
					m_type = m_texture->getType();
					m_internalFormat = m_texture->getInternalFormat();
					m_format = m_texture->getFormat();
					m_size = m_texture->getSize();
				}

			}

		}

	}

}