/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
*/

#include <cstdio>
#define UP	1
#define DOWN	2
#define LEFT	3
#define RIGHT	4

using namespace std;
typedef struct {
	int cnt;	// 미생물의 수
	int dir;	// 진행 방향
	int maxcnt;	// 해당 칸으로 여러 군집이 왔을 경우 가장 큰 군집의 미생물의 수
} node;

node map[100][100];			// 현재 미생물 정보
node next_map[100][100];	// 1시간 후 미생물 정보
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };
int N, M, K;

void move(void) {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (map[x][y].cnt > 0) {
				int nx = x + dx[map[x][y].dir];
				int ny = y + dy[map[x][y].dir];

				// 약품 처리된 곳인 경우
				if (nx == 0 || nx == N - 1 || ny == 0 || ny == N - 1) {
					next_map[nx][ny].cnt = map[x][y].cnt / 2;
					// 진행방향 반전
					switch (map[x][y].dir) {
					case UP: next_map[nx][ny].dir = DOWN; break;
					case DOWN: next_map[nx][ny].dir = UP; break;
					case LEFT: next_map[nx][ny].dir = RIGHT; break;
					case RIGHT: next_map[nx][ny].dir = LEFT; break;
					}
				}
				else {
					next_map[nx][ny].cnt += map[x][y].cnt;
					if (map[x][y].cnt > next_map[nx][ny].maxcnt) {
						next_map[nx][ny].maxcnt = map[x][y].cnt;
						next_map[nx][ny].dir = map[x][y].dir;
					}
				}
			}
		}
	}

	// next_map 정보를 map으로 옮긴 후 next_map 초기화
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			map[x][y] = next_map[x][y], next_map[x][y] = { 0, 0, 0 };
}

// 남아있는 총 미생물 수 반환
int get_answer(void) {
	int sum = 0;
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			sum += map[x][y].cnt;
	return sum;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int x, y, c, d;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				map[i][j] = { 0, 0, 0 };

		// 입력부
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &x, &y, &c, &d);
			map[x][y] = { c, d, c };
		}

		// 처리부
		while (M--)
			move();

		// 출력부
		printf("#%d %d\n", t, get_answer());
	}
	return 0;
}
