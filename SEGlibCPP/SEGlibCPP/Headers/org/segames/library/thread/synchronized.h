#pragma once
#include <org/segames/library/thread/volatile.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A more exception safe way of using Volatile<T>::lock() and Volatile<T>::unlock().

				Usage:
				Volatile<int> var(123); // Variable somewhere

				// Piece of code changing the volatile variable
				{
					Synchronized<int> lock(var);
					int& v = var.var();
					v ++;
				}

				// Alternatively using operators
				{
					Synchronized<int> lock(var);
					(*var)++;
				}

				* @author	Philip Rosberg
				* @since	2018-06-11
				* @edited	2019-05-11
			*/
			template<class T>
			class Synchronized final
			{
			private:

				/*
					The volatile var to lock and unlock.
				*/
				Volatile<T>& m_var;

			public:

				/*
					Creates a thread-synchronization lock on the given volatile variable.
					* @param[in] var The volatile variable to lock
				*/
				Synchronized(Volatile<T>& var) :
					m_var(var)
				{
					m_var.lock();
				}

				/*
					Ensure no copying of locks.
				*/
				Synchronized(const Synchronized<T>&) = delete;

				/*
					Destructor.
				*/
				~Synchronized()
				{
					m_var.unlock();
				}

				/*
					Ensure no copying of locks.
				*/
				Synchronized<T>& operator=(const Synchronized<T>&) const = delete;

			};

		}

	}

}