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

			/*
				Abstract class for actual frame buffers.

				* @author	Philip Rosberg
				* @since	2019-06-16
				* @edited	2019-06-30
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
				Dimension2i m_size;

				/*
					The color component texture.
				*/
				std::unique_ptr<GLTexture> m_color;

				/*
					The depth component texture.
				*/
				std::unique_ptr<GLTexture> m_depth;

				/*
					The additional color components.
				*/
				ArrayList<GLTexture*> m_additional_colors;

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
				explicit GLAbstractFramebuffer(GLTexture* color, GLTexture* depth, const Dimension2i& size);

				/*
					Copy constructor.
					* @param[in] obj The framebuffer to copy
				*/
				explicit GLAbstractFramebuffer(const GLAbstractFramebuffer& obj);

				/*
					Destructor.
				*/
				virtual ~GLAbstractFramebuffer() override;

				/*
					Returns the id of the frame buffer.
				*/
				virtual GLuint getID() const override;

				/*
					Returns the size of the frame buffer.
				*/
				virtual const Dimension2i& getSize() const override;

				/*
					Returns a pointer to the color component of the frame buffer.
				*/
				virtual GLTexture* getColorComp() const override;

				/*
					Returns a pointer to the depth component of the frame buffer.
				*/
				virtual GLTexture* getDepthComp() const override;

				/*
					Returns the list of additional color components.
				*/
				virtual const ArrayList<GLTexture*>& getAdditionalColorComp() const override;

				/*
					Sets the size of the framebuffer.
					NOTE! FBO must be rebuilt for effects to take place.
					* @param[in] size The new size of the frame buffer
				*/
				virtual void setSize(const Dimension2i& size) override;

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
					Adds an additional color component. Dellocated by this instance on destruction.
					NOTE! FBO must be rebuilt for effects to take place.
					NOTE! This operation does not replace the setColorComp()
					NOTE! The texture parameters should be set before the component is added
					* @param[in] tex The texture to use
				*/
				virtual void addAdditionalColorComp(GLTexture* tex) override;

				/*
					Removes and returns the additional color component of the given index.
					* @param[in] index The index of the additional color component
				*/
				virtual GLTexture* removeAdditionalColorComp(const int index) override;

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