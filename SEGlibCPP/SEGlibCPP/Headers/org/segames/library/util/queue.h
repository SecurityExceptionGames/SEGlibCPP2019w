#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Interface for a generic queue type.

				* @author	Philip Rosberg
				* @since	2019-03-16
				* @edited	2019-03-16
			*/
			template<typename T>
			class Queue
			{
			public:

				/*
					Returns true if the queue is empty.
				*/
				virtual bool isEmpty() const = 0;

				/*
					Returns the first value in the queue.
				*/
				virtual T& peek() const = 0;

				/*
					Removes the first element in the queue and returns the value.
				*/
				virtual T dequeue() = 0;

				/*
					Adds the given value to the back of the queue.
					* @param[in] value The value to add
				*/
				virtual void enqueue(const T& value) = 0;

				/*
					Removes all content from the queue.
				*/
				virtual void clear() = 0;

			};

		}

	}

}
