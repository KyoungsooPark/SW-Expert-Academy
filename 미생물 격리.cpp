/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int n, max; } point;
typedef struct { int x, y, n, d; } microbe;

point map[100][100], next_map[100][100];
int dx[5] = { 0, -1, 1, 0, 0 };	// 1: ��, 2: ��, 3: ��, 4: ��
int dy[5] = { 0, 0, 0, -1, 1 };	// 1: ��, 2: ��, 3: ��, 4: ��
int N, M, K;

bool isedge(int x, int y) { return x == 0 || x == N - 1 || y == 0 || y == N - 1; }
// �̻��� ���� ���
int count(void) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (map[i][j].n)
				ret += map[i][j].n;
			map[i][j] = { 0, 0 };
		}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		queue<microbe> q;
		// �Էº�
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < K; i++) {
			int x, y, n, d;
			scanf("%d %d %d %d", &x, &y, &n, &d);
			q.push({ x, y, n, d });
			map[x][y] = { n, n };
		}
		// ó����
		while (M--) {
			int size = q.size();
			while (size--) {
				microbe m = q.front(); q.pop();
				if (m.n == map[m.x][m.y].max) {	// ���� ��ġ�� ���� �� �̻��� ���� ���� ���� ����
					if (m.n < map[m.x][m.y].n)	// �ٸ� ������ ���� ���
						m.n = map[m.x][m.y].n;	// ���� ��ħ

					m.x += dx[m.d], m.y += dy[m.d];	// �̵� ��ġ ���
					if (isedge(m.x, m.y)) {	// �̵� ��ġ�� �����ڸ�
						m.n >>= 1;	// �̻��� �� �ݰ�
						if (!m.n) continue;	// �̻����� ��� ����
						m.d % 2 ? m.d++ : m.d--;	// ���� ����
					}

					next_map[m.x][m.y].n += m.n;	// ���� ��ġ�� �̻��� �� ����
					if (m.n > next_map[m.x][m.y].max) {	// �ش� ��ġ�� �̵��� ���� �� �ִ� �̻��� �� ������Ʈ
						next_map[m.x][m.y].max = m.n;
						q.push(m);
					}
				}
			}
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					// �� ������Ʈ
					map[i][j] = next_map[i][j], next_map[i][j] = { 0, 0 };
		}
		// ��º�
		printf("#%d %d\n", t, count());
	}
	return 0;
}