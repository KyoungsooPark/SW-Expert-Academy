/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE
*/

#include <cstdio>
#define MAX	150 + 50 + 150
#define QUEUESIZE	700
using namespace std;
typedef struct { int x, y, life; } cell;

cell q[10][QUEUESIZE];	// 우선순위 큐
int map[MAX][MAX];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int begin[10], end[10];

int size(int p) { return begin[p] <= end[p] ? end[p] - begin[p] : QUEUESIZE + end[p] - begin[p]; }
void push(int p, cell c) { q[p][end[p]++] = c; if (end[p] == QUEUESIZE) end[p] = 0; }
cell pop(int p) { cell ret = q[p][begin[p]++]; if (begin[p] == QUEUESIZE) begin[p] = 0; return ret; }

void reset(void) {
	// 세포가 죽더라도 소멸되지 않고 남아있으므로 리셋해줘야 함
	for (int n = 0; n < MAX; n++)
		for (int m = 0; m < MAX; m++)
			map[n][m] = 0;
	// 우선순위 큐 초기화
	for (int p = 0; p < 10; p++)
		begin[p] = end[p] = 0;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K, ans = 0;

		// 입력부
		scanf("%d %d %d", &N, &M, &K);
		for (int n = 150; n < N + 150; n++) {
			for (int m = 150; m < M + 150; m++) {
				scanf("%d", &map[n][m]);
				if (map[n][m])
					push(map[n][m] - 1, { n, m, map[n][m] * 2 });
			}
		}

		// 처리부
		while (K--) {
			for (int p = 9; p >= 0; p--) {	// 생명력이 강한 줄기세포부터 번식
				int qsize = size(p);
				while (qsize--) {	// 큐 내의 줄기세포 모두 수행
					cell now = pop(p);
					if (now.life == map[now.x][now.y]) {	// 줄기세포가 활성화된 경우
						for (int d = 0; d < 4; d++) {
							int nx = now.x + dx[d], ny = now.y + dy[d];
							if (map[nx][ny] == 0) {	// 네 방향 중 세포가 존재하지 않는 곳에 번식
								map[nx][ny] = now.life;
								push(p, { nx, ny, now.life * 2 });
							}
						}
					}
					if (--now.life)	// 줄기세포는 시간이 지남에 따라 (K가 감소함에 따라) 생명 감소
						push(p, now);	// 죽지 않은 세포는 큐에 다시 삽입
				}
			}
		}

		// 출력부
		for (int p = 0; p < 10; p++)
			ans += size(p);

		printf("#%d %d\n", t, ans);
		reset();	// 초기화
	}
	return 0;
}
