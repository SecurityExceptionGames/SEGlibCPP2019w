#pragma once
#include <org/segames/library/dllmain.h>

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
					A class storing core OpenGL constants and such.

					* @author	Philip Rosberg
					* @since	2019-06-12
					* @edited	2019-06-12
				*/
				class SEG_API GLCore final
				{
				private:

					/*
						The OpenGL version.
					*/
					static float m_version;

				public:

					/*
						Returns the OpenGL version.
					*/
					static float glVersion();

				};

			}

		}

	}

}