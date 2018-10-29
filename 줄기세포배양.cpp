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
		// 세포가 죽더라도 소멸되지 않고 남아있으므로 리셋해줘야 함
		memset(board, 0, sizeof(board));

		// 입력부
		scanf("%d %d %d", &N, &M, &K);
		for (int n = 150; n < N + 150; n++) {
			for (int m = 150; m < M + 150; m++) {
				scanf("%d", &board[n][m]);
				if (board[n][m])
					q[board[n][m]].push({ n, m, board[n][m] * 2 });
			}
		}

		// 처리부
		while (K--) {
			// 우선순위에 따라 (생명력이 강한 줄기세포부터) 번식
			for (int l = 10; l > 0; l--) {
				// 큐 내의 줄기세포 모두 수행
				int qsize = q[l].size();
				while (qsize--) {
					cell c = q[l].front();
					q[l].pop();
					// 줄기세포가 활성화된 경우
					if (c.life == board[c.x][c.y]) {
						// 네 방향으로
						for (int i = 0; i < 4; i++) {
							int nx = c.x + dx[i], ny = c.y + dy[i];
							// 세포가 존재하지 않는 곳에 동시에 번식
							if (board[nx][ny] == 0) {
								board[nx][ny] = c.life;
								q[l].push({ nx, ny, c.life * 2 });
							}
						}
					}
					// 줄기세포는 시간이 지남에 따라 (K가 감소함에 따라) 생명 감소
					if (--c.life > 0)
						// 죽지 않은 세포는 큐에 다시 삽입
						q[l].push(c);
				}
			}
		}

		// 출력부
		for (int l = 1; l <= 10; l++)
			ans += q[l].size();
		printf("#%d %d\n", t, ans);
	}
	return 0;
}