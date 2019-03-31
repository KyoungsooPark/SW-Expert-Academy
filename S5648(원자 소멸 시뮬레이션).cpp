/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <queue>
using namespace std;
typedef struct { int x, y, d, k; } atom;

queue<atom> q;
int map[4001][4001];	// -1000 ~ 1000 => 0 ~ 2000 => 0 ~ 4000 (0.5�� ����)
int dx[4] = { -1, 1, 0, 0 };	// ��, ��, ��, ��
int dy[4] = { 0, 0, -1, 1 };	// ��, ��, ��, ��
int N, ans;

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int x, y, d, k;
			scanf("%d %d %d %d", &y, &x, &d, &k);
			x = 2000 - 2 * x, y = 2000 + 2 * y;
			q.push({ x, y, d, k });
			map[x][y] = k;	// �ʱ� ���� ��ġ�� ������ ũ�� ǥ��
		}
		// ó����
		ans = 0;
		while (!q.empty()) {
			atom now = q.front(); q.pop();
			if (map[now.x][now.y] > now.k) {	// ���� ��ġ�� ���� ���� ���� ����
				ans += map[now.x][now.y];	// ����. ���� ������ �ջ�
				map[now.x][now.y] = 0;	// �ش� ��ġ�� ������ ��� ����
			}
			else if (map[now.x][now.y] == now.k) {	// ���� ��ġ�� �ϳ��� ���ڸ� ����
				map[now.x][now.y] = 0;	// ���� �̵��� ���� ���� ��ġ�� ������ �ʱ�ȭ
				now.x += dx[now.d], now.y += dy[now.d];	// ���� �̵�
				if (0 <= now.x && now.x <= 4000 && 0 <= now.y && now.y <= 4000) {
					map[now.x][now.y] += now.k;	// �̵��� ��ġ�� ������ ����
					q.push(now);
				}
			}
		}
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}