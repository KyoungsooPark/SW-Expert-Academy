/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } wormhole;
int board[102][102];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int bounce[4][4] = {
	{ 1, 3, 0, 2 },	// 1번 블록에 튕겨서 나가는 방향
	{ 1, 2, 3, 0 },	// 2번 블록에 튕겨서 나가는 방향
	{ 2, 0, 3, 1 },	// 3번 블록에 튕겨서 나가는 방향
	{ 3, 0, 1, 2 }	// 4번 블록에 튕겨서 나가는 방향
};
int N, ans;

int next_direction(int block, int direction) { return bounce[block - 1][direction]; }

void go(int x, int y, int d, int s, vector<wormhole> wh[]) {
	// 다음 목적지 탐색
	int nx = x + dx[d], ny = y + dy[d], nd;
	switch (d) {
	case 0: case 1:	// 우, 좌
		while (board[nx][ny] == 0) ny += dy[d];
		break;
	case 2: case 3: // 하, 상
		while (board[nx][ny] == 0) nx += dx[d];
		break;
	}
	// 다음 목적지 유형 검사 후 재귀 또는 종료
	switch (board[nx][ny]) {
	case -1:	// 시작점 또는 블랙홀
		if (ans < s)
			ans = s;
		return;
	case 1: case 2: case 3: case 4:	// 1~4번 블록
		nd = next_direction(board[nx][ny], d);
		go(nx, ny, nd, s + 1, wh);
		break;
	case 5:	// 5번 블록
		s = s * 2 + 1;
		if (ans < s)
			ans = s;
		return;
	case 6: case 7: case 8: case 9: case 10:	// 웜홀
		int idx = board[nx][ny] - 6;
		if (nx == wh[idx][0].x && ny == wh[idx][0].y)
			nx = wh[idx][1].x, ny = wh[idx][1].y;
		else
			nx = wh[idx][0].x, ny = wh[idx][0].y;
		go(nx, ny, d, s, wh);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		vector<wormhole> arr[5];
		scanf("%d", &N);
		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
					board[i][j] = 5;
					continue;
				}
				scanf("%d", &board[i][j]);
				if (board[i][j] >= 6)
					arr[board[i][j] - 6].push_back({ i, j });
			}
		}

		// 처리부
		ans = 0;
		for (int x = 1; x <= N; x++) {
			for (int y = 1; y <= N; y++) {
				if (board[x][y] == 0) {
					board[x][y] = -1;
					for (int d = 0; d < 4; d++)
						go(x, y, d, 0, arr);
					board[x][y] = 0;
				}
			}
		}

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}