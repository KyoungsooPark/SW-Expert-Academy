/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpLlKAQ4DFAUq&categoryId=AV5PpLlKAQ4DFAUq&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	80	// 20시간 후 queue의 최대 길이 = 4 * 19 = 76
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

// 위쪽으로 진행
void up(int x, int y) {
	x += dx[0];
	if (0 <= x && x < N && !visited[x][y]) {
		switch (map[x][y]) {	// 다음 터널의 구조물 타입
		case 1: case 2: case 5: case 6:	// ┼, │, ┌, ┐
			push({ x, y }), visited[x][y] = true;
		}
	}
}
// 아래쪽으로 진행
void down(int x, int y) {
	x += dx[1];
	if (0 <= x && x < N && !visited[x][y]) {
		switch (map[x][y]) {	// 다음 터널의 구조물 타입
		case 1: case 2: case 4: case 7:	// ┼, │, └, ┘
			push({ x, y }), visited[x][y] = true;
		}
	}
}
// 왼쪽으로 진행
void left(int x, int y) {
	y += dy[2];
	if (0 <= y && y < M && !visited[x][y]) {
		switch (map[x][y]) {	// 다음 터널의 구조물 타입
		case 1: case 3: case 4: case 5:	// ┼, ─, └, ┌
			push({ x, y }), visited[x][y] = true;
		}
	}
}
// 오른쪽으로 진행
void right(int x, int y) {
	y += dy[3];
	if (0 <= y && y < M && !visited[x][y]) {
		switch (map[x][y]) {	// 다음 터널의 구조물 타입
		case 1: case 3: case 6: case 7:	// ┼, ─, ┐, ┘
			push({ x, y }), visited[x][y] = true;
		}
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
				scanf("%d", &map[n][m]), visited[n][m] = false;

		// 처리부
		push({ R, C }), visited[R][C] = true;
		while (--L) {
			int qsize = size();
			if (qsize == 0) break;
			while (qsize--) {
				node now = pop();
				switch (map[now.x][now.y]) {	// 현재 위치의 터널 구조물 타입
				case 1:	// ┼
					up(now.x, now.y), down(now.x, now.y), left(now.x, now.y), right(now.x, now.y); break;
				case 2:	// │
					up(now.x, now.y), down(now.x, now.y); break;
				case 3:	// ─
					left(now.x, now.y), right(now.x, now.y); break;
				case 4:	// └
					up(now.x, now.y), right(now.x, now.y); break;
				case 5:	// ┌
					down(now.x, now.y), right(now.x, now.y); break;
				case 6:	// ┐
					down(now.x, now.y), left(now.x, now.y); break;
				case 7:	// ┘
					up(now.x, now.y), left(now.x, now.y); break;
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
