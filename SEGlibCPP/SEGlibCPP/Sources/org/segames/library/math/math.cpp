#include <org/segames/library/math/math.h>
#include <org/segames/library/util/random.h>

using namespace org::segames::library::util;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace math
			{

				struct {
					Random<float> rng32;
					Random<double> rng64;
				} rngInfo;

				float randomf()
				{
					return rngInfo.rng32.random();
				}

				double random()
				{
					return rngInfo.rng64.random();
				}

			}

		}

	}

}