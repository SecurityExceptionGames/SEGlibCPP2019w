#pragma once
#include <org/segames/library/glfw/glfw_listener.h>
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A listener for detecting the cursor position relative to a window.

				* @author	Philip Rosberg
				* @since	2019-05-11
				* @edited	2019-05-11
			*/
			class SEG_API GLFWMousePositionListener :
				public Object,
				public GLFWListener<GLFWMousePositionListener>
			{
			private:

				/*
					Callback for GLFW.
				*/
				static void callback(GLFWwindow* window, double mx, double my);

			public:

				/*
					Unlinks the callback for the given window.
					* @param[in] window The GLFW window id
				*/
				static void detach(GLFWwindow* window);

			protected:

				/*
					Mouse x position.
				*/
				int m_mx;

				/*
					Mouse y position.
				*/
				int m_my;

				/*
					Links this listener to GLFW.
					* @param[in] window The GLFW window id
				*/
				virtual void linkGLFW(GLFWwindow* window) override;

			public:

				/*
					Returns the x position of the cursor relative to the window.
				*/
				virtual int getMX() const;

				/*
					Returns the y position of the cursor relative to the window.
				*/
				virtual int getMY() const;

				/*
					The method that is called when the listener is activated.
					* @param[in] mx The mouse x position
					* @param[in] my The mouse y position
				*/
				virtual void invoke(double mx, double my);

			};

		}

	}

}