#include <org/segames/library/gl/gl_core.h>
#include <org/segames/library/util/string_util.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			float GLCore::m_version = 0.0f;
			std::unique_ptr<std::unordered_set<std::string>> GLCore::m_extensions = std::unique_ptr<std::unordered_set<std::string>>(nullptr);

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

			bool GLCore::hasExtension(const std::string& ext)
			{
				return glExtensions().find(ext) != m_extensions->end();
			}

			const std::unordered_set<std::string>& GLCore::glExtensions()
			{
				if (!m_extensions.get())
				{
					std::unique_ptr<std::unordered_set<std::string>> temp(new std::unordered_set<std::string>());
					m_extensions.swap(temp);

					const GLubyte* str = glGetString(GL_EXTENSIONS);
					if (str)
					{
						std::string full(reinterpret_cast<const char*>(str));
						ArrayList<std::string> list;
						StringUtil::split(full, " ", list);
						
						m_extensions->reserve(list.size());
						for (int i = 0; i < list.size(); i++)
							m_extensions->insert(list.get(i));
					}

				}
				return *m_extensions;
			}

		}

	}

}