#include <org/segames/library/glfw/glfw_window_size_listener.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				void GLFWWindowSizeListener::linkGLFW(GLFWwindow* win)
				{
					glfwSetWindowSizeCallback(win, callback);
					glfwGetWindowSize(win, &m_w, &m_h);
				}

				void GLFWWindowSizeListener::callback(GLFWwindow* win, int w, int h)
				{
					auto listener = m_listeners.find(win);
					if (listener != m_listeners.end())
					{
						listener->second->m_w = w;
						listener->second->m_h = h;
					}

				}

				int GLFWWindowSizeListener::width() const
				{
					return m_w;
				}

				int GLFWWindowSizeListener::height() const
				{
					return m_h;
				}

			}

		}

	}

}