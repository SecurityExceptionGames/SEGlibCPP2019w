#include <org/segames/library/glfw/glfw_key_listener.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				void GLFWKeyListener::callback(GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					auto pair = m_listeners.find(window);
					if (pair != m_listeners.end())
						pair->second->invoke(key, scancode, action, mods);
				}

				void GLFWKeyListener::detach(GLFWwindow* window)
				{
					glfwSetKeyCallback(window, NULL);
				}

				void GLFWKeyListener::linkGLFW(GLFWwindow* window)
				{
					glfwSetKeyCallback(window, callback);
				}

				bool GLFWKeyListener::isPressed(int button) const
				{
					return m_keys.find(button) != m_keys.end();
				}

				void GLFWKeyListener::invoke(int key, int scancode, int action, int mods)
				{
					if (action == GLFW_PRESS)
						m_keys.insert(key);
					else if (action == GLFW_RELEASE)
						m_keys.erase(key);
				}

			}

		}

	}

}