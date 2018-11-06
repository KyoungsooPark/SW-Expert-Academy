/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu&categoryId=AV5VwAr6APYDFAWu&categoryType=CODE
*/

#include <cstdio>
using namespace std;

bool visited[101];
int map[20][20];
int dxy[4][2] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };	// 시계방향으로 12시부터 회전
int N, xs, ys, ans;

void go(int x, int y, int d, int n) {
	if (x == xs && y == ys) {
		// 한 바퀴 순회 후 시작지점으로 돌아온 경우
		if (visited[map[x][y]]) {
			if (ans < n)
				ans = n;
			return;
		}

		// 탐색 시작인 경우 현재 디저트와 오른쪽 하단의 디저트가 같다면 탐색하지 않음
		if (map[x + 1][y + 1] == map[x][y])
			return;

		// 시작지점에서 탐색은 항상 오른쪽 하단으로 진행
		visited[map[x][y]] = true;
		go(x + 1, y + 1, d, n + 1);
		visited[map[x][y]] = false;
	}
	else {
		visited[map[x][y]] = true;
		// 다음 방향은 이전 진행 방향과 동일하거나 시계방향에 맞게 변경
		for (int nd = d; nd <= d + 1; nd++) {
			int nx = x + dxy[nd][0], ny = y + dxy[nd][1];
			// nx는 시작지점보다 위로 넘어갈 수 없음
			if (xs <= nx && nx < N && 0 <= ny && ny < N) {
				// 먹지 않은 디저트이거나 시작지점인 경우만 진행
				if (!visited[map[nx][ny]] || (nx == xs && ny == ys))
					go(nx, ny, nd, n + 1);
			}
		}
		visited[map[x][y]] = false;
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
				scanf("%d", &map[i][j]);

		// 처리부
		ans = -1;
		// 대각선 좌/우, 또는 하단으로 진행하지 못하는 시작지점을 제외하고 탐색
		for (xs = 0; xs < N - 3; xs++)
			for (ys = 1; ys < N - 1; ys++)
				// 시작지점에서 탐색은 항상 오른쪽 하단으로 진행
				go(xs, ys, 0, 0);

		//출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}