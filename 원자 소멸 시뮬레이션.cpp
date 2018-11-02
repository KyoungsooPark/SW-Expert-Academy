/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	100000
using namespace std;
typedef struct { int r, c, d, k; } atom;
atom q[QUEUESIZE];
int map[4001][4001];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int begin, end;

bool empty(void) {
	return begin == end;
}

void push(atom a) {
	q[end++] = a;
	if (end == QUEUESIZE)
		end = 0;
}

atom pop(void) {
	atom ret = q[begin++];
	if (begin == QUEUESIZE)
		begin = 0;
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, ans = 0;
		begin = end = 0;

		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int c, r, d, k;
			scanf("%d %d %d %d", &c, &r, &d, &k);
			// 1초 단위를 0.5초 단위로 변경
			r = 4000 - (r + 1000) * 2;
			c = (c + 1000) * 2;
			map[r][c] = k;
			// 초기 원자들의 위치 큐에 삽입
			push({ r, c, d, k });
		}

		// 처리부
		while (!empty()) {
			atom a = pop();
			if (map[a.r][a.c] > a.k)
				ans += map[a.r][a.c];
			else {
				int nr = a.r + dr[a.d], nc = a.c + dc[a.d];
				if (0 <= nr && nr < 4001 && 0 <= nc && nc < 4001) {
					// 다음 위치에 원자가 존재하지 않으면
					if (map[nr][nc] == 0)
						// 다음 이동을 위해 큐에 삽입
						push({ nr, nc, a.d, a.k });
					// 존재하면 소멸로 인해 큐에 삽입하지 않고 방출할 에너지를 쌓아둠
					map[nr][nc] += map[a.r][a.c];
				}
			}
			// 이동 전 위치의 에너지를 0으로 변경
			map[a.r][a.c] = 0;
		}

		// 출력부
		printf("#%d %d\n", t, ans);
	}

	return 0;
}
