/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef struct { int x, y, t; } cell;

// K�� �ִ밪(300)�̰� ���� �ӵ��� ���� ���� ����(����� = 1)�� ��� �� ���⸶��
// �ִ� 150ĭ(300 / 2) ��ŭ ����. ����, 150 + N, M �ִ밪 50 + 150 = 350
int map[350][350];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, K;
// ���� ����
void proliferate(queue<cell> q[], cell p) {
	for (int d = 0; d < 4; d++) {
		int nx = p.x + dx[d], ny = p.y + dy[d];
		if (!map[nx][ny]) {	// �ٸ� ������ �������� �ʴ� ���
			map[nx][ny] = p.t;	// ��� �ð��� ����°� ���� ��, ������ ������� ���� ����
			q[p.t].push({ nx, ny, p.t * 2 });	// ���Ӱ� ���ĵ� ���� ť�� ����
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		queue<cell> q[11];
		int ans = 0;

		// �Էº�
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 150; i < N + 150; i++) {
			for (int j = 150; j < M + 150; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j])
					q[map[i][j]].push({ i, j, map[i][j] * 2 });
			}
		}
		// ó����
		while (K--) {
			for (int life = 10; life > 0; life--) {	// ����� ��ġ�� ���� ���� �켱
				int size = q[life].size();
				while (size--) {	// ���Ӱ� ���ĵǴ� ������ �����ϰ� ����
					cell now = q[life].front(); q[life].pop();
					if (now.t == life)	// ��������� ��� �ð��� ������ ����°� ������ ���
						proliferate(q, now);	// ����
					if (--now.t)	// �ð� ��� �� ���� ���������
						q[life].push(now);	// ť�� ����
				}
			}
		}
		//��º�
		for (int life = 10; life > 0; life--)
			ans += q[life].size();		// ������� ����ִ� (ť�� �����ϴ�) ���� �� �ջ�
		printf("#%d %d\n", t, ans);
		memset(map, 0, sizeof(map));	// ���� �׽�Ʈ�� ���� �ʱ�ȭ
	}
	return 0;
}