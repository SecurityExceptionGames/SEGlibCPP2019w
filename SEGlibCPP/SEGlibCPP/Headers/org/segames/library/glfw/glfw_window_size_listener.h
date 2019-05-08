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
					A window size listener for GLFW

					* @author	Philip Rosberg
					* @since	2019-05-08
					* @edited	2019-05-08
				*/
				class SEG_API GLFWWindowSizeListener :
					public Object,
					public GLFWListener<GLFWWindowSizeListener>
				{
				protected:

					/*
						Window width.
					*/
					int m_w;

					/*
						Window height.
					*/
					int m_h;

					/*
						Links this listener to GLFW
						* @param[in] win The GLFW window id
					*/
					virtual void linkGLFW(GLFWwindow* win) override;

					/*
						Callback for GLFW.
					*/
					static void callback(GLFWwindow* win, int w, int h);

				public:

					/*
						Returns the window width.
					*/
					virtual int width() const;

					/*
						Returns the window height.
					*/
					virtual int height() const;

				};

			}

		}

	}

}