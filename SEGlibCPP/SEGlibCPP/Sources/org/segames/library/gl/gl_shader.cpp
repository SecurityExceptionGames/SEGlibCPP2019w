#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/io/file_not_found_exception.h>
#include <org/segames/library/util/timer.h>

#include <fstream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLuint GLShader::createAndCompileShader(const GLenum type, const std::string& name, const std::string& src)
			{
				GLuint id = glCreateShader(type);
				const char* str = src.c_str();
				GLint size = static_cast<GLint>(src.length());
				glShaderSource(id, 1, &str, &size);
				glCompileShader(id);
					
				GLint status;
				glGetShaderiv(id, GL_COMPILE_STATUS, &status);
				if (status == FALSE)
				{
					std::unique_ptr<char[]> buf(new char[0x00100000]);
					glGetShaderInfoLog(id, 0x00100000, NULL, buf.get());
					glDeleteShader(id);
						
					throw GLException("Shader \"" + name + "\" did not compile\n" + std::string(buf.get()));
				}

				return id;
			}

			std::string GLShader::readSource(const File& file)
			{
				if (!file.exists())
					throw FileNotFoundException(file.getPath());

				std::ifstream input(file.getPath(), std::fstream::binary);
				if (!input.good())
					throw IOException("Could not read file \"" + file.getPath() + "\"");

				std::unique_ptr<char[]> buf(new char[file.length()]);
				input.read(buf.get(), file.length());

				return std::string(buf.get(), file.length());
			}

			GLShader::GLShader() :
				m_id(0),
				m_vData(nullptr),
				m_gData(nullptr),
				m_fData(nullptr)
			{}

			GLShader::~GLShader()
			{
				if (m_id)
					glDeleteProgram(m_id);
			}

			GLuint GLShader::getID() const
			{
				return m_id;
			}

			void GLShader::setVertexData(const std::string& src)
			{
				std::unique_ptr<std::string> temp(new std::string(src));
				m_vData.swap(temp);
			}

			void GLShader::setGeometryData(const std::string& src)
			{
				std::unique_ptr<std::string> temp(new std::string(src));
				m_gData.swap(temp);
			}

			void GLShader::setFragmentData(const std::string& src)
			{
				std::unique_ptr<std::string> temp(new std::string(src));
				m_fData.swap(temp);
			}

			void GLShader::loadVertexData(const std::string& path)
			{
				loadVertexData(File(path));
			}

			void GLShader::loadGeometryData(const std::string& path)
			{
				loadGeometryData(File(path));
			}

			void GLShader::loadFragmentData(const std::string& path)
			{
				loadFragmentData(File(path));
			}

			void GLShader::loadVertexData(const File& file)
			{
				setVertexData(readSource(file));
			}

			void GLShader::loadGeometryData(const File& file)
			{
				setGeometryData(readSource(file));
			}

			void GLShader::loadFragmentData(const File& file)
			{
				setFragmentData(readSource(file));
			}
				
			const GLShader& GLShader::bind() const
			{
				glUseProgram(m_id);
				return *this;
			}

			const GLShader& GLShader::release() const
			{
				glUseProgram(GL_NONE);
				return *this;
			}

			bool GLShader::upload()
			{
				size_t time = Timer::milliTime();
				size_t millis = time % 1000;
				size_t secs = (time / 1000) % 60;
				size_t mins = (time / 60000) % 60;
				size_t hours = (time / 3600000) % 24;
				return upload(std::string("Shader # ") += 
					(std::to_string(hours) += "h # ") +=
					(std::to_string(mins) + "m # ") += 
					(std::to_string(secs) += ".") +=
					std::to_string(millis) += "s");
			}

			bool GLShader::upload(const std::string& name)
			{
				bool changed = false;
				GLuint id = m_id;
				GLuint vertex = 0, geometry = 0, fragment = 0;

				if (!id)
					id = glCreateProgram();

				if (m_vData)
					glAttachShader(id, vertex = createAndCompileShader(GL_VERTEX_SHADER, name, *m_vData));

				if (m_gData)
					glAttachShader(id, geometry = createAndCompileShader(GL_GEOMETRY_SHADER, name, *m_gData));

				if (m_fData)
					glAttachShader(id, fragment = createAndCompileShader(GL_FRAGMENT_SHADER, name, *m_fData));

				if ((changed = vertex || geometry || fragment))
				{
					GLint status;

					glLinkProgram(id);
					glGetProgramiv(id, GL_LINK_STATUS, &status);
					if (status == GL_FALSE)
					{
						std::unique_ptr<char[]> buf(new char[0x00100000]);
						glGetShaderInfoLog(id, 0x00100000, NULL, buf.get());

						glDeleteProgram(id);
						if (vertex) glDeleteShader(vertex);
						if (geometry) glDeleteShader(geometry);
						if (fragment) glDeleteShader(fragment);

						throw GLException("Could not link program \"" + name + "\" " + std::string(buf.get()));
					}

					glValidateProgram(id);
					glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
					if (status == GL_FALSE)
					{
						std::unique_ptr<char[]> buf(new char[0x00100000]);
						glGetShaderInfoLog(id, 0x00100000, NULL, buf.get());

						glDeleteProgram(id);
						if (vertex) glDeleteShader(vertex);
						if (geometry) glDeleteShader(geometry);
						if (fragment) glDeleteShader(fragment);

						throw GLException("Could not validate program \"" + name + "\" " + std::string(buf.get()));
					}

					if (vertex) { glDetachShader(id, vertex); glDeleteShader(vertex); };
					if (geometry) { glDetachShader(id, geometry); glDeleteShader(geometry); };
					if (fragment) { glDetachShader(id, fragment); glDeleteShader(fragment); };

					m_id = id;
				}
				
				return changed;
			}

		}

	}

}