#include <org/segames/library/math/math.h>

namespace org
{

	namespace segames
	{

		namespace library
		{
			thread_local Math::RngInfo Math::m_rngInfo = { Random<float>(), Random<double>() };

			float Math::randomf()
			{
				return m_rngInfo.rng32.random();
			}

			double Math::random()
			{
				return m_rngInfo.rng64.random();
			}

		}

	}

}