#pragma once
#include <org/segames/library/gl/fbo/gl_abstract_framebuffer.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Implementation of a OpenGL EXT framebuffer for older systems.

				* @author	Philip Rosberg
				* @since	2019-06-16
				* @edited	2019-06-16
			*/
			class SEG_API GLFramebufferEXT :
				public GLAbstractFramebuffer
			{
			protected:

				/*
					Links the frame buffer.
				*/
				virtual void buildFBO() override;

			public:

				/*
					Creates a zeroed/empty framebuffer.
				*/
				GLFramebufferEXT();

				/*
					Creates a EXT frame buffer.
					* @param[in] color The color component of the framebuffer, responsibility is handed over to this instance
					* @param[in] depth The depth component of the framebuffer, responsibility is handed over to this instance
					* @param[in] size The size of the frame buffer
				*/
				explicit GLFramebufferEXT(GLTexture* color, GLTexture* depth, const Dimension2i& size);

				/*
					Copy constructor.
					* @param[in] obj The framebuffer to copy
				*/
				explicit GLFramebufferEXT(const GLFramebufferEXT& obj);

				/*
					Destructor.
				*/
				virtual ~GLFramebufferEXT() override;

				/*
					Binds this framebuffer to the OpenGL context.
				*/
				virtual const GLFramebufferEXT& bind() const override;

				/*
					Releases this framebuffer from the OpenGL context.
				*/
				virtual const GLFramebufferEXT& release() const override;

				/*
					Returns true if EXT framebuffers are supported.
				*/
				static bool isSupported();

			};

		}

	}

}