#include <org/segames/library/gl/gl_pointer_binding.h>
#include <org/segames/library/gl/gl_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				GLPointerBinding::GLPointerBinding() :
					GLPointerBinding(GLDataType::VERTEX, GLPointerInf::TWO_FLOAT_POINTER)
				{}

				GLPointerBinding::GLPointerBinding(const GLDataType type, const GLPointerInf& inf) :
					m_type(type),
					m_inf(inf)
				{
					switch (m_type)
					{
					case GLDataType::VERTEX:
						m_infSetMethod = inf.setVertexPointer;
						break;
					case GLDataType::NORMAL:
						m_infSetMethod = inf.setNormalPointer;
						break;
					case GLDataType::COLOR:
						m_infSetMethod = inf.setColorPointer;
						break;
					case GLDataType::TEX_COORD:
						m_infSetMethod = inf.setTexCoordPointer;
						break;
					case GLDataType::INDEX:
						m_infSetMethod = inf.setIndexPointer;
						break;
					case GLDataType::EDGE_FLAG:
						m_infSetMethod = inf.setEdgeFlagPointer;
						break;
					default:
						m_infSetMethod = nullptr;
						break;
					}

				}

				GLPointerBinding::GLPointerBinding(const GLPointerBinding& obj) :
					GLPointerBinding(obj.m_type, obj.m_inf)
				{}

				GLPointerBinding::~GLPointerBinding()
				{}

				GLDataType GLPointerBinding::getType() const
				{
					return m_type;
				}

				const GLPointerInf& GLPointerBinding::getInf() const
				{
					return m_inf;
				}

				void GLPointerBinding::setPointer() const
				{
#ifdef SEG_API_DEBUG_THROW
					if (m_type == GLDataType::ATTRIBUTE)
						throw GLException("Cannot bind attribute pointer information without attribute id.");
#endif
					(m_inf.*m_infSetMethod)();
				}

				void GLPointerBinding::setPointer(const GLuint location) const
				{
					m_inf.setAttribPointer(location);
				}

				bool GLPointerBinding::equals(const Object& obj) const
				{
					if (typeid(obj) == typeid(*this))
					{
						const GLPointerBinding& ref = dynamic_cast<const GLPointerBinding&>(obj);

						if (ref.m_inf != m_inf)
							return false;
						else if (ref.m_type != m_type)
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