#pragma once
#include <org/segames/library/gl/fbo/gl_framebuffer.h>
#include <org/segames/library/object.h>

#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					Abstract class for actual frame buffers.

					* @author	Philip Rosberg
					* @since	2019-06-16
					* @edited	2019-06-16
				*/
				class SEG_API GLAbstractFramebuffer :
					public GLFramebuffer,
					public Object
				{
				protected:

					/*
						True if the texture[s] should be reset/rescaled on build.
					*/
					bool m_resetTexture;

					/*
						The framebuffer id.
					*/
					GLuint m_id;

					/*
						Size of the framebuffer.
					*/
					math::Dimension2i m_size;

					/*
						The color component texture.
					*/
					std::unique_ptr<GLTexture> m_color;

					/*
						The depth component texture.
					*/
					std::unique_ptr<GLTexture> m_depth;

					/*
						Links the frame buffer.
					*/
					virtual void buildFBO() = 0;

					/*
						Creates the textures for the buffer.
						* @param[out] changed Set to true if anything changed with the textures
					*/
					virtual void buildTextures(bool* changed);

				public:

					/*
						Creates an abstract frame buffer.
						* @param[in] color The color component of the framebuffer, responsibility is handed over to this instance
						* @param[in] depth The depth component of the framebuffer, responsibility is handed over to this instance
						* @param[in] size The size of the frame buffer
					*/
					explicit GLAbstractFramebuffer(GLTexture* color, GLTexture* depth, const math::Dimension2i& size);

					/*
						Copy constructor.
						* @param[in] obj The framebuffer to copy
					*/
					explicit GLAbstractFramebuffer(const GLAbstractFramebuffer& obj);

					/*
						Destructor.
					*/
					virtual ~GLAbstractFramebuffer() override = 0;

					/*
						Returns the id of the frame buffer.
					*/
					virtual GLuint getID() const override;

					/*
						Returns the size of the frame buffer.
					*/
					virtual const math::Dimension2i& getSize() const override;

					/*
						Returns a pointer to the color component of the frame buffer.
					*/
					virtual GLTexture* getColorComp() const override;

					/*
						Returns a pointer to the depth component of the frame buffer.
					*/
					virtual GLTexture* getDepthComp() const override;

					/*
						Sets the size of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						* @param[in] size The new size of the frame buffer
					*/
					virtual void setSize(const math::Dimension2i& size) override;

					/*
						Sets the color component of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						* @param[in] tex The texture to use
					*/
					virtual void setColorComp(GLTexture* tex) override;

					/*
						Sets the depth component of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						NOTE! Should have internal format GL_DEPTH_COMPONENT
						* @param[in] tex The texture to use
					*/
					virtual void setDepthComp(GLTexture* tex) override;

					/*
						Binds this framebuffer to the OpenGL context.
					*/
					virtual const GLAbstractFramebuffer& bind() const override = 0;

					/*
						Releases this framebuffer from the OpenGL context.
					*/
					virtual const GLAbstractFramebuffer& release() const override = 0;

					/*
						Builds the framebuffer.
					*/
					virtual void build() override;

				};

			}

		}

	}

}