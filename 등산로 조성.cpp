/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&categoryId=AV5PoOKKAPIDFAUq&categoryType=CODE
*/

#include <cstdio>
using namespace std;

bool visited[8][8];
int map[8][8];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, K, ans;

int max(int a, int b) { return a > b ? a : b; }

void go(int x, int y, int n, bool flag) {
	visited[x][y] = true;
	ans = max(ans, n);
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d], ny = y + dy[d];
		if (0 <= nx && nx < N && 0 <= ny && ny < N && !visited[nx][ny]) {
			if (map[nx][ny] < map[x][y])	// �� ���� ������ ���
				go(nx, ny, n + 1, flag);
			else if (!flag && map[nx][ny] - map[x][y] < K) {	// ��Ƽ� �̵� ������ ���
				int temp = map[nx][ny];	// ��� �� ����
				map[nx][ny] = map[x][y] - 1;	// ���� �� ����
				go(nx, ny, n + 1, true);
				map[nx][ny] = temp;
			}
		}
	}
	visited[x][y] = false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int M = 0;
		// �Էº�
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				M = max(M, map[i][j]);
			}
		// ó����
		ans = 1;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (map[i][j] == M)
					go(i, j, 1, false);
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}