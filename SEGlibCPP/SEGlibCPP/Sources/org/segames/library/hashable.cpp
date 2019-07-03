#include <org/segames/library/hashable.h>

#include <string>

namespace org
{

	namespace segames
	{

		namespace library
		{

			size_t Hashable::hashCode(const Hashable& obj)
			{
				return obj.hashCode();
			}

			size_t Hashable::hashCode(const char* str)
			{
				return hashCode(std::string(str));
			}

			size_t Hashable::hashCode(const std::string& str)
			{
				size_t hash = 0;
				size_t len = str.length();

				for (size_t i = 0; i < len; i++)
				{
					size_t exp = (len - i - 1);
					size_t partVal = str.at(i);
					for (size_t e = 0; e < exp; e++)
						partVal *= 31;
					hash += partVal;
				}

				return hash;
			}

			size_t Hashable::hashCode(const void* ptr, const size_t len)
			{
				size_t hash = 0;
				const unsigned char* mem = reinterpret_cast<const unsigned char*>(ptr);
				if (len <= sizeof(size_t))
				{
					for (size_t i = 0; i < len; i++, mem++)
						hash |= (((size_t)*mem) << (i * 8));
				}
				else
				{
					// FNV-1a algorithm
					hash = 14695981039346656037ull;
					for (size_t i = 0; i < len; i++, mem++)
					{
						hash ^= (size_t)*mem;
						hash *= 1099511628211;
					}

				}

				return hash;
			}

		}

	}

}
