#include <org/segames/library/gl/fbo/gl_abstract_framebuffer.h>
#include <org/segames/library/gl/gl_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void GLAbstractFramebuffer::buildTextures(bool* changed)
			{
#ifdef SEG_API_DEBUG_THROW
				GLenum error;
#endif
				// Depth comp
				if (m_depth)
				{
					bool newTex = !m_depth->getID();
					if (newTex || m_resetTexture)
					{
						m_depth->upload(GL_FLOAT, nullptr);
						if (newTex)
							m_depth->bind().setParameters(GL_CLAMP, GL_NEAREST, GL_NEAREST).release();
						*changed = true;
					}

#ifdef SEG_API_DEBUG_THROW
					error = glGetError();
					if (error != GL_NO_ERROR)
						throw GLException(error, __FILE__, __LINE__);
#endif
				}

				// Additional color comp
				for (int i = 0; i < m_additional_colors.size(); i++)
				{
					bool newTex = !m_additional_colors.get(i)->getID();
					if (newTex || m_resetTexture)
					{
						m_additional_colors.get(i)->upload(GL_UNSIGNED_BYTE, nullptr);
						*changed = true;
					}

#ifdef SEG_API_DEBUG_THROW
					error = glGetError();
					if (error != GL_NO_ERROR)
						throw GLException(error, __FILE__, __LINE__);
#endif
				}

				// Color comp
				if (m_color)
					if (!m_color->getID() || m_resetTexture)
					{
						m_color->upload(GL_UNSIGNED_BYTE, nullptr);
						*changed = true;
					}

#ifdef SEG_API_DEBUG_THROW
				error = glGetError();
				if (error != GL_NO_ERROR)
					throw GLException(error, __FILE__, __LINE__);
#endif
			}
				
			GLAbstractFramebuffer::GLAbstractFramebuffer(GLTexture* color, GLTexture* depth, const Dimension2i& size) :
				m_resetTexture(true),
				m_id(0),
				m_size(size),
				m_color(color),
				m_depth(depth)
			{
				if (m_color)
					m_color->setSize(Dimension3i(m_size.getWidth(), m_size.getHeight(), m_color->getSize().getDepth()));
				if (m_depth)
					m_depth->setSize(Dimension3i(m_size.getWidth(), m_size.getHeight(), m_depth->getSize().getDepth()));
			}

			GLAbstractFramebuffer::GLAbstractFramebuffer(const GLAbstractFramebuffer& obj) :
				GLAbstractFramebuffer(
					obj.m_color ? new GLTexture(*obj.m_color) : nullptr,
					obj.m_depth ? new GLTexture(*obj.m_depth) : nullptr,
					obj.m_size
				)
			{}

			GLAbstractFramebuffer::~GLAbstractFramebuffer()
			{
				for (int i = 0; i < m_additional_colors.size(); i++)
					if (m_additional_colors.get(i))
						delete m_additional_colors.get(i);
			}

			GLuint GLAbstractFramebuffer::getID() const
			{
				return m_id;
			}

			const Dimension2i& GLAbstractFramebuffer::getSize() const
			{
				return m_size;
			}

			GLTexture* GLAbstractFramebuffer::getColorComp() const
			{
				return m_color.get();
			}

			GLTexture* GLAbstractFramebuffer::getDepthComp() const
			{
				return m_depth.get();
			}

			const ArrayList<GLTexture*>& GLAbstractFramebuffer::getAdditionalColorComp() const
			{
				return m_additional_colors;
			}

			void GLAbstractFramebuffer::setSize(const Dimension2i& size)
			{
				m_size = size;
				Dimension3i texSize = Dimension3i(m_size.getWidth(), m_size.getHeight(), m_color->getSize().getDepth());
				if (m_color)
					m_color->setSize(texSize);
				for (int i = 0; i < m_additional_colors.size(); i++)
					m_additional_colors.get(i)->setSize(texSize);
				if(m_depth)
					m_depth->setSize(texSize);
				m_resetTexture = true;
			}

			void GLAbstractFramebuffer::setColorComp(GLTexture* tex)
			{
				std::unique_ptr<GLTexture> temp(tex);
				m_color.swap(temp);
				m_resetTexture = true;
			}

			void GLAbstractFramebuffer::setDepthComp(GLTexture* tex)
			{
				std::unique_ptr<GLTexture> temp(tex);
				m_depth.swap(temp);
				m_resetTexture = true;
			}

			void GLAbstractFramebuffer::addAdditionalColorComp(GLTexture* tex)
			{
				m_additional_colors.add(tex);
				m_resetTexture = true;
			}

			GLTexture* GLAbstractFramebuffer::removeAdditionalColorComp(const int index)
			{
				m_resetTexture = true;
				return m_additional_colors.remove(index);
			}

			void GLAbstractFramebuffer::build()
			{
				bool changed = false;
				buildTextures(&changed);
				if (changed)
					buildFBO();
			}

		}

	}

}