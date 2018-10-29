/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&categoryId=AWXRQm6qfL0DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int h, w, r; } block;
int map[15][12], drop[4];
int N, W, H, begin, end, ans;

// DFS
void go(int n) {
	if (n == N) {
		int cpy[15][12], cnt = 0;
		queue<block> q;
		// �� ī��
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				cpy[h][w] = map[h][w];

		for (int i = 0; i < N; i++) {
			// ���� ���� ���� Ž��
			for (int h = 0; h < H; h++) {
				if (cpy[h][drop[i]] > 0) {
					q.push({ h, drop[i], cpy[h][drop[i]] });
					break;
				}
			}
			// BFS
			// ����
			while (!q.empty()) {
				block b = q.front();
				q.pop();
				// ����
				cpy[b.h][b.w] = 0;
				for (int range = 1; range < b.r; range++) {
					// �����¿� ���� �� �ش� ��� ���� 0���� �����ϴ� ����:
					// �������߷� �̹� ť�� ���� ����� ���� �������� �� �Ǵٽ� �� �� �ֱ� ������
					// ��
					if (b.h - range >= 0 && cpy[b.h - range][b.w] > 0) {
						q.push({ b.h - range, b.w, cpy[b.h - range][b.w] });
						cpy[b.h - range][b.w] = 0;
					}
					// ��
					if (b.h + range < H && cpy[b.h + range][b.w] > 0) {
						q.push({ b.h + range, b.w, cpy[b.h + range][b.w] });
						cpy[b.h + range][b.w] = 0;
					}
					// ��
					if (b.w - range >= 0 && cpy[b.h][b.w - range] > 0) {
						q.push({ b.h, b.w - range, cpy[b.h][b.w - range] });
						cpy[b.h][b.w - range] = 0;
					}
					// ��
					if (b.w + range < W && cpy[b.h][b.w + range] > 0) {
						q.push({ b.h, b.w + range, cpy[b.h][b.w + range] });
						cpy[b.h][b.w + range] = 0;
					}
					// �ð� �ʰ�
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
			// ���� ����
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
		// ���� ���� ����
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				if (cpy[h][w] > 0)
					cnt++;
		if (ans > cnt)
			ans = cnt;
		return;
	}

	for (int w = 0; w < W; w++) {
		drop[n] = w;
		go(n + 1);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {

		// �Էº�
		scanf("%d %d %d", &N, &W, &H);
		for (int h = 0; h < H; h++)
			for (int w = 0; w < W; w++)
				scanf("%d", &map[h][w]);

		// ó����
		ans = 2e9;
		go(0);

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}