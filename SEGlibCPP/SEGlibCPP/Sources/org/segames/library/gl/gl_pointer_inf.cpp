#include <org/segames/library/gl/gl_pointer_inf.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLPointerInf::GLPointerInf() :
				GLPointerInf(GL_FLOAT, 2, 0, 0)
			{}

			GLPointerInf::GLPointerInf(const GLenum type, const GLint size, const GLint stride, const size_t offset) :
				GLPointerInf(false, type, size, stride, offset)
			{}

			GLPointerInf::GLPointerInf(const GLboolean normalized, const GLenum type, const GLint size, const GLint stride, const size_t offset) :
				m_normalized(normalized),
				m_type(type),
				m_size(size),
				m_stride(stride),
				m_offset(offset)
			{}

			GLboolean GLPointerInf::normalized() const
			{
				return m_normalized;
			}

			GLenum GLPointerInf::getType() const
			{
				return m_type;
			}

			GLint GLPointerInf::getSize() const
			{
				return m_size;
			}

			GLint GLPointerInf::getStride() const
			{
				return m_stride;
			}

			GLint GLPointerInf::getOffset() const
			{
				return m_offset;
			}

			void GLPointerInf::setVertexPointer() const
			{
				glVertexPointer(m_size, m_type, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setNormalPointer() const
			{
				glNormalPointer(m_type, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setColorPointer() const
			{
				glColorPointer(m_size, m_type, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setTexCoordPointer() const
			{
				glTexCoordPointer(m_size, m_type, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setAttribPointer(const GLuint location) const
			{
				glVertexAttribPointer(location, m_size, m_type, m_normalized, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setIndexPointer() const
			{
				glIndexPointer(m_type, m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			void GLPointerInf::setEdgeFlagPointer() const
			{
				glEdgeFlagPointer(m_stride, static_cast<GLubyte*>(0) + m_offset);
			}

			bool GLPointerInf::equals(const Object& obj) const
			{
				if (typeid(obj) != typeid(*this))
					return false;
				else
				{
					const GLPointerInf& pInf = dynamic_cast<const GLPointerInf&>(obj);
						
					if (pInf.m_normalized != m_normalized)
						return false;
					else if (pInf.m_type != m_type)
						return false;
					else if (pInf.m_size != m_size)
						return false;
					else if (pInf.m_stride != m_stride)
						return false;
					else if (pInf.m_offset != m_offset)
						return false;
					return true;
				}

			}

			GLPointerInf GLPointerInf::ONE_FLOAT_POINTER	= GLPointerInf(GL_FLOAT, 1, 0, 0);
			GLPointerInf GLPointerInf::TWO_FLOAT_POINTER	= GLPointerInf(GL_FLOAT, 2, 0, 0);
			GLPointerInf GLPointerInf::THREE_FLOAT_POINTER	= GLPointerInf(GL_FLOAT, 3, 0, 0);
			GLPointerInf GLPointerInf::FOUR_FLOAT_POINTER	= GLPointerInf(GL_FLOAT, 4, 0, 0);

			GLPointerInf GLPointerInf::ONE_INT_POINTER		= GLPointerInf(GL_INT, 1, 0, 0);
			GLPointerInf GLPointerInf::TWO_INT_POINTER		= GLPointerInf(GL_INT, 2, 0, 0);
			GLPointerInf GLPointerInf::THREE_INT_POINTER	= GLPointerInf(GL_INT, 3, 0, 0);
			GLPointerInf GLPointerInf::FOUR_INT_POINTER		= GLPointerInf(GL_INT, 4, 0, 0);

		}

	}

}