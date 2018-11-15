/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpLlKAQ4DFAUq&
*/

#include <cstdio>
#define QUEUESIZE	700
using namespace std;
typedef struct { int x, y; } node;

node q[QUEUESIZE];
bool visited[50][50];
int map[50][50];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, M, begin, end;

int size(void) { return begin <= end ? end - begin : QUEUESIZE + end - begin; }
void push(node n) { q[end++] = n; if (end == QUEUESIZE) end = 0; }
node pop(void) { node ret = q[begin++]; if (begin == QUEUESIZE) begin = 0; return ret; }
bool isvalid(int x, int y) { return 0 <= x && x < N && 0 <= y && y < M && !visited[x][y]; }

// 위쪽으로 진행
void up(int x, int y) {
	int nx = x + dx[0], ny = y + dy[0];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {	// 다음 위치의 터널 구조물 타입
	case 1: case 2: case 5: case 6:	// ┼, │, ┌, ┐
		visited[nx][ny] = true;
		push({ nx, ny });
	}
}
// 아래쪽으로 진행
void down(int x, int y) {
	int nx = x + dx[1], ny = y + dy[1];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {	// 다음 위치의 터널 구조물 타입
	case 1: case 2: case 4: case 7:	// ┼, │, └, ┘
		visited[nx][ny] = true;
		push({ nx, ny });
	}
}
// 왼쪽으로 진행
void left(int x, int y) {
	int nx = x + dx[2], ny = y + dy[2];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {	// 다음 위치의 터널 구조물 타입
	case 1: case 3: case 4: case 5:	// ┼, ─, └, ┌
		visited[nx][ny] = true;
		push({ nx, ny });
	}
}
// 오른쪽으로 진행
void right(int x, int y) {
	int nx = x + dx[3], ny = y + dy[3];
	if (!isvalid(nx, ny)) return;
	switch (map[nx][ny]) {	// 다음 위치의 터널 구조물 타입
	case 1: case 3: case 6: case 7:	// ┼, ─, ┐, ┘
		visited[nx][ny] = true;
		push({ nx, ny });
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int R, C, L, ans = 0;
		begin = end = 0;

		// 입력부
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int n = 0; n < N; n++)
			for (int m = 0; m < M; m++)
				scanf("%d", &map[n][m]);
		for (int n = 0; n < 50; n++)
			for (int m = 0; m < 50; m++)
				visited[n][m] = false;

		// 처리부
		visited[R][C] = true;
		push({ R, C });
		while (--L) {
			int qsize = size();
			if (qsize == 0) break;
			while (qsize--) {
				node now = pop();
				switch (map[now.x][now.y]) {	// 현재 위치의 터널 구조물 타입
				case 1:	// ┼
					up(now.x, now.y); down(now.x, now.y); left(now.x, now.y); right(now.x, now.y); break;
				case 2:	// │
					up(now.x, now.y); down(now.x, now.y); break;
				case 3:	// ─
					left(now.x, now.y); right(now.x, now.y); break;
				case 4:	// └
					up(now.x, now.y); right(now.x, now.y); break;
				case 5:	// ┌
					down(now.x, now.y); right(now.x, now.y); break;
				case 6:	// ┐
					down(now.x, now.y); left(now.x, now.y); break;
				case 7:	// ┘
					up(now.x, now.y); left(now.x, now.y); break;
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
