#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Interface for a generic stack type.

				* @author	Philip Rosberg
				* @since	2019-03-17
				* @edited	2019-03-17
			*/
			template<typename T>
			class Stack
			{
			public:

				/*
					Returns true if the stack is empty.
				*/
				virtual bool isEmpty() const = 0;
					
				/*
					Returns the top value in the stack.
				*/
				virtual T& peek() const = 0;

				/*
					Removes and returns the top value in the stack.
				*/
				virtual T pop() = 0;

				/*
					Adds the given value to the top of the stack.
					* @param[in] value The value to add
				*/
				virtual void push(const T& value) = 0;

				/*
					Removes all content from the stack.
				*/
				virtual void clear() = 0;

			};

		}

	}

}
