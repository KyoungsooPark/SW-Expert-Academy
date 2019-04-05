/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int n, max; } point;
typedef struct { int x, y, n, d; } microbe;

point map[100][100], next_map[100][100];
int dx[5] = { 0, -1, 1, 0, 0 };	// 1: 상, 2: 하, 3: 좌, 4: 우
int dy[5] = { 0, 0, 0, -1, 1 };	// 1: 상, 2: 하, 3: 좌, 4: 우
int N, M, K;

bool isedge(int x, int y) { return x == 0 || x == N - 1 || y == 0 || y == N - 1; }
// 미생물 총합 계산
int count(void) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (map[i][j].n)
				ret += map[i][j].n;
			map[i][j] = { 0, 0 };
		}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		queue<microbe> q;
		// 입력부
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < K; i++) {
			int x, y, n, d;
			scanf("%d %d %d %d", &x, &y, &n, &d);
			q.push({ x, y, n, d });
			map[x][y] = { n, n };
		}
		// 처리부
		while (M--) {
			int size = q.size();
			while (size--) {
				microbe m = q.front(); q.pop();
				if (m.n == map[m.x][m.y].max) {	// 현재 위치의 군집 중 미생물 수가 가장 많은 군집
					if (m.n < map[m.x][m.y].n)	// 다른 군집도 모인 경우
						m.n = map[m.x][m.y].n;	// 군집 합침

					m.x += dx[m.d], m.y += dy[m.d];	// 이동 위치 계산
					if (isedge(m.x, m.y)) {	// 이동 위치가 가장자리
						m.n >>= 1;	// 미생물 수 반감
						if (!m.n) continue;	// 미생물이 모두 죽음
						m.d % 2 ? m.d++ : m.d--;	// 방향 반전
					}

					next_map[m.x][m.y].n += m.n;	// 다음 위치에 미생물 수 누산
					if (m.n > next_map[m.x][m.y].max) {	// 해당 위치로 이동한 군집 중 최대 미생물 수 업데이트
						next_map[m.x][m.y].max = m.n;
						q.push(m);
					}
				}
			}
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					// 맵 업데이트
					map[i][j] = next_map[i][j], next_map[i][j] = { 0, 0 };
		}
		// 출력부
		printf("#%d %d\n", t, count());
	}
	return 0;
}