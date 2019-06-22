#include <org/segames/library/io/file_attributes.h>
#include <org/segames/library/util/string_util.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#endif

#include <fstream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			void FileAttributes::loadAttribWindows(const char* path)
			{
#ifdef _WIN32
				DWORD nameLen = GetFullPathNameA(path, 0, nullptr, nullptr);
				std::unique_ptr<char> strBuff(new char[nameLen]);
				GetFullPathNameA(path, nameLen, strBuff.get(), nullptr);
				this->m_path = std::string(strBuff.get());

				DWORD attrib = GetFileAttributesA(strBuff.get());
				if (attrib == INVALID_FILE_ATTRIBUTES)
				{
					this->m_exists = false;
					this->m_directory = false;
					this->m_length = 0;
				}
				else
				{
					this->m_exists = true;

					if (attrib & FILE_ATTRIBUTE_DIRECTORY)
					{
						this->m_directory = true;
						this->m_length = 0;
					}
					else
					{
						this->m_directory = false;

						std::ifstream in(strBuff.get(), std::ifstream::ate | std::ifstream::binary);
						signed long long len = in.tellg();
						in.close();

						if (len == -1)
							this->m_length = 0;
						else
							this->m_length = (size_t)len;
					}

				}

				this->m_dissectedPath = StringUtil::split(m_path, SEG_API_SYSTEM_DIR_SEPARATOR);
#endif
			}

			FileAttributes::FileAttributes() :
				m_exists(false),
				m_directory(false),
				m_length(0),
				m_path(""),
				m_dissectedPath(0)
			{}

			FileAttributes::FileAttributes(const char* path) :
				FileAttributes()
			{
#ifdef _WIN32
				if (*path == '\0')
					loadAttribWindows(".\\");
				else
					loadAttribWindows(path);
#endif
			}

			FileAttributes::FileAttributes(const std::string& path) :
				FileAttributes(path.c_str())
			{}

			bool FileAttributes::exists() const
			{
				return m_exists;
			}

			bool FileAttributes::isDirectory() const
			{
				return m_directory;
			}

			size_t FileAttributes::length() const
			{
				return m_length;
			}

			std::string& FileAttributes::getPath() const
			{
				return (std::string&)m_path;
			}

			ArrayList<std::string>& FileAttributes::getPathDissection() const
			{
				return (ArrayList<std::string>&)m_dissectedPath;
			}

			void FileAttributes::setExisting(const bool flag)
			{
				this->m_exists = flag;
			}

			void FileAttributes::setDirectory(const bool flag)
			{
				this->m_directory = flag;
			}

			void FileAttributes::setLength(const size_t length)
			{
				this->m_length = length;
			}

			void FileAttributes::setPath(const std::string& path)
			{
				this->m_path = path;
				this->m_dissectedPath = StringUtil::split(m_path, SEG_API_SYSTEM_DIR_SEPARATOR);
			}

			void FileAttributes::update()
			{
#ifdef _WIN32
				loadAttribWindows(m_path.c_str());
#endif
			}

			size_t FileAttributes::hashCode() const
			{
				return Hashable::hashCode(m_path);
			}

			std::string FileAttributes::toString() const
			{
				std::string out = "FileAttributes(";
				if (exists())
				{
					out += "E";
					out += (isDirectory() ? "D" : "F");
					out += "): \"";
				}
				else
					out += "--): \"";
				out += getPath();
				out += "\"";
				return out;
			}

		}

	}

}