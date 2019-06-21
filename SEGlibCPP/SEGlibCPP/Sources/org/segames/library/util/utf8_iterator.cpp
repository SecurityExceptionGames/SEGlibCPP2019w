#include <org/segames/library/util/utf8_iterator.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				UTF8Iterator::UTF8Iterator(const std::string& src) :
					UTF8Iterator(src.begin())
				{}

				UTF8Iterator::UTF8Iterator(const std::string::const_iterator& itr) :
					m_moved(true),
					m_currentCodepoint(0),
					m_itr(itr)
				{}

				UTF8Iterator::UTF8Iterator(const UTF8Iterator& itr) :
					m_moved(itr.m_moved),
					m_currentCodepoint(itr.m_currentCodepoint),
					m_itr(itr.m_itr)
				{}

				UTF8Iterator& UTF8Iterator::operator=(const UTF8Iterator& itr)
				{
					this->m_moved = itr.m_moved;
					this->m_currentCodepoint = itr.m_currentCodepoint;
					this->m_itr = itr.m_itr;
					return *this;
				}

				UTF8Iterator& UTF8Iterator::operator++()
				{
					char firstC = *m_itr;
					std::string::difference_type offset = 1;

					if (firstC & BitMask::FIRST)
					{
						if (firstC & BitMask::THIRD)
						{
							if (firstC & BitMask::FOURTH)
								offset = 4;
							else
								offset = 3;
						}
						else
							offset = 2;
					}

					m_itr += offset;
					m_moved = true;
					return *this;
				}

				UTF8Iterator UTF8Iterator::operator++(int)
				{
					UTF8Iterator temp = *this;
					++(*this);
					return temp;
				}

				UTF8Iterator& UTF8Iterator::operator--()
				{
					--m_itr;
					if (*m_itr & BitMask::FIRST)
					{
						--m_itr;
						if ((*m_itr & BitMask::SECOND) == 0)
						{
							--m_itr;
							if ((*m_itr & BitMask::SECOND) == 0)
								--m_itr;
						}

					}
					m_moved = true;
					return *this;
				}

				UTF8Iterator UTF8Iterator::operator--(int)
				{
					UTF8Iterator temp = *this;
					--(*this);
					return temp;
				}

				unsigned int UTF8Iterator::operator*() const
				{
					if (m_moved)
					{
						unsigned int codePoint = 0;
						char firstC = *m_itr;

						if (firstC & BitMask::FIRST)
						{
							if (firstC & BitMask::THIRD)
							{
								if (firstC & BitMask::FOURTH)
								{
									codePoint = (firstC & 0x07) << 18;

									char secondC = *(m_itr + 1);
									codePoint += (secondC & 0x3f) << 12;

									char thirdC = *(m_itr + 2);
									codePoint += (thirdC & 0x3f) << 6;

									char fourthC = *(m_itr + 3);
									codePoint += (fourthC & 0x3f);
								}
								else
								{
									codePoint = (firstC & 0x0f) << 12;

									char secondC = *(m_itr + 1);
									codePoint += (secondC & 0x3f) << 6;

									char thirdC = *(m_itr + 2);
									codePoint += (thirdC & 0x3f);
								}

							}
							else
							{
								codePoint = (firstC & 0x1f) << 6;
								char secondC = *(m_itr + 1);
								codePoint += (secondC & 0x3f);
							}

						}
						else
						{
							codePoint = (unsigned int)firstC;
						}

						m_currentCodepoint = codePoint;
						m_moved = false;
					}

					return m_currentCodepoint;
				}

				bool UTF8Iterator::operator==(const UTF8Iterator& itr) const
				{
					return m_itr == itr.m_itr;
				}

				bool UTF8Iterator::operator==(const std::string::iterator& itr) const
				{
					return m_itr == itr;
				}

				bool UTF8Iterator::operator==(const std::string::const_iterator& itr) const
				{
					return m_itr == itr;
				}

				bool UTF8Iterator::operator!=(const UTF8Iterator& itr) const
				{
					return m_itr != itr.m_itr;
				}

				bool UTF8Iterator::operator!=(const std::string::iterator& itr) const
				{
					return m_itr != itr;
				}

				bool UTF8Iterator::operator!=(const std::string::const_iterator& itr) const
				{
					return m_itr != itr;
				}

			}

		}

	}

}