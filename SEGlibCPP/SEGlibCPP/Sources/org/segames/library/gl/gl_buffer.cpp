#include <org/segames/library/gl/gl_buffer.h>
#include <org/segames/library/gl/gl_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				GLBuffer::GLBuffer() :
					m_id(0),
					m_bufferType(GL_ARRAY_BUFFER),
					m_uploadLength(0),
					m_infBindings(util::ArrayList<GLPointerBinding*>(1))
				{
					for (int i = 0; i < GLDataType::ATTRIBUTE - 1; i++)
						m_infBindings.add(nullptr);
				}

				GLBuffer::GLBuffer(const GLDataType type, const GLPointerInf& inf) :
					GLBuffer()
				{
					setPointerBinding(type, inf);
				}

				GLBuffer::~GLBuffer()
				{
					if (m_id)
						glDeleteBuffers(1, &m_id);

					for (int i = 0; i < m_infBindings.size(); i++)
						if (m_infBindings.get(i))
							delete m_infBindings.get(i);
				}

				GLuint GLBuffer::getID() const
				{
					return m_id;
				}

				GLenum GLBuffer::getBufferType() const
				{
					return m_bufferType;
				}

				GLsizeiptr GLBuffer::getUploadLength() const
				{
					return m_uploadLength;
				}

				const GLBuffer& GLBuffer::bind() const
				{
					glBindBuffer(m_bufferType, m_id);
					return *this;
				}

				const GLBuffer& GLBuffer::release() const
				{
					glBindBuffer(m_bufferType, GL_NONE);
					return *this;
				}

				const GLBuffer& GLBuffer::setPointerInf() const
				{
#ifdef SEG_API_DEBUG_THROW
					bool ptrInf = false;
#endif

					for (int i = 0; i < GLDataType::ATTRIBUTE - 1; i++)
						if (m_infBindings.get(i))
						{
							m_infBindings.get(i)->setPointer();
#ifdef SEG_API_DEBUG_THROW
							ptrInf = true;
#endif
						}

					for (int i = GLDataType::ATTRIBUTE; i < m_infBindings.size(); i++)
						if (m_infBindings.get(i))
						{
							m_infBindings.get(i)->setPointer(i - GLDataType::ATTRIBUTE);
#ifdef SEG_API_DEBUG_THROW
							ptrInf = true;
#endif
						}

#ifdef SEG_API_DEBUG_THROW
					if (!ptrInf)
						throw GLException("No pointer information set for buffer.");
#endif
					return *this;
				}

				GLBuffer& GLBuffer::setPointerBinding(const GLDataType type, const GLPointerInf& inf)
				{
#ifdef SEG_API_DEBUG_THROW
					if (type == GLDataType::ATTRIBUTE)
						throw GLException("Cannot set attribute pointer information without attribute id.");
#endif
					if (m_infBindings.get(type))
						*m_infBindings.get(type) = GLPointerBinding(type, inf);
					else
						m_infBindings.set(type, new GLPointerBinding(type, inf));
					return *this;
				}

				GLBuffer& GLBuffer::setPointerBinding(const GLDataType type, const GLPointerInf& inf, const GLuint location)
				{
					if (type != GLDataType::ATTRIBUTE)
						setPointerBinding(type, inf);
					else
					{
						int index = location + GLDataType::ATTRIBUTE;
						while (index >= m_infBindings.size())
							m_infBindings.add(nullptr);
						
						if (m_infBindings.get(index))
							*m_infBindings.get(index) = GLPointerBinding(type, inf);
						else
							m_infBindings.set(index, new GLPointerBinding(type, inf));
					}
					return *this;
				}

				GLBuffer& GLBuffer::removePointerBinding(const GLDataType type)
				{
#ifdef SEG_API_DEBUG_THROW
					if (type == GLDataType::ATTRIBUTE)
						throw GLException("Cannot remove attribute pointer information without attribute id.");
#endif
					if (m_infBindings.get(type))
						delete m_infBindings.set(type, nullptr);
					return *this;
				}

				GLBuffer& GLBuffer::removePointerBinding(const GLDataType type, const GLuint location)
				{
					if (type != GLDataType::ATTRIBUTE)
						removePointerBinding(type);
					else
					{
						int index = location + GLDataType::ATTRIBUTE;
						if (index < m_infBindings.size())
							if (m_infBindings.get(index))
								delete m_infBindings.set(index, nullptr);
					}
					return *this;
				}

				void GLBuffer::upload(const GLsizeiptr len, const void* data)
				{
					upload(len, data, GL_STATIC_DRAW);
				}

				void GLBuffer::upload(const GLsizeiptr len, const void* data, const GLenum mode)
				{
					if (!m_id)
						glGenBuffers(1, &m_id);
					glBindBuffer(m_bufferType, m_id);
					glBufferData(m_bufferType, len, data, mode);
					glBindBuffer(m_bufferType, GL_NONE);
					m_uploadLength = len;
				}

				bool GLBuffer::equals(const Object& obj) const
				{
					if (typeid(obj) == typeid(*this))
					{
						const GLBuffer& ref = dynamic_cast<const GLBuffer&>(obj);
						if (ref.m_id != m_id)
							return false;
						if (ref.m_bufferType != m_bufferType)
							return false;
						if (ref.m_infBindings.size() != m_infBindings.size())
							return false;

						for (int i = 0; i < m_infBindings.size(); i++)
							if (ref.m_infBindings.get(i) != m_infBindings.get(i))
								return false;
						return true;
					}
					else
						return false;
				}

			}

		}

	}

}