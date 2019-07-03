#include <org/segames/library/gl/fbo/gl_framebuffer_ext.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/gl/gl_core.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void GLFramebufferEXT::buildFBO()
			{
				GLint numColors;
				glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &numColors);
				numColors -= 1;

				if (!m_id)
					glGenFramebuffersEXT(1, &m_id);

				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_id);

				// Main color comp
				if (m_color)
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, m_color->getType(), m_color->getID(), 0);
				else
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, GL_NONE, 0);

				// Additional color comp
				for (int i = 0; i < Math::min(m_additional_colors.size(), numColors); i++)
				{
					GLTexture* tex = m_additional_colors.get(i);
					glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT + i, tex->getType(), tex->getID(), 0);
				}
				for (int i = m_additional_colors.size(); i < numColors; i++)
					glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT + i, GL_TEXTURE_2D, GL_NONE, 0);

				// Depth comp
				if (m_depth)
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, m_depth->getType(), m_depth->getID(), 0);
				else
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, GL_NONE, 0);

				if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
					throw GLException("Could not complete framebuffer.", __FILE__, __LINE__);

				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			}

			GLFramebufferEXT::GLFramebufferEXT() :
				GLFramebufferEXT(nullptr, nullptr, Dimension2i())
			{}

			GLFramebufferEXT::GLFramebufferEXT(GLTexture* color, GLTexture* depth, const Dimension2i& size) :
				GLAbstractFramebuffer(color, depth, size)
			{}

			GLFramebufferEXT::GLFramebufferEXT(const GLFramebufferEXT& obj) :
				GLAbstractFramebuffer(obj)
			{}

			GLFramebufferEXT::~GLFramebufferEXT()
			{
				if (m_id)
					glDeleteFramebuffersEXT(1, &m_id);
			}

			const GLFramebufferEXT& GLFramebufferEXT::bind() const
			{
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_id);
				return *this;
			}

			const GLFramebufferEXT& GLFramebufferEXT::release() const
			{
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GL_NONE);
				return *this;
			}

			bool GLFramebufferEXT::isSupported()
			{
				return GLCore::hasExtension("GL_EXT_framebuffer_object");
			}

		}

	}

}