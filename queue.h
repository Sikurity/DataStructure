#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 1000

namespace lys {

	template <typename T>
	struct Queue {

	private:

		int rear;
		int front;

		T datas[MAX_QUEUE_SIZE];

	public:

		Queue();

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
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			datas[rear] = d;
		}
	}

	template <typename T>
	T Queue<T>::front() {
		return datas[rear];
	}

	template <typename T>
	void Queue<T>::pop() throw(int) {

		if (isEmpty())
			throw -1;
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return datas[front];
		}
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