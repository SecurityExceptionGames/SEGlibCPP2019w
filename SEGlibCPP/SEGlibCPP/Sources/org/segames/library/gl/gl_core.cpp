#include <org/segames/library/gl/gl_core.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				float GLCore::m_version = 0.0f;

				float GLCore::glVersion()
				{
					if (m_version == 0.0f)
					{
						GLint major, minor;
						glGetIntegerv(GL_MAJOR_VERSION, &major);
						glGetIntegerv(GL_MINOR_VERSION, &minor);
						m_version = major + minor * 0.1f;
					}
					return m_version;
				}

			}

		}

	}

}