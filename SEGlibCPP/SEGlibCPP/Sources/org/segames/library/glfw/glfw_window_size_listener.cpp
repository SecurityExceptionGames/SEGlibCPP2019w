#include <org/segames/library/glfw/glfw_window_size_listener.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				void GLFWWindowSizeListener::callback(GLFWwindow* window, int w, int h)
				{
					auto pair = m_listeners.find(window);
					if (pair != m_listeners.end())
						pair->second->invoke(w, h);
				}

				void GLFWWindowSizeListener::detach(GLFWwindow* window)
				{
					glfwSetWindowSizeCallback(window, NULL);
				}

				void GLFWWindowSizeListener::linkGLFW(GLFWwindow* window)
				{
					glfwSetWindowSizeCallback(window, callback);
					glfwGetWindowSize(window, &m_w, &m_h);
				}

				int GLFWWindowSizeListener::getWidth() const
				{
					return m_w;
				}

				int GLFWWindowSizeListener::getHeight() const
				{
					return m_h;
				}
				
				void GLFWWindowSizeListener::invoke(int w, int h)
				{
					m_w = w;
					m_h = h;
				}

			}

		}

	}

}