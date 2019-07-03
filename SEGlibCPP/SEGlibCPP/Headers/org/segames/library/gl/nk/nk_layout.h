#pragma once
#include <org/segames/library/dllmain.h>

#define NK_INCLUDE_FIXED_TYPES
#include <nuklear/nuklear.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An abstract class/interface for handling nuklear user 
				interface layouts.

				* @author	Philip Rosberg
				* @since	2019-06-30
				* @edited	2019-06-30
			*/
			class SEG_API NkLayout
			{
			private:

				/*
					True if the layout has been initialized.
				*/
				bool m_initialized;
			
			protected:
				
				/*
					The initialization method of the interface structure (if any needs to be done)
					Return true when finished initializing.
					* @param[in] ctx The nuklear context pointer
				*/
				virtual bool initialize(nk_context* ctx) = 0;

				/*
					The update method of the interface structure, that builds the interface using 
					nuklear methods.
					* @param[in] ctx The nuklear context pointer
				*/
				virtual void layout(nk_context* ctx) = 0;

			public:
				
				/*
					The internal update method called from NkInstance.
					* @param[in] ctx The nuklear context pointer
				*/
				virtual void updateInternal(nk_context* ctx);

			};

		}

	}

}