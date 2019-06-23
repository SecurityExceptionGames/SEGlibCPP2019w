#pragma once
#ifdef _WIN32
#ifndef ZeroMemory
#include <Windows.h>
#endif
#else
#include <mutex>
#endif

#include <algorithm>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				A thread-wise lockable variable to ensure thread safety.

				Usage:
				Volatile<int> var(123); //Variable somewhere

				//Piece of code changing the volatile variable
				var.lock();

				int& v = var.var();
				v ++;

				var.unlock();

				* @author	Philip Rosberg
				* @since	2018-06-11
				* @edited	2019-05-11
			*/
			template<typename T>
			class Volatile final
			{
			private:

				/*
					The stored value
				*/
				T m_var;

#ifdef _WIN32
				/*
					Critical section for windows.
				*/
				CRITICAL_SECTION m_criticalSection;
#else
				/*
					Mutex for non-windows systems.
				*/
				std::mutex m_mutexVar;
#endif

			public:

				/*
					Creates a volatile var without setting the internal variable.
				*/
				Volatile()
				{
#ifdef _WIN32
					InitializeCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
#endif
				}
					
				/*
					Creates a volatile var from the given variable.
					* @param[in] var The variable to wrap
				*/
				Volatile(const T& var) :
					Volatile()
				{
					m_var = var;
				}

				/*
					Creates a volatile var from the given variable.
					* @param[in] var The variable to wrap
				*/
				Volatile(T& var) :
					Volatile()
				{
					std::swap(m_var, var);
				}

				/*
					Creates a volatile var from the given variable.
					* @param[in] var The variable to wrap
				*/
				Volatile(T&& var) :
					Volatile()
				{
					std::swap(m_var, var);
				}

				/*
					Copies the stored variable without changing the lock-state.
					* @param[in] obj The volatile variable to copy from
				*/
				explicit Volatile(const Volatile<T>& obj) :
					Volatile((const T&)obj.m_var)
				{}

				/*
					Destructor.
				*/
				~Volatile()
				{
#ifdef _WIN32
					DeleteCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
#endif
				}

				/*
					Returns a reference to the stored variable.
				*/
				T& var() noexcept
				{
					return m_var;
				}

				/*
					Returns a constant reference of the stored variable for read-only situations.
				*/
				T& peek() const noexcept
				{
					return m_var;
				}

				/*
					Locks the volatile variable so only one thread can use it at the same time.
				*/
				void lock()
				{
#ifdef _WIN32
					EnterCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
#else
					m_mutexVar.lock();
#endif
				}

				/*
					Unlocks the volatile variable.
				*/
				void unlock()
				{
#ifdef _WIN32
					LeaveCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
#else
					m_mutexVar.unlock();
#endif
				}

				/*
					Returns a reference to the stored variable, same as calling var().
				*/
				T& operator*() noexcept
				{
					return var();
				}

				/*
					Override of the member access operator.
				*/
				T* operator->()
				{
					return &m_var;
				}

				/*
					Copies the stored variable without changing the lock-state.
					* @param[in] obj The volatile variable to copy from
				*/
				Volatile<T>& operator=(const Volatile<T>& obj)
				{
					m_var = obj.m_var;
					return *this;
				}

			};

		}

	}

}