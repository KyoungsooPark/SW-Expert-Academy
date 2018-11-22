/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH&categoryId=AWIeUtVakTMDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

bool check[16];
int table[16][16];
int N, ans;

int min(int a, int b) { return a <= b ? a : b; }

int cal(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i] != check[j])
				continue;
			if (check[i])
				// A 요리의 재료
				ret += table[i][j];
			else
				// B 요리의 재료
				ret -= table[i][j];
		}
	}
	// 절대값 반환
	return ret >= 0 ? ret : -ret;
}

void go(int n, int cur) {
	if (n == N / 2) {
		ans = min(ans, cal());
		return;
	}
	// nC(n/2) 조합
	for (int i = cur; i <= N / 2 + n; i++) {
		// A 요리의 재료 선택
		check[i] = true;
		go(n + 1, i + 1);
		check[i] = false;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &table[i][j]);

		// 처리부
		ans = 2e9;
		go(0, 0);

		//출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
