#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y; } node;

bool visited[50][50];
int map[50][50];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, M, begin, end;

bool isvalid(int x, int y) { return 0 <= x && x < N && 0 <= y && y < M && !visited[x][y]; }

void up(queue<node> &q, int x, int y) {
	int nx = x + dx[0], ny = y + dy[0];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {
	case 1: case 2: case 5: case 6:
		visited[nx][ny] = true;
		q.push({ nx, ny });
	}
}

void down(queue<node> &q, int x, int y) {
	int nx = x + dx[1], ny = y + dy[1];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {
	case 1: case 2: case 4: case 7:
		visited[nx][ny] = true;
		q.push({ nx, ny });
	}
}

void left(queue<node> &q, int x, int y) {
	int nx = x + dx[2], ny = y + dy[2];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {
	case 1: case 3: case 4: case 5:
		visited[nx][ny] = true;
		q.push({ nx, ny });
	}
}

void right(queue<node> &q, int x, int y) {
	int nx = x + dx[3], ny = y + dy[3];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {
	case 1: case 3: case 6: case 7:
		visited[nx][ny] = true;
		q.push({ nx, ny });
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int R, C, L, ans = 0;
		queue<node> q;

		// 입력부
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int n = 0; n < N; n++)
			for (int m = 0; m < M; m++) {
				scanf("%d", &map[n][m]);
				visited[n][m] = false;
			}

		// 처리부
		visited[R][C] = true;
		q.push({ R, C });
		while (--L) {
			int qsize = q.size();
			if (qsize == 0) break;
			while (qsize--) {
				node now = q.front();
				q.pop();
				switch (map[now.x][now.y]) {	// 현재 위치의 터널 구조물 타입
				case 1:
					up(q, now.x, now.y); down(q, now.x, now.y); left(q, now.x, now.y); right(q, now.x, now.y); break;
				case 2:
					up(q, now.x, now.y); down(q, now.x, now.y); break;
				case 3:
					left(q, now.x, now.y); right(q, now.x, now.y); break;
				case 4:
					up(q, now.x, now.y); right(q, now.x, now.y); break;
				case 5:
					down(q, now.x, now.y); right(q, now.x, now.y); break;
				case 6:
					down(q, now.x, now.y); left(q, now.x, now.y); break;
				case 7:
					up(q, now.x, now.y); left(q, now.x, now.y); break;
				}
			}
		}

		// 출력부
		for (int n = 0; n < N; n++)
			for (int m = 0; m < M; m++)
				if (visited[n][m])
					ans++;
		printf("#%d %d\n", t, ans);
	}
	return 0;
}