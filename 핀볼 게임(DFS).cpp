/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
*/

#include <cstdio>
using namespace std;
enum { UP, DOWN, LEFT, RIGHT };
typedef struct { int x, y; } point;

point wormhole[5][2];
int map[102][102];
int dx[4] = { -1, 1, 0, 0 };	// ��, ��, ��, ��
int dy[4] = { 0, 0, -1, 1 };	// ��, ��, ��, ��
int bounce[6][4] = {	// ���� ����[��� ��ȣ][���� ����]
	{ 0, 0, 0, 0 },
	{ DOWN, RIGHT, UP, LEFT },	// 1�� ���
	{ RIGHT, UP, DOWN, LEFT },	// 2�� ���
	{ LEFT, UP, RIGHT, DOWN },	// 3�� ���
	{ DOWN, LEFT, RIGHT, UP },	// 4�� ���
	{ DOWN, UP, RIGHT, LEFT }	// 5�� ���
};
int N, ans;

int max(int a, int b) { return a > b ? a : b; }
// ���� ����(od : old direction)�� ���� ����(nd: new direction)�� ���� �ݴ����� �˻�
bool isopposite(int od, int nd) { return od % 2 ? nd == od - 1 : nd == od + 1; }
// �ɺ� �̵�
void move(int &x, int &y, int d) {
	while (true) {
		x += dx[d], y += dy[d];
		if (map[x][y] == 0)	// �� ������ ���
			continue;	// ��� ����
		if (map[x][y] <= 5)	// ��� ��ġ�� ��Ȧ (-1) �Ǵ� ��� (1 ~ 5) �� ���
			return;
		else if (map[x][y] > 5) {	// ��Ȧ�� ��� �ݴ��� ��Ȧ���� ��� ����
			int idx = map[x][y] - 6;
			if (x == wormhole[idx][0].x && y == wormhole[idx][0].y)
				x = wormhole[idx][1].x, y = wormhole[idx][1].y;
			else
				x = wormhole[idx][0].x, y = wormhole[idx][0].y;
		}
	}
}

void go(int x, int y, int d, int cnt) {
	move(x, y, d);	// ��� ��ġ�� ��Ȧ �Ǵ� ��ϱ��� �̵�
	switch (map[x][y]) {
	case -1: ans = max(ans, cnt); return;	// ��� ��ġ�� ��Ȧ�� ���
	case 1: case 2: case 3: case 4: case 5:	// ����� ���
		if (isopposite(d, bounce[map[x][y]][d])) {	// ���� ������ ���� ����� �ݴ��� ���
			ans = max(ans, cnt * 2 + 1);	// ���ݱ����� ����(cnt)�� �ι�� ���� ��� ���� (+1)
			return;
		}
		go(x, y, bounce[map[x][y]][d], cnt + 1);	// �ݴ밡 �ƴϸ� ��� ����
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < 5; i++)
			wormhole[i][0].x = -1;	// ��Ȧ �ʱ�ȭ
		for (int i = 0; i <= N + 1; i++) {
			for (int j = 0; j <= N + 1; j++) {
				if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
					map[i][j] = 5;	// ���� �׵θ��� 5�� ��� ��ġ
				else {
					scanf("%d", &map[i][j]);
					if (map[i][j] > 5) {	// ��Ȧ�� ���
						int idx = map[i][j] - 6;
						if (wormhole[idx][0].x == -1)
							wormhole[idx][0] = { i, j };
						else
							wormhole[idx][1] = { i, j };
					}
				}
			}
		}
		// ó����
		ans = 0;
		for (int x0 = 1; x0 <= N; x0++) {
			for (int y0 = 1; y0 <= N; y0++) {
				if (map[x0][y0] == 0) {
					map[x0][y0] = -1;	// ��� ��ġ üũ
					for (int d = 0; d < 4; d++)
						go(x0, y0, d, 0);
					map[x0][y0] = 0;	// ��� ��ġ üũ ����
				}
			}
		}
		// ��º�
		setbuf(stdout, NULL);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}