#include <org/segames/library/gl/texture/gl_texture.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/gl/gl_core.h>

using org::segames::library::math::Dimension3i;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				int GLTexture::m_glMaxTextureSize = 0;

				GLenum GLTexture::formatFromInternalFormat(const GLenum internalFormat)
				{
					switch (internalFormat)
					{
					case GL_RGBA8:
					case GL_RGBA16:
						return GL_RGBA;
					case GL_RGB8:
					case GL_RGB16:
						return GL_RGB;
					case GL_RG8:
					case GL_RG16:
						return GL_RG;
					case GL_R8:
					case GL_R16:
						return GL_RED;
					default:
						return internalFormat;
					}

				}

				GLTexture::GLTexture() :
					GLTexture(Dimension3i(0, 0, 0))
				{}

				GLTexture::GLTexture(const Dimension3i& size) :
					GLTexture(GL_RGBA8, size)
				{}

				GLTexture::GLTexture(const GLenum internalFormat, const Dimension3i& size) :
					GLTexture(GL_TEXTURE_2D, internalFormat, formatFromInternalFormat(internalFormat), size)
				{}

				GLTexture::GLTexture(const GLenum type, const GLenum internalFormat, const GLenum format, const Dimension3i& size) :
					m_id(0),
					m_type(type),
					m_internalFormat(internalFormat),
					m_format(format),
					m_size(size)
				{}

				GLTexture::~GLTexture()
				{
					if (m_id)
						glDeleteTextures(1, &m_id);
				}

				GLuint GLTexture::getID() const
				{
					return m_id;
				}

				GLenum GLTexture::getType() const
				{
					return m_type;
				}

				GLenum GLTexture::getInternalFormat() const
				{
					return m_internalFormat;
				}

				GLenum GLTexture::getFormat() const
				{
					return m_format;
				}

				const Dimension3i& GLTexture::getSize() const
				{
					return m_size;
				}

				const GLTexture& GLTexture::bind() const
				{
					glBindTexture(m_type, m_id);
					return *this;
				}

				const GLTexture& GLTexture::release() const
				{
					glBindTexture(m_type, GL_NONE);
					return *this;
				}

				const GLTexture& GLTexture::generateMipMap() const
				{
					if(GLCore::glVersion() >= 3.0f)
						glGenerateMipmap(m_type);
					return *this;
				}

				const GLTexture& GLTexture::setParameters(const GLenum wrapping, const GLenum minFilter, const GLenum magFilter) const
				{
					glTexParameteri(m_type, GL_TEXTURE_WRAP_S, wrapping);
					glTexParameteri(m_type, GL_TEXTURE_WRAP_T, wrapping);
					glTexParameteri(m_type, GL_TEXTURE_WRAP_R, wrapping);
					glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, minFilter);
					glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, magFilter);

					GLenum err = glGetError();
					if (err != GL_NO_ERROR)
						throw GLException(err, __FILE__, __LINE__);
					return *this;
				}

				void GLTexture::upload(const GLenum storage, const void* data)
				{
					if (!m_id)
					{
						glGenTextures(1, &m_id);
						if (!glIsEnabled(m_type))
							glEnable(m_type);

						bind();
						setParameters(GL_REPEAT, GL_NEAREST, GL_NEAREST);
					}
					else
						bind();

					switch (m_type)
					{
					case GL_TEXTURE_1D:
						glTexImage1D(m_type, 0, m_internalFormat, m_size.getWidth(), 0, m_format, storage, data);
						break;
					case GL_TEXTURE_2D:
					case GL_TEXTURE_1D_ARRAY:
						glTexImage2D(m_type, 0, m_internalFormat, m_size.getWidth(), m_size.getHeight(), 0, m_format, storage, data);
						break;
					case GL_TEXTURE_3D:
					case GL_TEXTURE_2D_ARRAY:
						glTexImage3D(m_type, 0, m_internalFormat, m_size.getWidth(), m_size.getHeight(), m_size.getDepth(), 0, m_format, storage, data);
						break;
					default:
						break;
					}

					release();
				}

				int GLTexture::glMaxTextureSize()
				{
					if (!m_glMaxTextureSize)
						glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_glMaxTextureSize);
					return m_glMaxTextureSize;
				}

			}

		}

	}

}