#include <org/segames/library/glfw/glfw_window.h>
#include <org/segames/library/math/math.h>
#include <org/segames/library/exception.h>

using namespace org::segames::library::math;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				GLFWmonitor* GLFWWindow::getCurrentMonitorFor(GLFWwindow* window)
				{
					int numMonitors;
					GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);

					int x, y, w, h;
					glfwGetWindowPos(window, &x, &y);
					glfwGetWindowSize(window, &w, &h);

					int bestSize = 0;
					GLFWmonitor* bestMonitor = glfwGetPrimaryMonitor();

					int mx, my, mw, mh;
					for (int i = 0; i < numMonitors; i++)
					{
						glfwGetMonitorPos(monitors[i], &mx, &my);
						glfwGetMonitorPhysicalSize(monitors[i], &mw, &mh);

						int size = max(0, min(x + w, mx + mw) - max(x, mx))
							* max(0, min(y + h, my + mh) - max(y, my));
						
						if (size > bestSize)
						{
							bestSize = size;
							bestMonitor = monitors[i];
						}

					}

					return bestMonitor;
				}

				void GLFWWindow::setStandardCreationHints()
				{
					glfwDefaultWindowHints();
					glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
					glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#ifdef __APPLE__
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
					glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
					glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
				}

				void GLFWWindow::pollEvents()
				{
					glfwPollEvents();
				}

				bool GLFWWindow::sm_glProcLoaded = false;

				GLFWWindow::GLFWWindow() :
					GLFWWindow(setStandardCreationHints)
				{}

				GLFWWindow::GLFWWindow(GLFWwindowhintsfun hints) :
					m_iconifyListener(nullptr),
					m_keyListener(nullptr),
					m_mbListener(nullptr),
					m_mpListener(nullptr),
					m_sizeListener(nullptr)
				{
					if (!glfwInit())
						throw Exception("Could not initialize GLFW.", __FILE__, __LINE__);

					if (hints == nullptr)
						setStandardCreationHints();
					else
						hints();

					if ((m_window = glfwCreateWindow(800, 600, "", 0, 0)) == NULL)
					{
						glfwDefaultWindowHints();
						glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
						glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
						
						if ((m_window = glfwCreateWindow(800, 600, "", 0, 0)) == NULL)
							throw Exception("Could not create GLFW window.", __FILE__, __LINE__);
					}

					setListener(new GLFWIconificationListener());
					setListener(new GLFWKeyListener());
					setListener(new GLFWMouseButtonListener());
					setListener(new GLFWMousePositionListener());
					setListener(new GLFWWindowSizeListener());
				}

				GLFWWindow::~GLFWWindow()
				{
					if (m_iconifyListener) delete m_iconifyListener;
					if (m_keyListener) delete m_keyListener;
					if (m_mbListener) delete m_mbListener;
					if (m_mpListener) delete m_mpListener;
					if (m_sizeListener) delete m_sizeListener;

					for (auto itr = m_listeners.begin(); itr != m_listeners.end(); itr++)
						delete static_cast<GLFWListener<void>*>(itr->second);

					if(m_window != NULL) glfwDestroyWindow(m_window);
				}

				bool GLFWWindow::isCloseRequested() const
				{
					return glfwWindowShouldClose(m_window);
				}

				bool GLFWWindow::isPressed(int button) const
				{
					if (button <= GLFW_MOUSE_BUTTON_LAST)
					{
						if (m_mbListener)
							return m_mbListener->isPressed(button);
						else
							return false;
					}
					else if (m_keyListener)
						return m_keyListener->isPressed(button);
					else
						return false;
				}

				int GLFWWindow::getMX() const
				{
					if (m_mpListener)
						return m_mpListener->getMX();
					else
						return 0;
				}

				int GLFWWindow::getMY() const
				{
					if (m_mpListener)
						return m_mpListener->getMY();
					else
						return 0;
				}

				int GLFWWindow::getWidth() const
				{
					if (m_sizeListener)
						return m_sizeListener->getWidth();
					else
						return 0;
				}

				int GLFWWindow::getHeight() const
				{
					if (m_sizeListener)
						return m_sizeListener->getHeight();
					else
						return 0;
				}

				GLFWwindow* GLFWWindow::getWindowID() const
				{
					return m_window;
				}

				void GLFWWindow::setVisible(const bool flag)
				{
					if (flag)
						glfwShowWindow(m_window);
					else
						glfwHideWindow(m_window);
				}

				void GLFWWindow::setSize(const int width, const int height)
				{
					glfwSetWindowSize(m_window, width, height);
				}

				void GLFWWindow::setFullscreen(const bool flag)
				{
					int w, h;
					glfwGetWindowSize(m_window, &w, &h);

					if (flag)
						glfwSetWindowMonitor(m_window, getCurrentMonitorFor(m_window), 0, 0, w, h, GLFW_DONT_CARE);
					else
						glfwSetWindowMonitor(m_window, 0, 0, 0, w, h, GLFW_DONT_CARE);
				}

				void GLFWWindow::setPosition(const int x, const int y)
				{
					glfwSetWindowPos(m_window, x, y);
				}

				void GLFWWindow::setPositionCenter()
				{
					int w, h;
					const GLFWvidmode* vidMode = glfwGetVideoMode(getCurrentMonitorFor(m_window));
					glfwGetWindowSize(m_window, &w, &h);
					glfwSetWindowPos(m_window, (vidMode->width - w) / 2, (vidMode->height - h) / 2);
				}

				void GLFWWindow::setTitle(const std::string& title)
				{
					glfwSetWindowTitle(m_window, title.c_str());
				}

				std::unique_ptr<GLFWListener<GLFWIconificationListener>> GLFWWindow::setListener(GLFWListener<GLFWIconificationListener>* list)
				{
					std::unique_ptr<GLFWListener<GLFWIconificationListener>> old(m_iconifyListener);
					m_iconifyListener = dynamic_cast<GLFWIconificationListener*>(list);
					if(list != nullptr)
						m_iconifyListener->link(m_window);
					else
						GLFWIconificationListener::detach(m_window);
					return old;
				}

				std::unique_ptr<GLFWListener<GLFWKeyListener>> GLFWWindow::setListener(GLFWListener<GLFWKeyListener>* list)
				{
					std::unique_ptr<GLFWListener<GLFWKeyListener>> old(m_keyListener);
					m_keyListener = dynamic_cast<GLFWKeyListener*>(list);
					if (list != nullptr)
						m_keyListener->link(m_window);
					else
						GLFWKeyListener::detach(m_window);
					return old;
				}

				std::unique_ptr<GLFWListener<GLFWMouseButtonListener>> GLFWWindow::setListener(GLFWListener<GLFWMouseButtonListener>* list)
				{
					std::unique_ptr<GLFWListener<GLFWMouseButtonListener>> old(m_mbListener);
					m_mbListener = dynamic_cast<GLFWMouseButtonListener*>(list);
					if (list != nullptr)
						m_mbListener->link(m_window);
					else
						GLFWMouseButtonListener::detach(m_window);
					return old;
				}

				std::unique_ptr<GLFWListener<GLFWMousePositionListener>> GLFWWindow::setListener(GLFWListener<GLFWMousePositionListener>* list)
				{
					std::unique_ptr<GLFWListener<GLFWMousePositionListener>> old(m_mpListener);
					m_mpListener = dynamic_cast<GLFWMousePositionListener*>(list);
					if (list != nullptr)
						m_mpListener->link(m_window);
					else
						GLFWMousePositionListener::detach(m_window);
					return old;
				}

				std::unique_ptr<GLFWListener<GLFWWindowSizeListener>> GLFWWindow::setListener(GLFWListener<GLFWWindowSizeListener>* list)
				{
					std::unique_ptr<GLFWListener<GLFWWindowSizeListener>> old(m_sizeListener);
					m_sizeListener = dynamic_cast<GLFWWindowSizeListener*>(list);
					if (list != nullptr)
						m_sizeListener->link(m_window);
					else
						GLFWWindowSizeListener::detach(m_window);
					return old;
				}

				void GLFWWindow::makeContextCurrent()
				{
					glfwMakeContextCurrent(m_window);
					if (!sm_glProcLoaded)
						sm_glProcLoaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
				}

				void GLFWWindow::swapBuffers()
				{
					glfwSwapBuffers(m_window);
				}

			}

		}

	}

}