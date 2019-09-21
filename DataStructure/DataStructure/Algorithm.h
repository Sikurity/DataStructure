template <typename T>
inline void SWAP(T &a, T &b) {

	T t = a;
	a = b;
	b = t;
}

template <typename T>
inline int partition(T list[], int l, int r) {
	int m = (l + r) >> 1;

	if (list[r] < list[l])
		SWAP(list[r], list[l]);

	if (list[m] < list[l])
		SWAP(list[m], list[l]);

	if (list[r] < list[m])
		SWAP(list[r], list[m]);

	T pivot = list[m];
	int low = l - 1;
	int high = r + 1;

	while (true) {
		while (list[++low] < pivot);
		while (pivot < list[--high]);

		if (high <= low)
			break;

		SWAP(list[low], list[high]);
	}

	return high;
}

template <typename T>
void quicksort(T list[], int l, int r) {
	if (l < r) {
		int p = partition(list, l, r);
		quicksort(list, l, p);
		quicksort(list, p + 1, r);
	}
}

template <typename T>
int lower_bound(T *list, int l, int r, T val) {
	int pos = r + 1;

	while (l <= r) {
		int m = (l + r) >> 1;
		if (val <= list[m]) {
			r = m - 1;
			pos = m;
		}
		else
			l = m + 1;
	}

	return pos;
}

template <typename T>
int upper_bound(T *list, int l, int r, T val) {
	int pos = l - 1;

	while (l <= r) {
		int m = (l + r) >> 1;
		if (val >= list[m]) {
			l = m + 1;
			pos = m;
		}
		else
			r = m - 1;
	}

	return pos + 1;
}