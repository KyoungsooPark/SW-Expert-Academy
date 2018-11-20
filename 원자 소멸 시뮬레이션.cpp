/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	1000
using namespace std;
typedef struct { int x, y, d, k; } atom;

atom q[1000];
int map[4001][4001];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int begin, end;

bool empty(void) { return begin == end; }
void push(atom a) { q[end++] = a; if (end == QUEUESIZE) end = 0; }
atom pop(void) { atom ret = q[begin++]; if (begin == QUEUESIZE) begin = 0; return ret; }

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, ans = 0;
		begin = end = 0;

		// 입력부
		scanf("%d", &N);
		for (int n = 0; n < N; n++) {
			int x, y, d, k;
			scanf("%d %d %d %d", &y, &x, &d, &k);
			// 1초 단위를 0.5초 단위로 변경
			x = 4000 - 2 * (x + 1000), y = 2 * (y + 1000);
			push({ x, y, d, k });	// 초기 원자들의 위치 큐에 삽입
			map[x][y] = k;	// 원자 위치에 에너지를 표시
		}

		// 처리부
		while (!empty()) {
			atom now = pop();
			// 현재 위치의 원자가 소멸한 경우
			if (map[now.x][now.y] == 0)
				continue;
			// 현재 위치에 두 개 이상의 원자가 존재하는 경우
			if (map[now.x][now.y] > now.k) {
				ans += map[now.x][now.y];	// 축적된 모든 에너지를 방출 후
				map[now.x][now.y] = 0;		// 소멸
				continue;
			}
			map[now.x][now.y] = 0;	// 원자가 이동하여 현재 위치의 에너지 0으로 변경
			now.x += dx[now.d], now.y += dy[now.d];	// 원자의 다음 위치 계산
			// 다음 위치가 맵의 범위 내일 경우
			if (0 <= now.x && now.x <= 4000 && 0 <= now.y && now.y <= 4000) {
				map[now.x][now.y] += now.k;	// 해당 위치에 원자의 에너지를 축적
				push(now);
			}
		}

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
