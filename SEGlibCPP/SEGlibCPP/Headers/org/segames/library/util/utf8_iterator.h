#pragma once
#include <org/segames/library/dllmain.h>

#include <string>

namespace org
{
	
	namespace segames
	{
		
		namespace library
		{
			
			/*
				A class for iterating through an UTF-8 encoded byte array.
					
				* @author	Philip Rosberg
				* @since	2019-06-20
				* @edited	2019-07-03
			*/
			class SEG_API UTF8Iterator final : 
				public std::iterator<std::bidirectional_iterator_tag, unsigned int, std::string::difference_type, const unsigned int*, const unsigned int&>
			{
			private:
					
				/*
					The bit masks.
				*/
				enum BitMask
				{
					FIRST = 128,
					SECOND = 64,
					THIRD = 32,
					FOURTH = 16
				};

				/*
					True if the iterator has moved.
				*/
				mutable bool m_moved;

				/*
					The current UTF-8 codepoint.
				*/
				mutable unsigned int m_currentCodepoint;
					
				/*
					The character (byte) pointer.
				*/
				std::string::const_iterator m_itr;

			public:
				
				/*
					UTF-8 iterator constructor.
					* @param[in] src The source string
				*/
				explicit UTF8Iterator(const std::string& src);

				/*
					UTF-8 iterator constructor.
					* @param[in] itr The string iterator
				*/
				explicit UTF8Iterator(const std::string::const_iterator& itr);

				/*
					UTF-8 iterator constructor.
					* @param[in] itr The UTF-8 iterator
				*/
				UTF8Iterator(const UTF8Iterator& itr);

				/*
					Sets the iterator to the given one.
					* @param[in] itr The UTF-8 iterator to compare
				*/
				UTF8Iterator& operator=(const UTF8Iterator& itr);

				/*
					Moves the iterator one positive step in UTF-8 characters.
				*/
				UTF8Iterator& operator++();

				/*
					Moves the iterator one positive step in UTF-8 characters.
				*/
				UTF8Iterator operator++(int);

				/*
					Moves the iterator one negative step in UTF-8 characters.
				*/
				UTF8Iterator& operator--();

				/*
					Moves the iterator one negative step in UTF-8 characters.
				*/
				UTF8Iterator operator--(int);

				/*
					Dereference operator, returns the UTF-8 character at the given position.
				*/
				unsigned int operator*() const;

				/*
					The equal to operator.
					* @param[in] itr The UTF-8 iterator to compare
				*/
				bool operator==(const UTF8Iterator& itr) const;

				/*
					The equal to operator.
					* @param[in] itr The iterator to compare
				*/
				bool operator==(const std::string::iterator& itr) const;

				/*
					The equal to operator.
					* @param[in] itr The iterator to compare
				*/
				bool operator==(const std::string::const_iterator& itr) const;

				/*
					The not equal to operator.
					* @param[in] itr The UTF-8 iterator to compare
				*/
				bool operator!=(const UTF8Iterator& itr) const;

				/*
					The not equal to operator.
					* @param[in] itr The iterator to compare
				*/
				bool operator!=(const std::string::iterator& itr) const;

				/*
					The not equal to operator.
					* @param[in] itr The iterator to compare
				*/
				bool operator!=(const std::string::const_iterator& itr) const;

				/*
					Converts the given codepoint to string.
					* @param[in] codepoint The UTF-8 codepoint
				*/
				static std::string codepointToString(const unsigned int codepoint);

				/*
					Converts the given codepoint to string.
					* @param[in] codepoint The UTF-8 codepoint
					* @param[out] str The string to write to
				*/
				static void codepointToString(const unsigned int codepoint, std::string& str);

			};

		}

	}

}