/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PobmqAPoDFAUq&categoryId=AV5PobmqAPoDFAUq&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int arr[10][10];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

// 달팽이 배열 생성
void snail_array(int N) {
	int x = 0, y = -1, cnt, d = 0, n = 1;
	cnt = 2 * N - 1;
	while (cnt--) {
		for (int i = 0; i < N; i++) {
			x += dx[d], y += dy[d];
			arr[x][y] = n++;
		}
		d == 3 ? d = 0 : d++;
		if (d % 2)
			N--;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		// 입력부
		scanf("%d", &N);
		// 처리부
		snail_array(N);
		// 출력부
		printf("#%d\n", t);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%d ", arr[i][j]);
			printf("\n");
		}
	}
	return 0;
}
