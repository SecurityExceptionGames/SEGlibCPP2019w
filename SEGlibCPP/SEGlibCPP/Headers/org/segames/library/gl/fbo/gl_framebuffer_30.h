#pragma once
#include <org/segames/library/gl/fbo/gl_abstract_framebuffer.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Implementation of a OpenGL 3.0 framebuffer.

				* @author	Philip Rosberg
				* @since	2019-06-16
				* @edited	2019-06-16
			*/
			class SEG_API GLFramebuffer30 :
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
				GLFramebuffer30();

				/*
					Creates a GL30 frame buffer.
					* @param[in] color The color component of the framebuffer, responsibility is handed over to this instance
					* @param[in] depth The depth component of the framebuffer, responsibility is handed over to this instance
					* @param[in] size The size of the frame buffer
				*/
				explicit GLFramebuffer30(GLTexture* color, GLTexture* depth, const Dimension2i& size);

				/*
					Copy constructor.
					* @param[in] obj The framebuffer to copy
				*/
				explicit GLFramebuffer30(const GLFramebuffer30& obj);

				/*
					Destructor.
				*/
				virtual ~GLFramebuffer30() override;

				/*
					Binds this framebuffer to the OpenGL context.
				*/
				virtual const GLFramebuffer30& bind() const override;

				/*
					Releases this framebuffer from the OpenGL context.
				*/
				virtual const GLFramebuffer30& release() const override;

				/*
					Returns true if GL30 framebuffers are supported.
				*/
				static bool isSupported();

			};

		}

	}

}