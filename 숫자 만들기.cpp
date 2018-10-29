/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH&categoryId=AWIeRZV6kBUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int num[12], optr[4], opt_cmb[11];
int N, max, min;

int calculate(void) {
	int ret = num[0];
	for (int i = 0; i < N - 1; i++) {
		switch (opt_cmb[i]) {
		case 0: ret += num[i + 1]; break;
		case 1: ret -= num[i + 1]; break;
		case 2: ret *= num[i + 1]; break;
		case 3: ret /= num[i + 1]; break;
		}
	}
	return ret;
}

void go(int n) {
	if (n == N - 1) {
		int temp = calculate();
		if (max < temp)
			max = temp;
		if (min > temp)
			min = temp;
		return;
	}

	for (int j = 0; j < 4; j++) {
		// 연산자 개수가 남아있는 경우
		if (optr[j] > 0) {
			// 개수를 하나 줄이고
			optr[j]--;
			// 해당 연산자를 입력
			opt_cmb[n] = j;
			// 다음 순서 진행
			go(n + 1);
			// 개수 반환
			optr[j]++;
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		max = -2e9, min = 2e9;

		// 입력부
		scanf("%d", &N);
		// optr[0]: + 연산자 개수
		// optr[1]: - 연산자 개수
		// optr[2]: * 연산자 개수
		// optr[3]: / 연산자 개수
		for (int i = 0; i < 4; i++)
			scanf("%d", &optr[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &num[i]);

		// 처리부
		go(0);

		// 출력부
		printf("#%d %d\n", t, max - min);
	}
	return 0;
}