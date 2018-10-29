/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <cstring>
#include <queue>
#define MAXSIZE    150 + 50 + 150
using namespace std;
typedef struct cell { int x, y, life; } cell;

int board[MAXSIZE][MAXSIZE];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K, ans = 0;
		queue<cell> q[11];
		// ������ �״��� �Ҹ���� �ʰ� ���������Ƿ� ��������� ��
		memset(board, 0, sizeof(board));

		// �Էº�
		scanf("%d %d %d", &N, &M, &K);
		for (int n = 150; n < N + 150; n++) {
			for (int m = 150; m < M + 150; m++) {
				scanf("%d", &board[n][m]);
				if (board[n][m])
					q[board[n][m]].push({ n, m, board[n][m] * 2 });
			}
		}

		// ó����
		while (K--) {
			// �켱������ ���� (������� ���� �ٱ⼼������) ����
			for (int l = 10; l > 0; l--) {
				// ť ���� �ٱ⼼�� ��� ����
				int qsize = q[l].size();
				while (qsize--) {
					cell c = q[l].front();
					q[l].pop();
					// �ٱ⼼���� Ȱ��ȭ�� ���
					if (c.life == board[c.x][c.y]) {
						// �� ��������
						for (int i = 0; i < 4; i++) {
							int nx = c.x + dx[i], ny = c.y + dy[i];
							// ������ �������� �ʴ� ���� ���ÿ� ����
							if (board[nx][ny] == 0) {
								board[nx][ny] = c.life;
								q[l].push({ nx, ny, c.life * 2 });
							}
						}
					}
					// �ٱ⼼���� �ð��� ������ ���� (K�� �����Կ� ����) ���� ����
					if (--c.life > 0)
						// ���� ���� ������ ť�� �ٽ� ����
						q[l].push(c);
				}
			}
		}

		// ��º�
		for (int l = 1; l <= 10; l++)
			ans += q[l].size();
		printf("#%d %d\n", t, ans);
	}
	return 0;
}