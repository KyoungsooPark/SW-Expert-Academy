/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu
*/

#include <cstdio>
using namespace std;

bool check[101];
int map[20][20];
int dx[4] = { 1, 1, -1, -1 };	// 시계방향
int dy[4] = { 1, -1, -1, 1 };	// 시계방향
int N, x0, y0, ans;

int max(int a, int b) { return a >= b ? a : b; }

void go(int x, int y, int d, int n) {
	if (x == x0 && y == y0) {	// 시작점
		if (check[map[x][y]]) {	// 한 바퀴 돌아온 경우
			ans = max(ans, n);
			return;
		}
		// 시작점과 다음 지점 디저트가 같은 경우 진행하지 않음
		if (map[x][y] == map[x + 1][y + 1])	return;

		check[map[x][y]] = true;
		go(x + 1, y + 1, d, n + 1);	// 시작점에서는 오른쪽 아래로 진행
		check[map[x][y]] = false;
		return;
	}

	check[map[x][y]] = true;
	// d = 3인 경우를 제외하고 동일방향 진행 혹은 시계방향 회전
	// d = 3인 경우는 동일방향만 진행
	for (int nd = d; nd <= d + 1 && nd < 4; nd++) {
		int nx = x + dx[nd], ny = y + dy[nd];
		// 시작점보다 높이 올라가지 않음
		if (x0 <= nx && nx < N && 0 <= ny && ny < N)
			// 먹지 않은 디저트거나 시작점인 경우
			if (!check[map[nx][ny]] || (nx == x0 && ny == y0))
				go(nx, ny, nd, n + 1);
	}
	check[map[x][y]] = false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		// 처리부
		ans = -1;
		for (x0 = 0; x0 < N - 2; x0++)
			for (y0 = 1; y0 < N - 1; y0++)
				go(x0, y0, 0, 0);
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}