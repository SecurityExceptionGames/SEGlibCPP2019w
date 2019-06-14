#pragma once
#include <org/segames/library/exception.h>

#include <glad/glad.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{
				
				/*
					An exception for OpenGL errors.

					* @author	Philip Rosberg
					* @since	2019-06-07
					* @edited	2019-06-07
				*/
				class SEG_API GLException :
					public Exception
				{
				private:

					/*
						Returns a string representation of the given error code.
						* @param[in] error The error code
					*/
					static std::string stringFromCode(const GLenum error);

					/*
						Message callback for OpenGL.
					*/
					static void GLAPIENTRY messageCallback(GLenum source,
						GLenum type,
						GLuint id,
						GLenum severity,
						GLsizei length,
						const GLchar* message,
						const void* userParam);

				public:

					/*
						Creates an OpenGL exception from the given error code.
						* @param[in] error The error code
					*/
					explicit GLException(const GLenum error);

					/*
						Creates an OpenGL exception with message.
						* @param[in] message The message to use for the exception
					*/
					explicit GLException(const std::string& message);

					/*
						Creates an OpenGL exception from the given error code.
						* @param[in] error The error code
						* @param[in] file The file in which the exception was thrown
						* @param[in] line The line at which the exception was thrown
					*/
					explicit GLException(const GLenum error, const char* file, const int line);

					/*
						Creates a OpenGL exception with the given message.
						* @param[in] message The message to use for the exception
						* @param[in] file The file in which the exception was thrown
						* @param[in] line The line at which the exception was thrown
					*/
					explicit GLException(const std::string& message, const char* file, const int line);

					/*
						Enables built in OpenGL debug callback.
					*/
					static void enableDebugCallback();

				};

			}

		}

	}

}