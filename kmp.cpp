// DataStructure.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "stack.h"
#include "algorithm.h"

#define MAX_STR_LENGTH 1000

lys::Stack<> S;

int *getPi(std::string p) {

	int m = static_cast<int>(p.size());
	int j = 0;

	int *pi = static_cast<int *>(calloc(m, sizeof(int)));

	for (int i = 1; i < m; i++) {
		while (j > 0 && p[i] != p[j])
			j = pi[j - 1];
		if (p[i] == p[j])
			pi[i] = ++j;
	}

	return pi;
}

void kmp(std::string a, std::string b, int *pi) {
	int j = 0;

	int size = (int)a.length();
	for (int i = 0; i < size; i++) {

		while (j > 0 && a[i] != b[j])       // 현재 j만큼 찾았는데 이번에 비교하는 문자가 다른 경우
			j = pi[j - 1];					// 문자열 B를 failure function 이후 부터 비교를 해줍니다.

		if (a[i] == b[j]) {					// 비교하는 문자가 같은 경우
			if (j == b.length() - 1) {		// 문자열 B를 전부 탐색하였기 때문에 답에 위치를 넣어줍니다.
				S.push(i - b.length() + 1);
				j = pi[j];					// 다음 탐색을 위하여 이번에도 failure function 이후 부터 비교를 해줍니다.
			}
			else
				j++;						// 문자열 B의 다음 단어를 비교해줍니다.
		}
	}
}

struct Test {
	int a;
	int b;
};

int main()
{
	int arr[] = { 5, 1, 4, 2, 3 };

	int size = sizeof(arr) / sizeof(int);
	lys::quicksort(arr, 0, size - 1);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	char input[MAX_STR_LENGTH + 1];

	scanf("%s", input);
	std::string keyword(input);

	scanf("%s", input);
	std::string str(input);

	int *pi = getPi(keyword);

	kmp(str, keyword, pi);

	while (!S.isEmpty()) {
		printf("%d\n", S.top());
		S.pop();
	}

	free(pi);

	return 0;
}