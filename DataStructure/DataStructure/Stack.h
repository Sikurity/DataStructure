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

		T top();
		void push(T d);
		void pop();
		bool isEmpty();
	};
}

namespace lys {

	template <typename T>
	Stack<T>::Stack() {
		cur = -1;
	}

	template <typename T>
	T Stack<T>::top() {

		if (cur > -1)
			return value[cur];
		else
			throw - 1;
	}

	template <typename T>
	void Stack<T>::push(T d) {

		if (cur < MAX_STACK_SIZE)
			value[++cur] = d;
		else
			throw - 1;
	}

	template <typename T>
	void Stack<T>::pop() {

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