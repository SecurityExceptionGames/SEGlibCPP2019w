#pragma once
#include <org/segames/library/util/array_list.h>

#ifndef SEG_API_SYSTEM_DIR_SEPARATOR
#ifdef _WIN32
#define SEG_API_SYSTEM_DIR_SEPARATOR_CHAR '\\'
#define SEG_API_SYSTEM_DIR_SEPARATOR "\\"
#else
#define SEG_API_SYSTEM_DIR_SEPARATOR_CHAR '/'
#define SEG_API_SYSTEM_DIR_SEPARATOR "/"
#endif
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					A class storing the attributes of a file, initialized on creation, copied on copy.

					* @author	Philip Rosberg
					* @since	2018-11-05
					* @edited	2019-05-12
				*/
				class SEG_API FileAttributes :
					public Object
				{
				protected:

					/*
						True if the file exists.
					*/
					bool m_exists;

					/*
						True if the file is a directory.
					*/
					bool m_directory;

					/*
						The length/size of the file.
					*/
					size_t m_length;

					/*
						The file path.
					*/
					std::string m_path;

					/*
						The file path dissected.
					*/
					util::ArrayList<std::string> m_dissectedPath;

				protected:

					/*
						Loads the attributes using the windows library.
						* @param[in] path The path of the file
					*/
					virtual void loadAttribWindows(const char* path);

				public:

					/*
						Creates an empty file attributes object in the local path of the executable.
					*/
					FileAttributes();

					/*
						Loads the file attributes for the given path.
						* @param[in] path The path of the file
					*/
					explicit FileAttributes(const char* path);

					/*
						Loads the file attributes for the given path.
						* @param[in] path The path of the file
					*/
					explicit FileAttributes(const std::string& path);

					/*
						Returns true if the file exists.
					*/
					virtual bool exists() const;

					/*
						Returns true if the given file is a directory.
					*/
					virtual bool isDirectory() const;

					/*
						Returns the length of the file in num. bytes.
					*/
					virtual size_t length() const;

					/*
						Returns the file path (absolute).
					*/
					virtual std::string& getPath() const;

					/*
						Retruns the path dissected into all sub-parts.
					*/
					virtual util::ArrayList<std::string>& getPathDissection() const;

					/*
						Sets if the file exists or not.
						WARNING! THIS METHOD ONLY CHANGES THE ATTRIBUTE OBJECT AND NOT THE FILE ON THE SYSTEM!
						* @param[in] flag True if the file exists
					*/
					virtual void setExisting(const bool flag);

					/*
						Sets if the file is a directory or not.
						WARNING! THIS METHOD ONLY CHANGES THE ATTRIBUTE OBJECT AND NOT THE FILE ON THE SYSTEM!
						* @param[in] float True if the file is a directory
					*/
					virtual void setDirectory(const bool flag);

					/*
						Sets the file representation length.
						WARNING! THIS METHOD ONLY CHANGES THE ATTRIBUTE OBJECT AND NOT THE FILE ON THE SYSTEM!
						* @param[in] length The length of the file
					*/
					virtual void setLength(const size_t length);

					/*
						Sets the path of the file representation.
						WARNING! THIS METHOD ONLY CHANGES THE ATTRIBUTE OBJECT AND NOT THE FILE ON THE SYSTEM!
						* @param[in] path The path
					*/
					virtual void setPath(const std::string& path);

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