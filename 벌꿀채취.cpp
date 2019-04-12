/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu
*/

#include <cstdio>
using namespace std;

int map[10][10];
int N, M, C, x1, y1, x2, y2, ans;

int max(int a, int b) { return a > b ? a : b; }
// 주어진 시작지점(x, y)부터 M개의 벌통 중 수익의 합의 최대값 계산
int cal(int x, int y) {
	int ret = 0, temp1, temp2;
	for (int i = 1; i < (1 << M); i++) {
		temp1 = temp2 = 0;
		for (int j = 0; j < M; j++)
			if (i & (1 << j))
				temp1 += map[x][y + j], temp2 += map[x][y + j] * map[x][y + j];
		if (temp1 <= C)
			ret = max(ret, temp2);
	}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d %d", &N, &M, &C);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		// 처리부
		ans = 0;
		for (x1 = 0; x1 < N; x1++)
			for (y1 = 0; y1 <= N - M; y1++) {	// 일꾼1의 시작점
				int cal1 = cal(x1, y1);	// 일꾼1의 벌꿀 채취 최대 양
				for (x2 = x1; x2 < N; x2++)
					for (y2 = x1 == x2 ? y1 + M : 0; y2 <= N - M; y2++)	// 일꾼2의 시작점
						if (y2 <= N - M)
							ans = max(ans, cal1 + cal(x2, y2));	// 최대 수익 계산
			}
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
