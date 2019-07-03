#include <org/segames/library/gl/fbo/gl_framebuffer_30.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/gl/gl_core.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void GLFramebuffer30::buildFBO()
			{
				GLint numColors;
				glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &numColors);
				numColors -= 1;

				if (!m_id)
					glGenFramebuffers(1, &m_id);

				glBindFramebuffer(GL_FRAMEBUFFER, m_id);

				// Main color comp
				if (m_color)
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color->getType(), m_color->getID(), 0);
				else
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GL_NONE, 0);

				// Additional color comp
				for (int i = 0; i < Math::min(m_additional_colors.size(), numColors); i++)
				{
					GLTexture* tex = m_additional_colors.get(i);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1 + i, tex->getType(), tex->getID(), 0);
				}
				for (int i = m_additional_colors.size(); i < numColors; i++)
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1 + i, GL_TEXTURE_2D, GL_NONE, 0);

				// Depth comp
				if (m_depth)
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth->getType(), m_depth->getID(), 0);
				else
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, GL_NONE, 0);

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					throw GLException("Could not complete framebuffer.", __FILE__, __LINE__);

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			GLFramebuffer30::GLFramebuffer30() :
				GLFramebuffer30(nullptr, nullptr, Dimension2i())
			{}

			GLFramebuffer30::GLFramebuffer30(GLTexture* color, GLTexture* depth, const Dimension2i& size) :
				GLAbstractFramebuffer(color, depth, size)
			{}

			GLFramebuffer30::GLFramebuffer30(const GLFramebuffer30& obj) :
				GLAbstractFramebuffer(obj)
			{}

			GLFramebuffer30::~GLFramebuffer30()
			{
				if (m_id)
					glDeleteFramebuffers(1, &m_id);
			}

			const GLFramebuffer30& GLFramebuffer30::bind() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, m_id);
				return *this;
			}

			const GLFramebuffer30& GLFramebuffer30::release() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
				return *this;
			}

			bool GLFramebuffer30::isSupported()
			{
				return GLCore::glVersion() >= 3.0f;
			}

		}

	}

}