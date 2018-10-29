/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&
*/

#include <cstdio>
using namespace std;

int map[8][8];
bool visited[8][8];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int n, k, ans;

void go(int x, int y, int h, int l, bool flag) {
	if (ans < l)
		ans = l;
	visited[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (0 <= nx && nx < n && 0 <= ny && ny < n) {
			if (!visited[nx][ny]) {
				// ���� ��ġ�� ���簡 �ʿ����� ���� ���
				if (map[nx][ny] < h)
					go(nx, ny, map[nx][ny], l + 1, flag);
				// ���簡 �ʿ��� ��� �̹� ���縦 �������� �ʾҴٸ�
				else if (flag == false && map[nx][ny] - k < h)
					// ���� ��ġ�� ���̺��� 1 ���� ��ŭ�� ��� flag�� true�� ����
					go(nx, ny, h - 1, l + 1, true);
			}
		}
	}
	visited[x][y] = false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int peak = 0;

		// �Էº�
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
				if (peak < map[i][j])
					peak = map[i][j];
			}
		}

		// ó����
		ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j] == peak)
					go(i, j, map[i][j], 1, false);
			}
		}

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}