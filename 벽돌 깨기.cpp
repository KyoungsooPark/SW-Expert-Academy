/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&categoryId=AWXRQm6qfL0DFAUo&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	15 * 12
using namespace std;
typedef struct { int h, w, r; } block;
block q[QUEUESIZE];
int map[15][12], drop[4];
int N, W, H, begin, end, ans;

bool empty(void) { return begin == end; }
void push(block b) { q[end++] = b; }
block pop(void) { return q[begin++]; }

// DFS
void go(int n) {
	if (n == N) {
		int cpy[15][12], cnt = 0;
		// 맵 카피
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				cpy[h][w] = map[h][w];

		for (int i = 0; i < N; i++) {
			begin = end = 0;
			// 구슬 낙하 지점 탐색
			for (int h = 0; h < H; h++) {
				if (cpy[h][drop[i]] > 0) {
					push({ h, drop[i], cpy[h][drop[i]] });
					break;
				}
			}
			// BFS
			// 폭발
			while (!empty()) {
				block b = pop();
				cpy[b.h][b.w] = 0;
				for (int range = 1; range < b.r; range++) {
					// 상하좌우 폭발 시 해당 블록 값을 0으로 변경하는 이유:
					// 연쇄폭발로 이미 큐에 넣은 블록이 다음 연쇄폭발 때 또다시 들어갈 수 있기 때문에
					// 상
					if (b.h - range >= 0 && cpy[b.h - range][b.w] > 0) {
						push({ b.h - range, b.w, cpy[b.h - range][b.w] });
						cpy[b.h - range][b.w] = 0;
					}
					// 하
					if (b.h + range < H && cpy[b.h + range][b.w] > 0) {
						push({ b.h + range, b.w, cpy[b.h + range][b.w] });
						cpy[b.h + range][b.w] = 0;
					}
					// 좌
					if (b.w - range >= 0 && cpy[b.h][b.w - range] > 0) {
						push({ b.h, b.w - range, cpy[b.h][b.w - range] });
						cpy[b.h][b.w - range] = 0;
					}
					// 우
					if (b.w + range < W && cpy[b.h][b.w + range] > 0) {
						push({ b.h, b.w + range, cpy[b.h][b.w + range] });
						cpy[b.h][b.w + range] = 0;
					}
					// 시간 초과
					//int nh[4] = { b.h - range, b.h + range, b.h, b.h };
					//int nw[4] = { b.w, b.w, b.w - range, b.w + range };
					//for (int i = 0; i < 4; i++) {
					//	if (0 <= nh[i] && nh[i] < H && 0 <= nw[i] && nw[i] < W)
					//		if (cpy[nh[i]][nw[i]] > 0) {
					//			push({ nh[i], nw[i], cpy[nh[i]][nw[i]] });
					//			cpy[nh[i]][nw[i]] = 0;
					//		}
					//}
				}
			}
			// 벽돌 낙하
			for (int w = 0; w < W; w++)
				for (int h = H - 1; h > 0; h--)
					if (cpy[h][w] == 0)
						for (int hh = h - 1; hh >= 0; hh--)
							if (cpy[hh][w] > 0) {
								cpy[h][w] = cpy[hh][w];
								cpy[hh][w] = 0;
								break;
							}
		}
		// 남은 벽돌 세기
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				if (cpy[h][w] > 0)
					cnt++;
		if (ans > cnt)
			ans = cnt;
		return;
	}

	for (int i = 0; i < W; i++) {
		drop[n] = i;
		go(n + 1);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {

		// 입력부
		scanf("%d %d %d", &N, &W, &H);
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				scanf("%d", &map[h][w]);

		// 처리부
		ans = 2e9;
		go(0);

		// 출력부
		printf("#%d %d\n", t, ans);
	}

	return 0;
}
