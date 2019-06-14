#pragma once
#include <org/segames/library/io/file_attributes.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					A class for representing a file in the standard file system.
					Note! This class is not thread safe, which means that a file instance
					should not be copied from one thread to another. Copying using the
					file attributes is thread safe (as thread safe as the os allows it to be).

					* @author	Philip Rosberg
					* @since	2018-11-05
					* @edited	2019-05-12
				*/
				class SEG_API File :
					public Object
				{
				protected:

					/*
						The file attributes, eg. path, existance etc.
					*/
					std::shared_ptr<FileAttributes> m_attributes;

				protected:

					/*
						Creates a new file using the windows library and returns true if the creation succeeded.
					*/
					virtual bool createNewFileWindows();

					/*
						Creates the directory to this directory using the windows library.
					*/
					virtual bool mkdirsWindows();

					/*
						Lists the names of the sub files and folders of this file.
						* @param[out] names The arraylist to place the file names in
					*/
					virtual void listWindows(util::ArrayList<std::string>& names) const;

					/*
						Lists the sub files and folders of this file using the windows library.
						* @param[out] files The arraylist to place the files in
					*/
					virtual void listFilesWindows(util::ArrayList<File>& files) const;

				public:

					/*
						Creates an empty file object.
					*/
					File();

					/*
						Creates a new file representation from the given path.
						* @param[in] path The path of the file
					*/
					explicit File(const char* path);

					/*
						Creates a new file representation from the given path.
						* @param[in] path The path of the file
					*/
					explicit File(const std::string& path);

					/*
						Creates a copy of the file representation from the given file attributes (Thread safe copying).
						* @param[in] attrib The file attributes, gets copied
					*/
					explicit File(const FileAttributes& attrib);

					/*
						Creates a copy of the file representation (Not 100% thread safe copying).
						* @param[in] obj The file instance to copy
					*/
					File(const File& obj);

					/*
						Returns true if the file attributes is null.
					*/
					virtual bool isNull() const;

					/*
						Returns true if the file exists.
					*/
					virtual bool exists() const;

					/*
						Returns true if the given file is a directory.
					*/
					virtual bool isDirectory() const;

					/*
						Creates a new file and returns true if the creation succeeded.
					*/
					virtual bool createNewFile();

					/*
						Deletes the file or directory denoted by this path.
					*/
					virtual bool deleteFile();

					/*
						Creates the directory to this directory.
					*/
					virtual bool mkdirs();

					/*
						Renames the file denoted by this pathname.
						* @param[in] path The path to rename to
					*/
					virtual bool renameTo(const char* path);

					/*
						Renames the file denoted by this pathname.
						* @param[in] path The path to rename to
					*/
					virtual bool renameTo(const std::string& path);

					/*
						Renames the file denoted by this pathname.
						* @param[in] attrib The file attributes to rename to
					*/
					virtual bool renameTo(const FileAttributes& attrib);

					/*
						Renames the file denoted by this pathname.
						* @param[in] file The file to rename to
					*/
					virtual bool renameTo(const File& file);

					/*
						Returns the length of the file in num. bytes.
					*/
					virtual size_t length() const;

					/*
						Returns the name (the last part of the path) of the file.
					*/
					virtual std::string& getName() const;

					/*
						Returns the file path (absolute).
					*/
					virtual std::string& getPath() const;

					/*
						Returns the path to the parent file.
					*/
					virtual std::string getParent() const;

					/*
						Returns the parent file or directory of this file.
					*/
					virtual File getParentFile() const;

					/*
						Lists the names of the sub files and folders of this file.
						* @param[out] names The arraylist to place the file names in
					*/
					virtual void list(util::ArrayList<std::string>& names) const;

					/*
						Returns an arraylist with the names of with the sub files of this file.
					*/
					virtual util::ArrayList<std::string> list() const;

					/*
						Lists the sub files and folders of this file.
						* @param[out] files The arraylist to place the files in
					*/
					virtual void listFiles(util::ArrayList<File>& files) const;

					/*
						Returns an arraylist with the with the sub files of this file.
					*/
					virtual util::ArrayList<File> listFiles() const;

					/*
						Updates the file attributes.
					*/
					virtual void update();

					/*
						Returns a hash code from the path.
					*/
					virtual size_t hashCode() const override;

					/*
						Returns a string representation of the file attributes.
					*/
					virtual std::string toString() const override;

				};

			}

		}

	}

}