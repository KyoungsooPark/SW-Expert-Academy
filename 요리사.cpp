/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH&categoryId=AWIeUtVakTMDFAVH&categoryType=CODE
*/

#include <cstdio>
#include <vector>
using namespace std;

int table[16][16];
bool visited[16];
vector<int> A;
int N, ans;

int calculate(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i] != visited[j])
				continue;
			// A 요리의 재료
			if (visited[i])
				ret += table[i][j];
			// B 요리의 재료
			else
				ret -= table[i][j];
		}
	}
	// 절대값 반환
	return ret > 0 ? ret : -ret;
}

void go(int n, int cur) {
	if (n == N / 2) {
		int temp = calculate();
		if (ans > temp)
			ans = temp;
		return;
	}
	
	// nC(n/2) 조합을 위한 범위
	for (int i = cur; i <= N / 2 + n; i++) {
		// A 요리의 재료 선택
		visited[i] = true;
		go(n + 1, i + 1);
		visited[i] = false;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
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