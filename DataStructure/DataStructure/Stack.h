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
		bool isFull();
		bool isEmpty();
	};
}

namespace lys {

	template <typename T>
	Stack<T>::Stack() {
		cur = 0;
	}

	template <typename T>
	T Stack<T>::top() {
		if(isEmpty())
			throw - 1;
		
		return value[cur - 1];
	}

	template <typename T>
	void Stack<T>::push(T data) {
		if(isFull())
			throw - 1;
			
		value[cur++] = data;
	}

	template <typename T>
	void Stack<T>::pop() {
		if (isEmpty())
			throw - 1;

		--cur;
	}

	template <typename T>
	bool Stack<T>::isFull() {
		return cur == MAX_STACK_SIZE;
	}

	template <typename T>
	bool Stack<T>::isEmpty() {
		return cur == 0;
	}
}

#endif