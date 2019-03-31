/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, d, k; } atom;

queue<atom> q;
int map[4001][4001];	// -1000 ~ 1000 => 0 ~ 2000 => 0 ~ 4000 (0.5초 단위)
int dx[4] = { -1, 1, 0, 0 };	// 상, 하, 좌, 우
int dy[4] = { 0, 0, -1, 1 };	// 상, 하, 좌, 우
int N, ans;

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int x, y, d, k;
			scanf("%d %d %d %d", &y, &x, &d, &k);
			x = 2000 - 2 * x, y = 2000 + 2 * y;
			q.push({ x, y, d, k });
			map[x][y] = k;	// 초기 원자 위치의 에너지 크기 표시
		}
		// 처리부
		ans = 0;
		while (!q.empty()) {
			atom now = q.front(); q.pop();
			if (map[now.x][now.y] > now.k) {	// 현재 위치에 여러 개의 원자 존재
				ans += map[now.x][now.y];	// 폭발. 방출 에너지 합산
				map[now.x][now.y] = 0;	// 해당 위치의 에너지 모두 방출
			}
			else if (map[now.x][now.y] == now.k) {	// 현재 위치에 하나의 원자만 존재
				map[now.x][now.y] = 0;	// 원자 이동을 위해 현재 위치의 에너지 초기화
				now.x += dx[now.d], now.y += dy[now.d];	// 원자 이동
				if (0 <= now.x && now.x <= 4000 && 0 <= now.y && now.y <= 4000) {
					map[now.x][now.y] += now.k;	// 이동한 위치에 에너지 누적
					q.push(now);
				}
			}
		}
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}