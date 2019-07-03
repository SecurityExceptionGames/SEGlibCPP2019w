#include <org/segames/library/gl/nk/nk_layout.h>

namespace org
{

	namespace segames
	{

		namespace library
		{
		
			void NkLayout::updateInternal(nk_context* ctx)
			{
				if (!m_initialized)
				{
					m_initialized = initialize(ctx);
					if (m_initialized)
						layout(ctx);
				}
				else
					layout(ctx);
			}

		}

	}

}