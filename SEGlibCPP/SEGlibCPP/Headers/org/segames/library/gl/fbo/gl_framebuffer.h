#pragma once
#include <org/segames/library/gl/texture/gl_texture.h>
#include <org/segames/library/gl/gl_bindable.h>
#include <org/segames/library/math/dimension_2.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					Interface for framebuffers.

					* @author	Philip Rosberg
					* @since	2019-06-16
					* @edited	2019-06-16
				*/
				class GLFramebuffer :
					public GLBindable
				{
				public:

					/*
						Destructor.
					*/
					virtual ~GLFramebuffer() = 0;

					/*
						Returns the id of the frame buffer.
					*/
					virtual GLuint getID() const = 0;

					/*
						Returns the size of the frame buffer.
					*/
					virtual const math::Dimension2i& getSize() const = 0;

					/*
						Returns a pointer to the color component of the frame buffer.
					*/
					virtual GLTexture* getColorComp() const = 0;

					/*
						Returns a pointer to the depth component of the frame buffer.
					*/
					virtual GLTexture* getDepthComp() const = 0;

					/*
						Sets the size of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						* @param[in] size The new size of the frame buffer
					*/
					virtual void setSize(const math::Dimension2i& size) = 0;

					/*
						Sets the color component of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						* @param[in] tex The texture to use
					*/
					virtual void setColorComp(GLTexture* tex) = 0;

					/*
						Sets the depth component of the framebuffer.
						NOTE! FBO must be rebuilt for effects to take place.
						NOTE! Should have internal format GL_DEPTH_COMPONENT
						* @param[in] tex The texture to use
					*/
					virtual void setDepthComp(GLTexture* tex) = 0;

					/*
						Binds this framebuffer to the OpenGL context.
					*/
					virtual const GLFramebuffer& bind() const override = 0;

					/*
						Releases this framebuffer from the OpenGL context.
					*/
					virtual const GLFramebuffer& release() const override = 0;

					/*
						Builds the framebuffer.
					*/
					virtual void build() = 0;

				};

			}

		}

	}

}