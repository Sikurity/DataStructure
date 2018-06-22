#ifndef LIST_H
#define LIST_H

namespace lys {

	template <typename T>
	struct Node {
		T value;
		Node<T> *next;

		Node<T>(T d);
	};

	template <typename T>
	Node<T>::Node(T d) {
		value = d;
		next = nullptr;
	}

	template <typename T>
	struct List {
	
	private:
		int count;
		Node<T> *head;

	public:

		List();

		void insert(T d, int position) throw;

		void remove(int position);

		int search(T d);

		void update(T d, int position);

		void print();
	};

	template <typename T>
	List<T>::List() {
		count = 0;
		head = nullptr;
	}

	template <typename T>
	void List<T>::insert()(T d, int position) {

		if (0 <= position && position <= count) {
			
			Node *node = new Node(d);
			Node *target = head;

			if (position) {

				
				for (int i = 1; i < position; i++)
					target = target->next;

				node->next = target->next;
				target->next = node;
			}
			else {
				node->next = target;
				target = node;
			}

			count++;
		}
		else {
			throw -1;
		}
	}

	template <typename T>
	void List<T>::remove(int position) {
		if (0 <= position && position < count) {
			
			Node *target = head;

			if (position) {

				for (int i = 1; i < position; i++)
					target = target->next;

				target->next = target->next->next;
			}
			else {
				head = target->next;
			}

			delete target;

			count--;
		}
		else {
			throw - 1;
		}
	}
}

#endif
