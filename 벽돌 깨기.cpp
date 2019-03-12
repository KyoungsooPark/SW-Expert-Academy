/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, r; } block;
int map[15][12], cpy[15][12], drop_cols[4];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, W, H, ans;
// 벽돌 낙하
void drop(void) {
	for (int w = 0; w < W; w++) {
		for (int h = H - 1; h > 0; h--) {
			if (!cpy[h][w]) {
				for (int hh = h - 1; hh >= 0; hh--) {
					if (cpy[hh][w]) {
						cpy[h--][w] = cpy[hh][w];
						cpy[hh][w] = 0;
					}
				}
				break;
			}
		}
	}
}
// 완성된 drop_cols를 이용하여 시뮬레이션
int simulation(void) {
	queue<block> q;
	int ret = 0;
	// 맵 카피
	for (int h = 0; h < H; h++)
		for (int w = 0; w < W; w++)
			cpy[h][w] = map[h][w];

	// N회 구슬 낙하
	for (int i = 0; i < N; i++) {
		int w = drop_cols[i];	// 구슬 낙하 열
		for (int h = 0; h < H; h++) {	// 구슬이 떨어질 벽돌 위치 탐색
			if (cpy[h][w]) {
				q.push({ h, w, cpy[h][w] });
				cpy[h][w] = 0;
				break;
			}
		}
		while (!q.empty()) {
			block b = q.front(); q.pop();
			for (int r = 1; r < b.r; r++) {
				for (int d = 0; d < 4; d++) {
					int nx = b.x + dx[d] * r, ny = b.y + dy[d] * r;
					if (0 <= nx && nx < H && 0 <= ny && ny < W && cpy[nx][ny]) {
						q.push({ nx, ny, cpy[nx][ny] });
						cpy[nx][ny] = 0;
					}
				}
			}
		}
		drop();
	}

	// 남은 벽돌 개수 반환
	for (int h = 0; h < H; h++)
		for (int w = 0; w < W; w++)
			if (cpy[h][w])
				ret++;
	return ret;
}

void go(int n) {
	if (n == N) {	// 순열 완성
		ans = min(ans, simulation());
		return;
	}
	for (int w = 0; w < W; w++) {
		drop_cols[n] = w;
		go(n + 1);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d %d", &N, &W, &H);
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				scanf("%d", &map[h][w]);
		// 처리부
		ans = 2e9;
		go(0);
		// 출력부
		printf("#%d %d\n", t, ans);
	}

	return 0;
}