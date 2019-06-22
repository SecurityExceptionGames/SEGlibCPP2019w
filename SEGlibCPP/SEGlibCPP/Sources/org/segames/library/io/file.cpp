#include <org/segames/library/io/file.h>
#include <org/segames/library/io/file_not_found_exception.h>
#include <org/segames/library/util/string_util.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			bool File::createNewFileWindows()
			{
#ifdef _WIN32
				bool retVal = false;
				if (m_attributes.get())
				{
					HANDLE hand = CreateFileA(getPath().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hand != INVALID_HANDLE_VALUE)
						retVal = true;
					CloseHandle(hand);
				}
				return retVal;
#else
				return false;
#endif
			}

			bool File::mkdirsWindows()
			{
#ifdef _WIN32
				bool retVal = false;
				if (m_attributes.get())
				{
					std::string tempPath = m_attributes->getPathDissection().get(0);
					for (int i = 1; i < m_attributes->getPathDissection().size(); i++)
					{
						if (m_attributes->getPathDissection().get(i).size() > 0)
						{
							tempPath += SEG_API_SYSTEM_DIR_SEPARATOR + m_attributes->getPathDissection().get(i);

							DWORD attrib = GetFileAttributesA(tempPath.c_str());
							if (attrib == INVALID_FILE_ATTRIBUTES)
							{
								int retValInt = _mkdir(tempPath.c_str());
								if (retValInt == 0)
									retVal = true;
							}

						}

					}

				}
				return retVal;
#else
				return false;
#endif
			}

			void File::listWindows(ArrayList<std::string>& names) const
			{
#ifdef _WIN32
				HANDLE dir;
				WIN32_FIND_DATAA findData;
				if ((dir = FindFirstFileA((getPath() + SEG_API_SYSTEM_DIR_SEPARATOR + "*").c_str(), &findData)) != INVALID_HANDLE_VALUE)
				{
					while (FindNextFileA(dir, &findData))
					{
						std::string name = std::string(findData.cFileName);
						if (name != "..")
							names.add(findData.cFileName);
					}
					FindClose(dir);
				}
#endif
			}

			void File::listFilesWindows(ArrayList<File>& files) const
			{
#ifdef _WIN32
				HANDLE dir;
				WIN32_FIND_DATAA findData;
				if ((dir = FindFirstFileA((getPath() + SEG_API_SYSTEM_DIR_SEPARATOR + "*").c_str(), &findData)) != INVALID_HANDLE_VALUE)
				{
					while (FindNextFileA(dir, &findData))
					{
						std::string name = std::string(findData.cFileName);
						if (name != "..")
							files.add(File(getPath() + SEG_API_SYSTEM_DIR_SEPARATOR + findData.cFileName));
					}
					FindClose(dir);
				}
#endif
			}

			File::File() :
				m_attributes(nullptr)
			{}

			File::File(const char* path) :
				m_attributes(path ? new FileAttributes(path) : nullptr)
			{}

			File::File(const std::string& path) :
				File(path.c_str())
			{}

			File::File(const FileAttributes& attrib) :
				m_attributes(new FileAttributes(attrib))
			{}

			File::File(const File& obj) :
				m_attributes(obj.m_attributes)
			{}

			bool File::isNull() const
			{
				return !m_attributes.get();
			}

			bool File::exists() const
			{
				if (m_attributes.get())
					return m_attributes->exists();
				return false;
			}

			bool File::isDirectory() const
			{
				if (m_attributes.get())
					return m_attributes->isDirectory();
				return false;
			}

			bool File::createNewFile()
			{
				bool retVal = false;
#ifdef _WIN32
				retVal = createNewFileWindows();
				if (retVal)
					m_attributes->update();
#endif
				return retVal;
			}

			bool File::deleteFile()
			{
				if (m_attributes.get())
					if (std::remove(getPath().c_str()) == 0)
					{
						m_attributes->setExisting(false);
						return true;
					}
				return false;
			}

			bool File::mkdirs()
			{
				bool retVal = false;
#ifdef _WIN32
				retVal = mkdirsWindows();
				if (retVal)
					m_attributes->update();
#endif
				return retVal;
			}

			bool File::renameTo(const char* path)
			{
				if (m_attributes.get())
					if (std::rename(getPath().c_str(), path) == 0)
					{
						this->m_attributes = std::shared_ptr<FileAttributes>(new FileAttributes(path));
						return true;
					}
				return false;
			}

			bool File::renameTo(const std::string& path)
			{
				return renameTo(path.c_str());
			}

			bool File::renameTo(const FileAttributes& attrib)
			{
				return renameTo(attrib.getPath());
			}

			bool File::renameTo(const File& file)
			{
				return renameTo(file.getPath());
			}

			size_t File::length() const
			{
				if (m_attributes.get())
					return m_attributes->length();
				return false;
			}

			std::string& File::getName() const
			{
				return m_attributes->getPathDissection().get(m_attributes->getPathDissection().size() - 1);
			}

			std::string& File::getPath() const
			{
				return m_attributes->getPath();
			}

			std::string File::getParent() const
			{
				if (m_attributes.get())
				{
					ArrayList<std::string>& pathDiss = m_attributes->getPathDissection();
					return StringUtil::concat(SEG_API_SYSTEM_DIR_SEPARATOR, pathDiss.begin(), ListIterator<std::string, typename ArrayList<std::string>::PosType>(pathDiss, pathDiss.size() - 1));
				}
				return "";
			}

			File File::getParentFile() const
			{
				return File(getParent());
			}

			std::ifstream File::openInput() const
			{
				if (!exists())
					throw FileNotFoundException(getPath(), __FILE__, __LINE__);
					
				std::ifstream stream(getPath(), std::fstream::binary);
				if (!stream.good())
					throw IOException("Could not open input stream to file \"" + getPath() + "\"", __FILE__, __LINE__);
				return stream;
			}

			std::ofstream File::openOutput() const
			{
				if (!exists())
					throw FileNotFoundException(getPath(), __FILE__, __LINE__);

				std::ofstream stream(getPath(), std::fstream::binary);
				if (!stream.good())
					throw IOException("Could not open output stream to file \"" + getPath() + "\"", __FILE__, __LINE__);
				return stream;
			}

			void File::list(ArrayList<std::string>& names) const
			{
#ifdef _WIN32
				listWindows(names);
#endif
			}

			ArrayList<std::string> File::list() const
			{
				ArrayList<std::string> out(1);
				list(out);
				return out;
			}

			void File::listFiles(ArrayList<File>& files) const
			{
#ifdef _WIN32
				listFilesWindows(files);
#endif
			}

			ArrayList<File> File::listFiles() const
			{
				ArrayList<File> out(1);
				listFiles(out);
				return out;
			}

			void File::update()
			{
				if (m_attributes.get())
					m_attributes->update();
			}

			size_t File::hashCode() const
			{
				if (m_attributes.get())
					return m_attributes->hashCode();
				return 0;
			}

			std::string File::toString() const
			{
				std::string out = "File(";
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