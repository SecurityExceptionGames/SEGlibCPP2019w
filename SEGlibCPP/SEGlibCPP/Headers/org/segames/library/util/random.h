#pragma once
#include <org/segames/library/util/timer.h>

#include <random>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					A random number generator wrapper, template should either be "float", "double" or "long double"

					* @author	Philip Rosberg
					* @since	2018-09-21
					* @edited	2018-09-21
				*/
				template<typename T> 
				class Random :
					public Object
				{
				private:

					/*
						The random number generator
					*/
					std::default_random_engine generator;

					/*
						The distribution control for the generator
					*/
					std::uniform_real_distribution<T> distribution;

				public:

					/*
						Creates a random number generator using the time as the seed
					*/
					Random() :
						Random((unsigned int)Timer::milliTime())
					{}

					/*
						Creates a random number generator using the given seed
						* @param[in] seed The seed to use
					*/
					Random(const unsigned int seed) :
						distribution(0, 1)
					{
						generator.seed(seed);
					}

					/*
						Returns the next random value in the range [0, 1)
					*/
					inline virtual T random()
					{
						return distribution(generator);
					}

					/*
						Returns a random int in the given range [min, max]
						* @param[in] min The minimum value
						* @param[in] max The maximum value
					*/
					inline virtual int randomInt(int min, int max)
					{
						return (int)(random() * (max - min + 1) + min);
					}

				};

			}

		}

	}

}