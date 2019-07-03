#pragma once
#include <org/segames/library/gl/fbo/gl_abstract_framebuffer.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A wrapper class for easy multi-version framebuffers.

				* @author	Philip Rosberg
				* @since	2019-06-16
				* @edited	2019-06-30
			*/
			class SEG_API GLFramebufferWrapper :
				public GLFramebuffer
			{
			protected:

				/*
					The actual buffer.
				*/
				std::unique_ptr<GLAbstractFramebuffer> m_buffer;

				/*
					Returns a new instance of a type of framebuffer that is supported.
					* @param[in] color The color component of the framebuffer, responsibility is handed over to the returned instance
					* @param[in] depth The depth component of the framebuffer, responsibility is handed over to the returned instance
					* @param[in] size The initial size of the framebuffer
				*/
				static GLAbstractFramebuffer* newSupportedFBO(GLTexture* color, GLTexture* depth, const Dimension2i& size);

			public:
					
				/*
					Creates a zeroed/empty framebuffer.
				*/
				GLFramebufferWrapper();

				/*
					Creates a frame buffer with the given components.
					* @param[in] color True if a color component should be present
					* @param[in] depth True if a depth component should be present
					* @param[in] size The initial size of the framebuffer
				*/
				explicit GLFramebufferWrapper(const bool color, const bool depth, const Dimension2i& size);

				/*
					Creates a frame buffer with the given components.
					* @param[in] color The color component of the framebuffer, responsibility is handed over to this instance
					* @param[in] depth The depth component of the framebuffer, responsibility is handed over to this instance
					* @param[in] size The initial size of the framebuffer
				*/
				explicit GLFramebufferWrapper(GLTexture* color, GLTexture* depth, const Dimension2i& size);

				/*
					Copy constructor.
					* @param[in] obj Framebuffer to copy
				*/
				explicit GLFramebufferWrapper(const GLFramebufferWrapper& obj);
					
				/*
					Destructor.
				*/
				virtual ~GLFramebufferWrapper() override;

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
					Returns the backing framebuffer.
				*/
				virtual GLAbstractFramebuffer* getBuffer() const;

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
				virtual const GLFramebufferWrapper& bind() const override;

				/*
					Releases this framebuffer from the OpenGL context.
				*/
				virtual const GLFramebufferWrapper& release() const override;

				/*
					Builds the framebuffer.
				*/
				virtual void build() override;

				/*
					Returns true if any framebuffer is supported.
				*/
				static bool isSupported();

			};

		}

	}

}