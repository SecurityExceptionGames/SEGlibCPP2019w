#pragma once
#ifndef GLFW_INCLUDED
#define GLFW_DLL
#include <glad/glad.h>
#include <glfw/glfw3.h>
#define GLFW_INCLUDED
#endif

#include <unordered_map>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace glfw
			{

				/*
					Abstract super class for GLFW event listeners.

					* @author	Philip Rosberg
					* @since	2019-05-08
					* @edited	2019-05-08
				*/
				template<class sub_class>
				class GLFWListener
				{
				protected:

					/*
						A map with references to the various listeners.
					*/
					static std::unordered_map<GLFWwindow*, sub_class*> m_listeners;

				protected:

					/*
						The ID of the window which this listener is linked to.
					*/
					GLFWwindow* m_win;

					/*
						Links this listener to GLFW
						* @param[in] win The GLFW window id
					*/
					virtual void linkGLFW(GLFWwindow* win) = 0;

				public:

					/*
						Creates a non-linked GLFW listener.
					*/
					GLFWListener() :
						m_win(nullptr)
					{}

					/*
						Destroys the listener and removes the map references to it.
					*/
					virtual ~GLFWListener()
					{
						//m_listeners.erase(m_win);
					}

					/*
						Adds this listener to the listeners map and calls linkGLFW().
						* @param[in] win The GLFW window id
					*/
					virtual void link(GLFWwindow* win)
					{
						m_listeners.insert(std::pair<GLFWwindow*, sub_class*>(win, (sub_class*)this));
						linkGLFW(win);
					}

				};

				template<class sub_class>
				std::unordered_map<GLFWwindow*, sub_class*> GLFWListener<sub_class>::m_listeners;

			}

		}

	}

}