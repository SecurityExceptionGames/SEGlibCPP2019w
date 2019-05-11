#include <org/segames/library/glfw/glfw_mouse_button_listener.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				void GLFWMouseButtonListener::callback(GLFWwindow* window, int button, int action, int mods)
				{
					auto pair = m_listeners.find(window);
					if (pair != m_listeners.end())
						pair->second->invoke(button, action, mods);
				}

				void GLFWMouseButtonListener::detach(GLFWwindow* window)
				{
					glfwSetMouseButtonCallback(window, NULL);
				}

				void GLFWMouseButtonListener::linkGLFW(GLFWwindow* window)
				{
					glfwSetMouseButtonCallback(window, callback);
				}

				bool GLFWMouseButtonListener::isPressed(int button) const
				{
					return m_buttons[button];
				}

				void GLFWMouseButtonListener::invoke(int button, int action, int mods)
				{
					if (button <= GLFW_MOUSE_BUTTON_LAST)
					{
						if (action == GLFW_RELEASE)
							m_buttons[button] = false;
						else if (mods == 0)
							m_buttons[button] = true;
					}

				}

			}

		}

	}

}