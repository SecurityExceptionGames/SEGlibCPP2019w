#pragma once
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{
				
				template<typename T>
				class HeapBlock :
					Object
				{
				protected:

					/*
						The current size of the memory
					*/
					size_t size;

					/*
						The memory pointer
					*/
					T* memory;

				public:



				};

			}

		}

	}

}