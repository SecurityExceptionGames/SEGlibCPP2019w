#pragma once
#include <cstddef>

namespace org
{

	namespace segames
	{

		namespace library
		{

			constexpr char BIG_ENDIAN		= 0b00000001;
			constexpr char LITTLE_ENDIAN	= 0b00000010;
			constexpr char SYSTEM_ENDIAN	= 0b00000100;
			
			/*
				Class/Namespace for system related functions.

				* @author	Philip Rosberg
				* @since	2019-01-25
				* @since	2019-01-25
			*/
			class System final
			{
			public:

				/*
					Returns true if the system is big endian and false if the system is little endian.
				*/
				static constexpr inline bool isBigEndian()
				{
					unsigned short v = 1;
					return *((char*)&v) != 1;
				}

			};
			
			/*
				Changes the byte-order of the given memory
				* @param[in] len The length of the memory in bytes
				* @param[in] ptr The pointer to the memory block
				* @param[in] mask The mask describing the way the order should be changed
			*/
			template<typename T>
			inline T* bo_cast(size_t len, void* ptr, char mask)
			{
				if (mask & SYSTEM_ENDIAN)
					return bo_cast<T>(len, ptr, (mask ^ SYSTEM_ENDIAN) | (System::isBigEndian() ? BIG_ENDIAN : LITTLE_ENDIAN));
				else if (mask & LITTLE_ENDIAN && mask & BIG_ENDIAN)
				{
					char* const pos = static_cast<char*>(ptr);
					for (size_t i = 0; i < len; i += sizeof(T))
						for (size_t c = 0; c < sizeof(T) / 2; c++)
						{
							char* const a = pos + (i + c);
							char* const b = pos + (i + sizeof(T) - c - 1);
							const char temp = *a;
							*a = *b;
							*b = temp;
						}

				}
				return static_cast<T*>(ptr);
			}

		}

	}

}