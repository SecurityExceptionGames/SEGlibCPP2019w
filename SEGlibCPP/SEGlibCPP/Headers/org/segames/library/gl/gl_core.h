#pragma once
#include <org/segames/library/dllmain.h>

#include <glad/glad.h>
#include <unordered_set>
#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
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

				/*
					The avaliable OpenGL extensions.
				*/
				static std::unique_ptr<std::unordered_set<std::string>> m_extensions;

			public:

				/*
					Returns the OpenGL version.
					Loads the version from OpenGL on first call.
				*/
				static float glVersion();

				/*
					Returns true if the given OpenGL extension is present.
				*/
				static bool hasExtension(const std::string& ext);

				/*
					Returns the present OpenGL extensions.
					Loads the extensions from OpenGL on first call.
				*/
				static const std::unordered_set<std::string>& glExtensions();

			};

		}

	}

}