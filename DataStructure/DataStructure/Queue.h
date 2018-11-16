#ifndef QUEUE_H
#define QUEUE_H

namespace lys {

	template <typename T>
	struct Queue {

		static const int MAX_QUEUE_SIZE;

	private:

		int rear;
		int front;

		T datas[MAX_QUEUE_SIZE];

	public:

		Queue(): MAX_QUEUE_SIZE(100000);

		void push(T d) throw(int);

		void pop() throw(int);

		T front();

		bool isEmpty();

		bool isFull();
	};

	template <typename T>
	Queue<T>::Queue() {
		rear = front = 0;
	}

	template <typename T>
	void Queue<T>::push(T d) throw(int) {

		if (isFull())
			throw - 1;

		rear = (rear + 1) % MAX_QUEUE_SIZE;
		datas[rear] = d;
	}

	template <typename T>
	T Queue<T>::front() {

		if (isEmpty())
			throw - 1;

		return datas[front];
	}

	template <typename T>
	void Queue<T>::pop() throw(int) {

		if (isEmpty())
			throw -1;

		front = (front + 1) % MAX_QUEUE_SIZE;
		return datas[front];
	}

	template <typename T>
	bool Queue<T>::isEmpty() {
		return front == rear;
	}

	template <typename T>
	bool Queue<T>::isFull() {
		return front == (rear + 1) % MAX_QUEUE_SIZE;
	}
}

#endif