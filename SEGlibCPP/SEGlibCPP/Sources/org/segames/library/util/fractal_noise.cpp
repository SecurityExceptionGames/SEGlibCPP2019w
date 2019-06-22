#include <org/segames/library/util/fractal_noise.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			FractalNoise::FractalNoise() :
				FractalNoise(1.0, 1.0, 2.0, 0.5)
			{}

			FractalNoise::FractalNoise(const unsigned int seed) :
				FractalNoise(seed, 1.0, 1.0, 2.0, 0.5)
			{}

			FractalNoise::FractalNoise(double frequency, double amplitude, double lacunarity, double persistence) :
				m_frequency(frequency),
				m_amplitude(amplitude),
				m_lacunarity(lacunarity),
				m_persistence(persistence),
				m_noise(SimplexNoise())
			{}

			FractalNoise::FractalNoise(const unsigned int seed, double frequency, double amplitude, double lacunarity, double persistence) :
				m_frequency(frequency),
				m_amplitude(amplitude),
				m_lacunarity(lacunarity),
				m_persistence(persistence),
				m_noise(SimplexNoise(seed))
			{}

			double FractalNoise::fractal(size_t octaves, double x) const
			{
				double output = 0.0;
				double denom = 0.0;
				double frequency = m_frequency;
				double amplitude = m_amplitude;

				for (size_t i = 0; i < octaves; i++) {
					output += (amplitude * m_noise.noise(x * frequency));
					denom += amplitude;

					frequency *= m_lacunarity;
					amplitude *= m_persistence;
				}

				return (output / denom);
			}

			double FractalNoise::fractal(size_t octaves, double x, double y) const
			{
				double output = 0.0;
				double denom = 0.0;
				double frequency = m_frequency;
				double amplitude = m_amplitude;

				for (size_t i = 0; i < octaves; i++) {
					output += (amplitude * m_noise.noise(x * frequency, y * frequency));
					denom += amplitude;

					frequency *= m_lacunarity;
					amplitude *= m_persistence;
				}

				return (output / denom);
			}

			double FractalNoise::fractal(size_t octaves, double x, double y, double z) const
			{
				double output = 0.0;
				double denom = 0.0;
				double frequency = m_frequency;
				double amplitude = m_amplitude;

				for (size_t i = 0; i < octaves; i++) {
					output += (amplitude * m_noise.noise(x * frequency, y * frequency, z * frequency));
					denom += amplitude;

					frequency *= m_lacunarity;
					amplitude *= m_persistence;
				}

				return (output / denom);
			}

		}

	}

}