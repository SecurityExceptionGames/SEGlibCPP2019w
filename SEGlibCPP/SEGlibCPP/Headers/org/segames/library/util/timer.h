#pragma once
#include <org/segames/library/object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					A simple timer class for time measurements and primitive frame synchronization.
					Note! Only one of time(), deltaTime() or sync() should be used with the
					same Timer instance.

					* @author	Philip Rosberg
					* @since	2018-06-08
					* @edited	2019-03-17
				*/
				class SEG_API Timer :
					public Object
				{
				public:

					/*
						Returns the time since epoch in nanoseconds, immitating System.nanoTime()
						from Java.
					*/
					static size_t nanoTime();

					/*
						Returns the time since epoch in microseconds.
					*/
					static size_t microTime();

					/*
						Returns the time since epoch in milliseconds.
					*/
					static size_t milliTime();

				protected:

					/*
						The amount of updates per second.
					*/
					double updateRate;

					/*
						The time in seconds between each update.
					*/
					double updateTime;

					/*
						The last measured time, ie. the stored time used to measure delta time.
					*/
					size_t lastTime;

				public:

					/*
						Creates a timer without time limit.
					*/
					Timer();

					/*
						Creates a timer using the given update rate.
						* @param[in] updateRate The rate at which the timer will consider it time to update, negative numbers will make time() allways return false
					*/
					explicit Timer(const double updateRate);

					/*
						Returns true if the time of one update has passed.
					*/
					virtual bool time();

					/*
						Returns the time difference in seconds between this call and the last.
					*/
					virtual double deltaTime();

					/*
						Returns the timer update rate, in updates per second.
					*/
					virtual double getUpdateRate() const;

					/*
						Returns the time per update
					*/
					virtual double getUpdateTime() const;

					/*
						Sets the update rate of the timer.
						* @param[in] updateRate The rate at which the timer will consider it time to update, negative numbers will make time() allways return false
					*/
					virtual void setUpdateRate(const double updateRate);

					/*
						Sleeps this thread to synchronize it with the update rate.
					*/
					virtual void sync();

				};

			}

		}

	}

}