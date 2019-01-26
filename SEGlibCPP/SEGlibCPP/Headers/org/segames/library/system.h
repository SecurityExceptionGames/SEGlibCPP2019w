#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Class/Namespace for system related functions

				* @author	Philip Rosberg
				* @since	2019-01-25
				* @since	2019-01-25
			*/
			class System
			{
			public:

				/*
					Returns true if the system is big endian and false if the system is little endian
				*/
				static constexpr inline bool isBigEndian()
				{
					unsigned short v = 1;
					return *((char*)&v) != 1;
				}

			};

		}

	}

}