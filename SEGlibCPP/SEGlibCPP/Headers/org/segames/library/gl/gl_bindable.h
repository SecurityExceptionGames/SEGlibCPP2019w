#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace gl
			{

				/*
					Interface for bindable OpenGL objects such as buffers, textures, etc.

					* @author	Philip Rosberg
					* @since	2019-06-04
					* @edited	2019-06-04
				*/
				class GLBindable
				{
				public:

					/*
						Binds this object to the OpenGL context.
					*/
					virtual const GLBindable& bind() const = 0;

					/*
						Releases this object from the OpenGL context.
					*/
					virtual const GLBindable& release() const = 0;

				};

			}

		}

	}

}