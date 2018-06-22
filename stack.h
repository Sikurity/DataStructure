#include "stdafx.h"

#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1000

namespace lys {
	template <typename T = int>
	struct Stack {
	private:
		int cur;
		T value[MAX_STACK_SIZE];

	public:
		Stack();

		T top() throw(int);

		void push(T d) throw(int);

		void pop() throw(int);

		bool isEmpty();
	};
}

namespace lys {

	template <typename T>
	Stack<T>::Stack() {
		cur = -1;
	}

	template <typename T>
	T Stack<T>::top() throw(int) {

		if (cur > -1)
			return value[cur];
		else
			throw - 1;
	}

	template <typename T = char>
	void Stack<T>::push(T d) throw(int) {

		if (cur < MAX_STACK_SIZE)
			value[++cur] = d;
		else
			throw - 1;
	}

	template <typename T>
	void Stack<T>::pop() throw(int) {

		if (cur > -1)
			cur--;
		else
			throw - 1;
	}

	template <typename T>
	bool Stack<T>::isEmpty() {

		return cur == -1;
	}
}

#endif