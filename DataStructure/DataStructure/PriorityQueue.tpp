//  PriorityQueue.tpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

template <typename T>
PriorityQueue<T>::PriorityQueue() {
	last = 0;
}

template <typename T>
bool PriorityQueue<T>::isFull() {
	return last == MAX_QUEUE_SIZE;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() {
	return last == 0;
}

template <typename T>
void PriorityQueue<T>::push(T data) {
	if (isFull())
		throw - 1;

	datas[++last] = data;

	int me = last;
	int parent = me >> 1;

	while (1 <= parent) {
		if (datas[me] < datas[parent])
			swap(datas[me], datas[parent]);
		else
			break;

		me = parent;
		parent = me >> 1;
	}
}

template <typename T>
void PriorityQueue<T>::pop() {
	if (isEmpty())
		throw - 1;

	swap(datas[1], datas[last--]);

	int me = 1;
	int l = me << 1;
	int r = l | 1;

	while (l <= last) {
		int p = l;
		if (r <= last && datas[r] < datas[l])
			p = r;

		if (datas[p] < datas[me])
			swap(datas[p], datas[me]);
		else
			break;

		me = p;
		l = me << 1;
		r = l | 1;
	}
}

template <typename T>
T PriorityQueue<T>::getTop() {

	if (isEmpty())
		throw - 1;

	return datas[1];
}
