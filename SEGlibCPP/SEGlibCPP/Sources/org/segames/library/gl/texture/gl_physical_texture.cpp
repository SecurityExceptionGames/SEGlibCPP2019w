#include <org/segames/library/gl/texture/gl_physical_texture.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLPhysicalTexture::GLPhysicalTexture() :
				GLTexture()
			{}

			GLPhysicalTexture::GLPhysicalTexture(const Dimension3i& size) :
				GLTexture(size)
			{}

			GLPhysicalTexture::GLPhysicalTexture(const GLenum internalFormat, const Dimension3i& size) :
				GLTexture(internalFormat, size)
			{}

			GLPhysicalTexture::GLPhysicalTexture(const GLenum type, const GLenum internalFormat, const GLenum format, const Dimension3i& size) :
				GLTexture(type, internalFormat, format, size)
			{}

			const std::string& GLPhysicalTexture::getPath() const
			{
				return m_path;
			}

			void GLPhysicalTexture::setPath(const std::string& path)
			{
				m_path = path;
			}

		}

	}

}