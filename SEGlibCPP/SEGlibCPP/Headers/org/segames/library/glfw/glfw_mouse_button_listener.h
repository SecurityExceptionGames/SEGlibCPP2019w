#pragma once
#include <org/segames/library/glfw/glfw_listener.h>
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				/*
					A listener for detecting when the cursor buttons are pressed.

					* @author	Philip Rosberg
					* @since	2019-05-11
					* @edited	2019-05-11
				*/
				class SEG_API GLFWMouseButtonListener :
					public Object,
					public GLFWListener<GLFWMouseButtonListener>
				{
				private:

					/*
						Callback for GLFW.
					*/
					static void callback(GLFWwindow* window, int button, int action, int mods);

				public:

					/*
						Unlinks the callback for the given window.
						* @param[in] window The GLFW window id
					*/
					static void detach(GLFWwindow* window);

				protected:

					/*
						The mouse buttons toggles.
					*/
					bool m_buttons[8];

					/*
						Links this listener to GLFW.
						* @param[in] window The GLFW window id
					*/
					virtual void linkGLFW(GLFWwindow* window) override;

				public:

					/*
						Returns true ifthe given mouse button is pressed.
						* @param[in] 
					*/
					virtual bool isPressed(int button) const;

					/*
						The method that is called when the listener is activated.
						* @param[in] button The mouse button that was pressed or released
						* @param[in] action One of GLFW_PRESS of GLFW_RELEASE
						* @param[in] mods Bitfield describing which modifiers keys were held down
					*/
					virtual void invoke(int button, int action, int mods);

				};

			}

		}

	}

}