#pragma once
#include <org/segames/library/util/array_list.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Class/Namespace for string utility related functions.

				* @author	Philip Rosberg
				* @since	2019-05-11
				* @since	2019-05-11
			*/
			class StringUtil final
			{
			private:

				StringUtil() {}
				StringUtil(const StringUtil&) = delete;

			public:

				/*
					Returns true if the given source string starts with the given expression.
					* @param[in] src The source string
					* @param[in] expr The expression to check for
				*/
				inline static bool startsWith(const std::string& src, const std::string& expr)
				{
					return src.compare(0, expr.size(), expr) == 0;
				}

				/*
					Returns true if the given source string ends with the given expression.
					* @param[in] src The source string
					* @param[in] expr The expression to check for
				*/
				inline static bool endsWith(const std::string& src, const std::string& expr)
				{
					return src.compare(src.size() - expr.size(), expr.size(), expr) == 0;
				}

				/*
					Concatenates the strings from the given collection of strings.
					* @param[in] first The begining iterator or pointer to a list/array of strings
					* @param[in] last The ending iterator or pointer
				*/
				template<typename ItrBeg, typename ItrEnd>
				inline static std::string concat(const ItrBeg& first, const ItrEnd& last)
				{
					size_t size = 0;
					for (ItrBeg itr = first; itr != last; itr++)
						size += (*itr).size();

					std::string out;
					out.reserve(size);
					for (ItrBeg itr = first; itr != last; itr++)
						out.append(*itr);
					return out;
				}

				/*
					Concatenates the strings from the given collection of strings and separates them by the given separator.
					* @param[in] separator The separator sequence, ie. the string inserted between the strings that are being concatenated
					* @param[in] first The begining iterator or pointer to a list/array of strings
					* @param[in] last The ending iterator or pointer
				*/
				template<typename ItrBeg, typename ItrEnd>
				static std::string concat(const std::string& separator, const ItrBeg& first, const ItrEnd& last)
				{
					size_t size = 0;
					for (ItrBeg itr = first; itr != last; itr++)
						size += (*itr).size() + separator.size();
					if (size > 0)
						size -= separator.size();

					std::string out;
					out.reserve(size);
					for (ItrBeg itr = first; itr != last; itr++)
					{
						const std::string& s = *itr;
						out.append(s);

						size -= s.size();
						if (size > 0)
						{
							out.append(separator);
							size -= separator.size();
						}

					}
					return out;
				}

				/*
					Concatenates the strings from the given collection of strings.
					* @param[in] collection The collection of strings to concatenate
				*/
				template<typename T, typename Itr>
				inline static std::string concat(const Iterable<T, Itr>& collection)
				{
					return concat(collection.begin(), collection.end());
				}

				/*
					Concatenates the strings from the given collection of strings and separates them by the given separator.
					* @param[in] separator The separator sequence, ie. the string inserted between the strings that are being concatenated
					* @param[in] collection The collection of strings to concatenate
				*/
				template<typename T, typename Itr>
				inline static std::string concat(const std::string& separator, const Iterable<T, Itr>& collection)
				{
					return concat(separator, collection.begin(), collection.end());
				}

				/*
					Splits the given string by the given separator sequence and stores the result in the given list.
					* @param[in] src The string to split
					* @param[in] separator The string to split the first one by
					* @param[out] output The list to write the resulting pieces to
				*/
				template<typename PosType_>
				inline static void split(const std::string& src, const std::string& separator, List<std::string, PosType_>& output)
				{
					size_t start = 0;
					size_t end = src.find(separator);
					while (end != std::string::npos)
					{
						output.add(src.substr(start, end - start));
						start = end + separator.length();
						end = src.find(separator, start);
					}
					output.add(src.substr(start, end - start));
				}

				/*
					Splits the given string by the given separator sequence and returns an array list with the resulting pieces.
					* @param[in] src The string to split
					* @param[in] separator The string to split the first one by
				*/
				inline static ArrayList<std::string> split(const std::string& src, const std::string& separator)
				{
					ArrayList<std::string> out;
					split(src, separator, out);
					return out;
				}

			};

		}

	}

}