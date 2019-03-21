/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu
*/

#include <cstdio>
using namespace std;

bool check[101];
int map[20][20];
int dx[4] = { 1, 1, -1, -1 };	// �ð����
int dy[4] = { 1, -1, -1, 1 };	// �ð����
int N, x0, y0, ans;

int max(int a, int b) { return a >= b ? a : b; }

void go(int x, int y, int d, int n) {
	if (x == x0 && y == y0) {	// ������
		if (check[map[x][y]]) {	// �� ���� ���ƿ� ���
			ans = max(ans, n);
			return;
		}
		// �������� ���� ���� ����Ʈ�� ���� ��� �������� ����
		if (map[x][y] == map[x + 1][y + 1])	return;

		check[map[x][y]] = true;
		go(x + 1, y + 1, d, n + 1);	// ������������ ������ �Ʒ��� ����
		check[map[x][y]] = false;
		return;
	}

	check[map[x][y]] = true;
	// d = 3�� ��츦 �����ϰ� ���Ϲ��� ���� Ȥ�� �ð���� ȸ��
	// d = 3�� ���� ���Ϲ��⸸ ����
	for (int nd = d; nd <= d + 1 && nd < 4; nd++) {
		int nx = x + dx[nd], ny = y + dy[nd];
		// ���������� ���� �ö��� ����
		if (x0 <= nx && nx < N && 0 <= ny && ny < N)
			// ���� ���� ����Ʈ�ų� �������� ���
			if (!check[map[nx][ny]] || (nx == x0 && ny == y0))
				go(nx, ny, nd, n + 1);
	}
	check[map[x][y]] = false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		// ó����
		ans = -1;
		for (x0 = 0; x0 < N - 2; x0++)
			for (y0 = 1; y0 < N - 1; y0++)
				go(x0, y0, 0, 0);
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}