#pragma once
#include <org/segames/library/glfw/glfw_iconification_listener.h>
#include <org/segames/library/glfw/glfw_key_listener.h>
#include <org/segames/library/glfw/glfw_listener.h>
#include <org/segames/library/glfw/glfw_mouse_button_listener.h>
#include <org/segames/library/glfw/glfw_mouse_position_listener.h>
#include <org/segames/library/glfw/glfw_window_size_listener.h>
#include <org/segames/library/object.h>

#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				/*
					A signature for a function called when creating a window for setting window creation hints.
					No parameters.
				*/
				typedef void(*GLFWwindowhintsfun)();

				/*
					A GLFW based window with a creation similar to that of a Java JFrame.

					* @author	Philip Rosberg
					* @since	2019-05-09
					* @edited	2019-05-09
				*/
				class SEG_API GLFWWindow :
					public Object
				{
				public:

					/*
						Returns the current monitor of the given window.
						* @param[in] window The window to find the monitor of
					*/
					static GLFWmonitor* getCurrentMonitorFor(GLFWwindow* window);

					/*
						Sets the standard window creation hints for GLFW.
					*/
					static void setStandardCreationHints();

					/*
						Polls the GLFW events.
					*/
					static void pollEvents();

				private:

					/*
						True if the glad OpenGL loader has been initialized.
					*/
					static bool sm_glProcLoaded;

				protected:

					/*
						The window id.
					*/
					GLFWwindow* m_window;

					/*
						The window iconification listener.
					*/
					GLFWIconificationListener* m_iconifyListener;

					/*
						The key listener.
					*/
					GLFWKeyListener* m_keyListener;

					/*
						The mouse button listener.
					*/
					GLFWMouseButtonListener* m_mbListener;

					/*
						The mouse position listener.
					*/
					GLFWMousePositionListener* m_mpListener;

					/*
						The window size listener.
					*/
					GLFWWindowSizeListener* m_sizeListener;

					/*
						Other window listeners.
					*/
					std::unordered_map<std::string, void*> m_listeners;

				public:

					/*
						Creates a new GLFW window with the standard hints.
					*/
					GLFWWindow();

					/*
						Creates a new GLFW window with the given creation hints.
						* @param[in] 
					*/
					explicit GLFWWindow(GLFWwindowhintsfun hints);

					/*
						Destructor.
					*/
					virtual ~GLFWWindow();

					/*
						Returns true if the window is requested to close by the user.
					*/
					virtual bool isCloseRequested() const;

					/*
						Returns true if the button or key of the given id is pressed.
						* @param[in] button The GLFW button/key id to check
					*/
					virtual bool isPressed(int button) const;

					/*
						Returns the mouse x position.
					*/
					virtual int getMX() const;

					/*
						Returns the mouse y position.
					*/
					virtual int getMY() const;

					/*
						Returns the current width of the window.
					*/
					virtual int getWidth() const;

					/*
						Returns the current height of the window.
					*/
					virtual int getHeight() const;

					/*
						Returns the id of the GLFW window.
					*/
					virtual GLFWwindow* getWindowID() const;

					/*
						Sets if the window should be visible.
						* @param[in] flag True if the window should be set to visible, otherwise false
					*/
					virtual void setVisible(const bool flag);

					/*
						Sets the size of the window.
						* @param[in] width The width to set
						* @param[in] height The height to set
					*/
					virtual void setSize(const int width, const int height);

					/*
						Sets if the window should be in fullscreen mode, ie. use an entire monitor.
						* @param[in] flag True if the window should be set to fullscreen, otherwise false
					*/
					virtual void setFullscreen(const bool flag);

					/*
						Sets the position of the window relative to the current monitor.
						* @param[in] x The x position to set
						* @param[in] y The y position to set
					*/
					virtual void setPosition(const int x, const int y);

					/*
						Sets the position of the window to the center of the current monitor.
					*/
					virtual void setPositionCenter();

					/*
						Sets the title of the window.
						* @param[in] title The title to set
					*/
					virtual void setTitle(const std::string& title);

					/*
						Sets the given window listener and returns the last listener of this type.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					template<class sub_class>
					std::unique_ptr<GLFWListener<sub_class>> setListener(GLFWListener<sub_class>* list)
					{
						const std::string key = typeid(sub_class).name();
						auto pair = m_listeners.find(key);

						if (list != nullptr)
						{
							list->link(m_window);
							m_listeners.insert(std::pair<std::string, void*>(key, list));
						}
						else
						{
							sub_class::detach(m_window);
							m_listeners.erase(key);
						}

						if (pair != m_listeners.end())
							return std::unique_ptr<GLFWListener<sub_class>>((GLFWListener<sub_class>*)pair->second);
						else
							return std::unique_ptr<GLFWListener<sub_class>>(nullptr);
					}

					/*
						Sets the given window iconification listener and returns the last window iconification listener.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					std::unique_ptr<GLFWListener<GLFWIconificationListener>> setListener(GLFWListener<GLFWIconificationListener>* list);

					/*
						Sets the given window key listener and returns the last window key listener.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					std::unique_ptr<GLFWListener<GLFWKeyListener>> setListener(GLFWListener<GLFWKeyListener>* list);
					
					/*
						Sets the given mouse button listener and returns the last mouse button listener.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					std::unique_ptr<GLFWListener<GLFWMouseButtonListener>> setListener(GLFWListener<GLFWMouseButtonListener>* list);

					/*
						Sets the given mouse position listener and returns the last mouse position listener.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					std::unique_ptr<GLFWListener<GLFWMousePositionListener>> setListener(GLFWListener<GLFWMousePositionListener>* list);

					/*
						Sets the given window size listener and returns the last window size listener.
						All rights, such as deallocation, for the listener is transferred to this GLFWWindow instance.
						* @param[in] list The pointer of the listener
					*/
					std::unique_ptr<GLFWListener<GLFWWindowSizeListener>> setListener(GLFWListener<GLFWWindowSizeListener>* list);

					/*
						Makes this window's context the current one for OpenGL/OpenGLES rendering.
					*/
					virtual void makeContextCurrent();

					/*
						Swaps the window buffers.
					*/
					virtual void swapBuffers();

				};

			}

		}

	}

}