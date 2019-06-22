#include <org/segames/library/glfw/glfw_iconification_listener.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void GLFWIconificationListener::callback(GLFWwindow* window, int flag)
			{
				auto pair = m_listeners.find(window);
				if (pair != m_listeners.end())
					pair->second->invoke(flag != 0);
			}

			void GLFWIconificationListener::detach(GLFWwindow* window)
			{
				glfwSetWindowIconifyCallback(window, NULL);
			}

			void GLFWIconificationListener::linkGLFW(GLFWwindow* window)
			{
				glfwSetWindowIconifyCallback(window, callback);
				m_iconified = false;
			}

			bool GLFWIconificationListener::isIconified() const
			{
				return m_iconified;
			}

			void GLFWIconificationListener::invoke(bool flag)
			{
				m_iconified = flag;
			}

		}

	}

}