#pragma once
#include <org/segames/library/glfw/glfw_listener.h>
#include <org/segames/library/object.h>

#include <unordered_set>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A listener for detecting key actions.

				* @author	Philip Rosberg
				* @since	2019-05-11
				* @edited	2019-05-11
			*/
			class SEG_API GLFWKeyListener :
				public Object,
				public GLFWListener<GLFWKeyListener>
			{
			private:

				/*
					Callback for GLFW.
				*/
				static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			public:

				/*
					Unlinks the callback for the given window.
					* @param[in] window The GLFW window id
				*/
				static void detach(GLFWwindow* window);

			protected:

				/*
					The active keys.
				*/
				std::unordered_set<int> m_keys;

				/*
					Links this listener to GLFW.
					* @param[in] window The GLFW window id
				*/
				virtual void linkGLFW(GLFWwindow* window) override;

			public:

				/*
					Returns true if the key of the given id is pressed.
					* @param[in] key The GLFW id of the key to check
				*/
				virtual bool isPressed(int key) const;

				/*
					The method that is called when the listener is activated.
					* @param[in] key The keyboard key that was pressed or released
					* @param[in] scancode The system-specific scancode of the key
					* @param[in] action The key action. One of: GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
					* @param[in] mods Bitfield describing which modifiers keys were held down
				*/
				virtual void invoke(int key, int scancode, int action, int mods);

			};

		}

	}

}