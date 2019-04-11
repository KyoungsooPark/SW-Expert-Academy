/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
*/

#include <cstdio>
#include <queue>
using namespace std;
enum { UP, DOWN, LEFT, RIGHT };
typedef struct { int x, y; } point;
typedef struct { int x, y, d, n; } ball;

point wormhole[5][2];
int map[102][102];
int dx[4] = { -1, 1, 0, 0 };	// ��, ��, ��, ��
int dy[4] = { 0, 0, -1, 1 };	// ��, ��, ��, ��
int bounce[6][4] = {
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
void move(ball &b) {
	while (true) {
		b.x += dx[b.d], b.y += dy[b.d];
		if (map[b.x][b.y] == 0)	// �� ������ ���
			continue;	// ��� ����
		if (map[b.x][b.y] <= 5)	// ��� ��ġ�� ��Ȧ (-1) �Ǵ� ��� (1 ~ 5) �� ���
			return;
		else if (map[b.x][b.y] > 5) {	// ��Ȧ�� ��� �ݴ��� ��Ȧ���� ��� ����
			int idx = map[b.x][b.y] - 6;
			if (b.x == wormhole[idx][0].x && b.y == wormhole[idx][0].y)
				b.x = wormhole[idx][1].x, b.y = wormhole[idx][1].y;
			else
				b.x = wormhole[idx][0].x, b.y = wormhole[idx][0].y;
		}
	}
}

void simulation(int x, int y) {
	queue<ball> q;
	for (int d = 0; d < 4; d++)
		q.push({ x, y, d, 0 });
	map[x][y] = -1;	// ��� ��ġ üũ
	while (!q.empty()) {
		ball b = q.front(); q.pop();
		move(b);	// ��� ��ġ�� ��Ȧ �Ǵ� ��ϱ��� �̵�
		switch (map[b.x][b.y]) {
		case -1: ans = max(ans, b.n); break;	// ��� ��ġ�� ��Ȧ�� ���
		case 1: case 2: case 3: case 4: case 5:	// ����� ���
			if (isopposite(b.d, bounce[map[b.x][b.y]][b.d]))	// ���� ������ ���� ����� �ݴ��� ���
				ans = max(ans, b.n * 2 + 1);	// ���ݱ����� ����(cnt)�� �ι�� ���� ��� ���� (+1)
			else	// �ݴ밡 �ƴϸ� ��� ����
				q.push({ b.x, b.y, bounce[map[b.x][b.y]][b.d], b.n + 1 });
		}
	}
	map[x][y] = 0;	// ��� ��ġ üũ ����
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
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (!map[i][j])
					simulation(i, j);
		// ��º�
		setbuf(stdout, NULL);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}