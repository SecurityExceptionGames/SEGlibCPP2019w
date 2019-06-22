#include <org/segames/library/gl/texture/gl_s3tc_texture.h>
#include <org/segames/library/gl/gl_core.h>
#include <org/segames/library/io/file_not_found_exception.h>
#include <org/segames/library/io/file.h>
#include <org/segames/library/math/math.h>
#include <org/segames/library/system.h>

#include <fstream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			GLenum GLS3TCTexture::asGLFormat(const int fourCC)
			{
				switch (fourCC)
				{
				case 827611204:
					return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				case 861165636:
					return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				case 894720068:
					return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				default:
					return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				}

			}

			GLS3TCTexture::GLS3TCTexture() :
				GLPhysicalTexture(),
				m_mipmapLevels(0),
				m_mipmapSizes(nullptr),
				m_mipmapData(nullptr)
			{}

			GLS3TCTexture::GLS3TCTexture(const std::string& path) :
				GLPhysicalTexture(),
				m_mipmapLevels(0),
				m_mipmapSizes(nullptr),
				m_mipmapData(nullptr)
			{
				setPath(path);
			}

			GLS3TCTexture::GLS3TCTexture(const GLS3TCTexture& obj) :
				GLPhysicalTexture(obj),
				m_mipmapLevels(0),
				m_mipmapSizes(nullptr),
				m_mipmapData(nullptr)
			{
				setPath(obj.m_path);
			}

			int GLS3TCTexture::getNumMipmaps() const
			{
				return m_mipmapLevels;
			}

			const Dimension2i* GLS3TCTexture::getMipmapSizes() const
			{
				return m_mipmapSizes.get();
			}

			void GLS3TCTexture::upload()
			{
				bool newlyGen = false;
				if (!m_id)
				{
					glGenTextures(1, &m_id);
					if (!glIsEnabled(m_type))
						glEnable(m_type);

					bind();
					newlyGen = true;
				}
				else
					bind();

				if (m_mipmapData.get() != nullptr)
				{
					const int blockSize = getFormat() == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16;
					for (int i = 0; i < m_mipmapLevels; i++)
					{
						const int size = ((m_mipmapSizes[i].getWidth() + 3) / 4) * ((m_mipmapSizes[i].getHeight() + 3) / 4) * blockSize;
						glCompressedTexImage2D(m_type, i, m_internalFormat, m_mipmapSizes[i].getWidth(), m_mipmapSizes[i].getHeight(), 0, size, m_mipmapData[i].get());
					}

					if (m_mipmapLevels == 1)
					{
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
						if (newlyGen)
							setParameters(GL_REPEAT, GL_NEAREST, GL_NEAREST);
					}
					else if (newlyGen)
						setParameters(GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

					m_mipmapData.reset();
				}

				release();
			}

			void GLS3TCTexture::importTexture()
			{
				importTexture(m_path);
			}

			void GLS3TCTexture::importTexture(const std::string& path)
			{
				File file(path);
				if (!file.exists())
					throw FileNotFoundException(path, __FILE__, __LINE__);

				std::ifstream input(file.getPath(), std::fstream::binary);
				if (!input.good())
					throw IOException("Could not open ifstream to \"" + file.getPath() + "\"", __FILE__, __LINE__);

				importTexture(input);
				input.close();
			}

			void GLS3TCTexture::importTexture(std::istream& input)
			{
				char fileCode[4];
				input.read(fileCode, 4);
				if (std::string(fileCode, 4) != "DDS ")
					throw IOException("Given stream does not contain DDS data!", __FILE__, __LINE__);

				char header[124];
				input.read(header, 124);

				m_mipmapLevels = *bo_cast<int>(4, header + 24, LITTLE_ENDIAN | SYSTEM_ENDIAN) + 1;
				m_mipmapSizes = std::unique_ptr<Dimension2i[]>(new Dimension2i[m_mipmapLevels]);
				m_mipmapData = std::unique_ptr<std::unique_ptr<char[]>[]>(new std::unique_ptr<char[]>[m_mipmapLevels]);

				m_internalFormat = asGLFormat(*bo_cast<int>(4, header + 80, LITTLE_ENDIAN | SYSTEM_ENDIAN));
				m_format = GLTexture::formatFromInternalFormat(m_internalFormat);
				m_type = GL_TEXTURE_2D;

				const int blockSize = getFormat() == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16;
				int width = *bo_cast<int>(4, header + 12, LITTLE_ENDIAN | SYSTEM_ENDIAN);
				int height = *bo_cast<int>(4, header + 8, LITTLE_ENDIAN | SYSTEM_ENDIAN);

				m_size = Dimension3i(width, height, 1);

				for (int i = 0; i < m_mipmapLevels; i++)
				{
					const int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

					m_mipmapSizes[i] = Dimension2i(width, height);
					m_mipmapData[i] = std::unique_ptr<char[]>(new char[size]);
					input.read(m_mipmapData[i].get(), size);

					width = Math::max(width / 2, 1);
					height = Math::max(height / 2, 1);
				}

			}

			bool GLS3TCTexture::isSupported()
			{
				return GLCore::hasExtension("GL_EXT_texture_compression_s3tc");
			}

		}

	}

}
