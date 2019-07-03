#include <org/segames/library/gl/fbo/gl_framebuffer_wrapper.h>
#include <org/segames/library/gl/fbo/gl_framebuffer_30.h>
#include <org/segames/library/gl/fbo/gl_framebuffer_ext.h>
#include <org/segames/library/gl/gl_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLAbstractFramebuffer* GLFramebufferWrapper::newSupportedFBO(GLTexture* color, GLTexture* depth, const Dimension2i& size)
			{
				if (GLFramebuffer30::isSupported())
					return new GLFramebuffer30(color, depth, size);
				else if (GLFramebufferEXT::isSupported())
					return new GLFramebufferEXT(color, depth, size);
				return nullptr;
			}

			GLFramebufferWrapper::GLFramebufferWrapper() :
				GLFramebufferWrapper(false, false, Dimension2i())
			{}

			GLFramebufferWrapper::GLFramebufferWrapper(const bool color, const bool depth, const Dimension2i& size) :
				GLFramebufferWrapper(
					color ? new GLTexture(GL_RGBA8, Dimension3i(size.getWidth(), size.getHeight(), 1)) : nullptr,
					depth ? new GLTexture(GL_DEPTH_COMPONENT, Dimension3i(size.getWidth(), size.getHeight(), 1)) : nullptr,
					size
				)
			{}

			GLFramebufferWrapper::GLFramebufferWrapper(GLTexture* color, GLTexture* depth, const Dimension2i& size) :
				m_buffer(newSupportedFBO(color, depth, size))
			{
				if (!m_buffer)
					throw GLException("No framebuffer is supported on this machine.", __FILE__, __LINE__);
			}

			GLFramebufferWrapper::GLFramebufferWrapper(const GLFramebufferWrapper& obj) :
				GLFramebufferWrapper(obj.getColorComp() != nullptr, obj.getDepthComp() != nullptr, obj.getSize())
			{}

			GLFramebufferWrapper::~GLFramebufferWrapper()
			{}

			GLuint GLFramebufferWrapper::getID() const
			{
				return m_buffer->getID();
			}

			const Dimension2i& GLFramebufferWrapper::getSize() const
			{
				return m_buffer->getSize();
			}

			GLTexture* GLFramebufferWrapper::getColorComp() const
			{
				return m_buffer->getColorComp();
			}

			GLTexture* GLFramebufferWrapper::getDepthComp() const
			{
				return m_buffer->getDepthComp();
			}

			const ArrayList<GLTexture*>& GLFramebufferWrapper::getAdditionalColorComp() const
			{
				return m_buffer->getAdditionalColorComp();
			}

			GLAbstractFramebuffer* GLFramebufferWrapper::getBuffer() const
			{
				return m_buffer.get();
			}

			void GLFramebufferWrapper::setSize(const Dimension2i& size)
			{
				m_buffer->setSize(size);
			}

			void GLFramebufferWrapper::setColorComp(GLTexture* tex)
			{
				m_buffer->setColorComp(tex);
			}

			void GLFramebufferWrapper::setDepthComp(GLTexture* tex)
			{
				m_buffer->setDepthComp(tex);
			}
			
			void GLFramebufferWrapper::addAdditionalColorComp(GLTexture* tex)
			{
				m_buffer->addAdditionalColorComp(tex);
			}

			GLTexture* GLFramebufferWrapper::removeAdditionalColorComp(const int index)
			{
				return m_buffer->removeAdditionalColorComp(index);
			}

			const GLFramebufferWrapper& GLFramebufferWrapper::bind() const
			{
				m_buffer->bind();
				return *this;
			}

			const GLFramebufferWrapper& GLFramebufferWrapper::release() const
			{
				m_buffer->release();
				return *this;
			}

			void GLFramebufferWrapper::build()
			{
				m_buffer->build();
			}

			bool GLFramebufferWrapper::isSupported()
			{
				return 
					GLFramebuffer30::isSupported() ||
					GLFramebufferEXT::isSupported();
			}

		}

	}

}