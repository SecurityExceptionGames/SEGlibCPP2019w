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
					A listener for detecting when a window is iconified (minimized).

					* @author	Philip Rosberg
					* @since	2019-05-11
					* @edited	2019-05-11
				*/
				class SEG_API GLFWIconificationListener :
					public Object,
					public GLFWListener<GLFWIconificationListener>
				{
				private:

					/*
						Callback for GLFW.
					*/
					static void callback(GLFWwindow* window, int flag);

				public:

					/*
						Unlinks the callback for the given window.
						* @param[in] window The GLFW window id
					*/
					static void detach(GLFWwindow* window);

				protected:

					/*
						True if the window is iconified.
					*/
					bool m_iconified;

					/*
						Links this listener to GLFW.
						* @param[in] window The GLFW window id
					*/
					virtual void linkGLFW(GLFWwindow* window) override;

				public:

					/*
						Returns true if the window is iconified.
					*/
					virtual bool isIconified() const;

					/*
						The method that is called when the listener is activated.
						* @param[in] flag True if the window is iconified
					*/
					virtual void invoke(bool flag);

				};

			}

		}

	}

}