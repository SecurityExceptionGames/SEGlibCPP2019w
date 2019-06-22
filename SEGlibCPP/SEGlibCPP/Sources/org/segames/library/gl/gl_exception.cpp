#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/core.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			std::string GLException::stringFromCode(const GLenum error)
			{
				switch (error)
				{
				case GL_INVALID_ENUM:
					return "GL_INVALID_ENUM";
				case GL_INVALID_VALUE:
					return "GL_INVALID_VALUE";
				case GL_INVALID_OPERATION:
					return "GL_INVALID_OPERATION";
				case GL_STACK_OVERFLOW:
					return "GL_STACK_OVERFLOW";
				case GL_STACK_UNDERFLOW:
					return "GL_STACK_UNDERFLOW";
				case GL_OUT_OF_MEMORY:
					return "GL_OUT_OF_MEMORY";
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					return "GL_INVALID_FRAMEBUFFER_OPERATION";
				case GL_CONTEXT_LOST:
					return "GL_CONTEXT_LOST";
				case GL_TABLE_TOO_LARGE:
					return "GL_TABLE_TOO_LARGE";
				default:
					return "???";
				}

			}

			void GLAPIENTRY GLException::messageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam)
			{
				Core::getErr() << "GL callback: " <<
					(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
					" type=" <<
					type <<
					" severity=" <<
					severity <<
					" message=\"" <<
					message <<
					"\"" <<
					std::endl;
			}

			GLException::GLException(const GLenum error) :
				GLException("OpenGL error " + stringFromCode(error))
			{}

			GLException::GLException(const std::string& message) :
				Exception(message)
			{}

			GLException::GLException(const GLenum error, const char* file, const int line) :
				GLException("OpenGL error " + stringFromCode(error), file, line)
			{}

			GLException::GLException(const std::string& message, const char* file, const int line) :
				Exception(message, file, line)
			{}

			void GLException::enableDebugCallback()
			{
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(messageCallback, NULL);
			}

		}

	}

}