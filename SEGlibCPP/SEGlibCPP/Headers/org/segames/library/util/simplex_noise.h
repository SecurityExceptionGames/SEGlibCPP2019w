#pragma once
#include <org/segames/library/object.h>

#include <memory>
#include <cstdint>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Implementation of simplex noise based on C++ code by Sebastien Rombauts 
					(sebastien.rombauts@gmail.com) and on the original Java code from 2012 by 
					Stefan Gustavson (stegu@itn.liu.se) and Peter Eastman (peastman@drizzle.stanford.edu).

					* @author	Philip Rosberg
					* @since	2019-05-26
					* @edited	2019-05-26
				*/
				class SEG_API SimplexNoise final :
					public Object
				{
				private:

					/*
						The seed of the noise.
					*/
					unsigned int m_seed;

					/*
						The local permutation table.
					*/
					std::shared_ptr<uint8_t[]> m_perm;

					/*
						Helper function to hash an integer using the permutation table.
						* @param[in] i The integer value to hash
						* @author Sebastien Rombauts
					*/
					uint8_t hash(const uint32_t i) const;

				private:

					/*
						Computes the largest integer value not greater than the double one.
						This method is faster than using (int32_t)std::floor(d).
						* @param[in] d The double to floor
						* @author Sebastien Rombauts
					*/
					static uint32_t fastFloor(const double d);

					/*
						Helper function to compute a gradients-dot-residual vector (1D).
						* @param[in] hash The hash value
						* @param[in] x The x distance to the corner
						* @author Sebastien Rombauts
					*/
					static double grad(uint32_t hash, const double x);

					/*
						Helper function to compute a gradients-dot-residual vector (2D).
						* @param[in] hash The hash value
						* @param[in] x The x distance to the corner
						* @param[in] y The y distance to the corner
						* @author Sebastien Rombauts
					*/
					static double grad(uint32_t hash, const double x, const double y);

					/*
						Helper function to compute a gradients-dot-residual vector (3D).
						* @param[in] hash The hash value
						* @param[in] x The x distance to the corner
						* @param[in] y The y distance to the corner
						* @param[in] z The z distance to the corner
						* @author Sebastien Rombauts
					*/
					static double grad(uint32_t hash, const double x, const double y, const double z);

				public:

					/*
						Creates a new simplex noise instance with a random seed.
					*/
					SimplexNoise();

					/*
						Creates a new simplex noise instance with a given seed.
						* @param[in] seed The seed to use
					*/
					explicit SimplexNoise(const unsigned int seed);

					/*
						Creates a new simplex noise instance with a given seed and the given amount of random swaps of the permutation table.
						* @param[in] seed The seed to use
						* @param[in] numSwaps The amount of swaps to perform in the permutation table
					*/
					explicit SimplexNoise(const unsigned int seed, const int numSwaps);

					/*
						Copies the given simplex noise instance.
						* @param[in] obj The simplex noise instance to copy
					*/
					SimplexNoise(const SimplexNoise& obj);

					/*
						Returns the seed of the noise.
					*/
					unsigned int getSeed() const;

					/*
						Generates a simplex noise value (1D).
						* @param[in] x The x coordinate
						* @author Sebastien Rombauts
					*/
					double noise(const double x) const;

					/*
						Generates a simplex noise value (2D).
						* @param[in] x The x coordinate
						* @param[in] y The y coordinate
						* @author Sebastien Rombauts
					*/
					double noise(const double x, const double y) const;

					/*
						Generates a simplex noise value (3D).
						* @param[in] x The x coordinate
						* @param[in] y The y coordinate
						* @param[in] z The z coordinate
						* @author Sebastien Rombauts
					*/
					double noise(const double x, const double y, const double z) const;

					/*
						Set operator override.
						* @param[in] obj The simplex noise instance to copy
					*/
					SimplexNoise& operator=(const SimplexNoise& obj);

				};

			}

		}

	}

}