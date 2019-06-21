#pragma once
#include <org/segames/library/object.h>
#include <org/segames/library/gl/gl_bindable.h>
#include <org/segames/library/io/file.h>

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
					A standard OpenGL shader.
					Any OpenGL resource is deallocated on deletion of this object.
				
					* @author	Philip Rosberg
					* @since	2019-06-08
					* @edited	2019-06-09
				*/
				class SEG_API GLShader :
					public Object,
					public GLBindable
				{
				protected:

					/*
						The shader program id.
					*/
					GLuint m_id;

					/*
						The vertex shader data.
					*/
					std::unique_ptr<std::string> m_vData;

					/*
						The geometry shader data.
					*/
					std::unique_ptr<std::string> m_gData;

					/*
						The fragment shader data.
					*/
					std::unique_ptr<std::string> m_fData;

					/*
						Compiles the given source into a shader.
						* @param[in] type The type of the shader, GL_VERTEX_SHADER etc.
						* @param[in] name The identification name for error outputs
						* @param[in] src The shader source
					*/
					static GLuint createAndCompileShader(const GLenum type, const std::string& name, const std::string& src);

					/*
						Reads the content of the given file and returns it as a dynamically allocated string.
						* @param[in] file The file to read
					*/
					static std::string readSource(const io::File& file);

				public:

					/*
						Creates a new shader object.
					*/
					GLShader();

					/*
						Destructor.
						Handles release of OpenGL resources.
					*/
					virtual ~GLShader();
					
					/*
						Returns the id of the shader.
					*/
					virtual GLuint getID() const;

					/*
						Sets the stored vertex shader data.
						All deallocation responsibilities are given to this instance.
						* @param[in] src The source data
					*/
					virtual void setVertexData(const std::string& src);

					/*
						Sets the stored geometry shader data.
						All deallocation responsibilities are given to this instance.
						* @param[in] src The source data
					*/
					virtual void setGeometryData(const std::string& src);

					/*
						Sets the stored fragment shader data.
						All deallocation responsibilities are given to this instance.
						* @param[in] src The source data
					*/
					virtual void setFragmentData(const std::string& src);

					/*
						Loads vertex shader data from the file at the given path.
						* @param[in] path The path of the file to load from
					*/
					virtual void loadVertexData(const std::string& path);

					/*
						Loads geometry shader data from the file at the given path.
						* @param[in] path The path of the file to load from
					*/
					virtual void loadGeometryData(const std::string& path);

					/*
						Loads fragment shader data from the file at the given path.
						* @param[in] path The path of the file to load from
					*/
					virtual void loadFragmentData(const std::string& path);

					/*
						Loads vertex shader data from the file at the given path.
						* @param[in] file The file to load from
					*/
					virtual void loadVertexData(const io::File& file);

					/*
						Loads geometry shader data from the file at the given path.
						* @param[in] file The file to load from
					*/
					virtual void loadGeometryData(const io::File& file);

					/*
						Loads fragment shader data from the file at the given path.
						* @param[in] file The file to load from
					*/
					virtual void loadFragmentData(const io::File& file);

					/*
						Binds this shader to the OpenGL context.
					*/
					virtual const GLShader& bind() const override;

					/*
						Releases this shader (all shaders) from the OpenGL context.
					*/
					virtual const GLShader& release() const override;

					/*
						Uploads the currently set data. Returns true if new data was uploaded, otherwise false.
						Uses an identification name based on the time.
					*/
					virtual bool upload();

					/*
						Uploads the currently set data. Returns true if new data was uploaded, otherwise false.
						* @param[in] name Identification name of the shader for displaying in upload/compile errors
					*/
					virtual bool upload(const std::string& name);

				};

			}

		}

	}

}