#pragma once
#include <org/segames/library/util/simplex_noise.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Implementation of fractal/fractional Brownian noise based on
					C++ code by Sebastien Rombauts (sebastien.rombauts@gmail.com).

					* @author	Philip Rosberg
					* @since	2019-05-26
					* @edited	2019-05-26
				*/
				class SEG_API FractalNoise final :
					public Object
				{
				private:

					/*
						Frequency ("width") of the first octave of noise (default to 1.0).
					*/
					double m_frequency;

					/*
						Amplitude ("height") of the first octave of noise (default to 1.0).
					*/
					double m_amplitude;

					/*
						Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
					*/
					double m_lacunarity;

					/*
						Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity).
					*/
					double m_persistence;

					/*
						The simplex noise generator.
					*/
					SimplexNoise m_noise;

				public:

					/*
						Creates a default fractal noise generator with a random seed.
					*/
					FractalNoise();

					/*
						Creates a default fractal noise generator with the given seed.
						* @param[in] seed The seed to use
					*/
					FractalNoise(const unsigned int seed);

					/*
						Creates a default fractal noise generator with a random seed and the given parameters.
						* @param[in] frequency Frequency ("width") of the first octave of noise (optional)
						* @param[in] amplitude Amplitude ("height") of the first octave of noise (optional)
						* @param[in] lacunarity Lacunarity specifies the frequency multiplier between successive octaves (optional)
						* @param[in] persistence Persistence is the loss of amplitude between successive octaves (optional)
					*/
					FractalNoise(double frequency = 1.0, double amplitude = 1.0, double lacunarity = 2.0, double persistence = 0.5);

					/*
						Creates a default fractal noise generator with the given seed and parameters.
						* @param[in] seed The seed to use
						* @param[in] frequency Frequency ("width") of the first octave of noise (optional)
						* @param[in] amplitude Amplitude ("height") of the first octave of noise (optional)
						* @param[in] lacunarity Lacunarity specifies the frequency multiplier between successive octaves (optional)
						* @param[in] persistence Persistence is the loss of amplitude between successive octaves (optional)
					*/
					FractalNoise(const unsigned int seed, double frequency = 1.0, double amplitude = 1.0, double lacunarity = 2.0, double persistence = 0.5);

					/*
						Generates a fractal/fractional Brownian noise value (1D).
						* @param[in] octaves The number of fraction of noise to sum
						* @param[in] x The x coordinate
						* @author Sebastien Rombauts
					*/
					double fractal(size_t octaves, double x) const;

					/*
						Generates a fractal/fractional Brownian noise value (2D).
						* @param[in] octaves The number of fraction of noise to sum
						* @param[in] x The x coordinate
						* @param[in] y The y coordinate
						* @author Sebastien Rombauts
					*/
					double fractal(size_t octaves, double x, double y) const;
					
					/*
						Generates a fractal/fractional Brownian noise value (3D).
						* @param[in] octaves The number of fraction of noise to sum
						* @param[in] x The x coordinate
						* @param[in] y The y coordinate
						* @param[in] z The z coordinate
						* @author Sebastien Rombauts
					*/
					double fractal(size_t octaves, double x, double y, double z) const;

				};

			}

		}

	}

}