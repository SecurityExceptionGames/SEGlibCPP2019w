#include <org/segames/library/glfw/glfw_mouse_position_listener.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				void GLFWMousePositionListener::callback(GLFWwindow* window, double mx, double my)
				{
					auto pair = m_listeners.find(window);
					if (pair != m_listeners.end())
						pair->second->invoke(mx, my);
				}

				void GLFWMousePositionListener::detach(GLFWwindow* window)
				{
					glfwSetCursorPosCallback(window, NULL);
				}

				void GLFWMousePositionListener::linkGLFW(GLFWwindow* window)
				{
					glfwSetCursorPosCallback(window, callback);
					
					double mx, my;
					glfwGetCursorPos(window, &mx, &my);
					invoke(mx, my);
				}
				
				int GLFWMousePositionListener::getMX() const
				{
					return m_mx;
				}

				int GLFWMousePositionListener::getMY() const
				{
					return m_my;
				}

				void GLFWMousePositionListener::invoke(double mx, double my)
				{
					m_mx = (int)mx;
					m_my = (int)my;
				}

			}

		}

	}

}