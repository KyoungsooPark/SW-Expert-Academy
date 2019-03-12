/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, r; } block;
int map[15][12], cpy[15][12], drop_cols[4];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, W, H, ans;
// ���� ����
void drop(void) {
	for (int w = 0; w < W; w++) {
		for (int h = H - 1; h > 0; h--) {
			if (!cpy[h][w]) {
				for (int hh = h - 1; hh >= 0; hh--) {
					if (cpy[hh][w]) {
						cpy[h--][w] = cpy[hh][w];
						cpy[hh][w] = 0;
					}
				}
				break;
			}
		}
	}
}
// �ϼ��� drop_cols�� �̿��Ͽ� �ùķ��̼�
int simulation(void) {
	queue<block> q;
	int ret = 0;
	// �� ī��
	for (int h = 0; h < H; h++)
		for (int w = 0; w < W; w++)
			cpy[h][w] = map[h][w];

	// Nȸ ���� ����
	for (int i = 0; i < N; i++) {
		int w = drop_cols[i];	// ���� ���� ��
		for (int h = 0; h < H; h++) {	// ������ ������ ���� ��ġ Ž��
			if (cpy[h][w]) {
				q.push({ h, w, cpy[h][w] });
				cpy[h][w] = 0;
				break;
			}
		}
		while (!q.empty()) {
			block b = q.front(); q.pop();
			for (int r = 1; r < b.r; r++) {
				for (int d = 0; d < 4; d++) {
					int nx = b.x + dx[d] * r, ny = b.y + dy[d] * r;
					if (0 <= nx && nx < H && 0 <= ny && ny < W && cpy[nx][ny]) {
						q.push({ nx, ny, cpy[nx][ny] });
						cpy[nx][ny] = 0;
					}
				}
			}
		}
		drop();
	}

	// ���� ���� ���� ��ȯ
	for (int h = 0; h < H; h++)
		for (int w = 0; w < W; w++)
			if (cpy[h][w])
				ret++;
	return ret;
}

void go(int n) {
	if (n == N) {	// ���� �ϼ�
		ans = min(ans, simulation());
		return;
	}
	for (int w = 0; w < W; w++) {
		drop_cols[n] = w;
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