/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu&categoryId=AV5VwAr6APYDFAWu&categoryType=CODE
*/

#include <cstdio>
using namespace std;

bool visited[101];
int map[20][20];
int dxy[4][2] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };	// �ð�������� 12�ú��� ȸ��
int N, xs, ys, ans;

void go(int x, int y, int d, int n) {
	if (x == xs && y == ys) {
		// �� ���� ��ȸ �� ������������ ���ƿ� ���
		if (visited[map[x][y]]) {
			if (ans < n)
				ans = n;
			return;
		}

		// Ž�� ������ ��� ���� ����Ʈ�� ������ �ϴ��� ����Ʈ�� ���ٸ� Ž������ ����
		if (map[x + 1][y + 1] == map[x][y])
			return;

		// ������������ Ž���� �׻� ������ �ϴ����� ����
		visited[map[x][y]] = true;
		go(x + 1, y + 1, d, n + 1);
		visited[map[x][y]] = false;
	}
	else {
		visited[map[x][y]] = true;
		// ���� ������ ���� ���� ����� �����ϰų� �ð���⿡ �°� ����
		for (int nd = d; nd <= d + 1; nd++) {
			int nx = x + dxy[nd][0], ny = y + dxy[nd][1];
			// nx�� ������������ ���� �Ѿ �� ����
			if (xs <= nx && nx < N && 0 <= ny && ny < N) {
				// ���� ���� ����Ʈ�̰ų� ���������� ��츸 ����
				if (!visited[map[nx][ny]] || (nx == xs && ny == ys))
					go(nx, ny, nd, n + 1);
			}
		}
		visited[map[x][y]] = false;
	}
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
		// �밢�� ��/��, �Ǵ� �ϴ����� �������� ���ϴ� ���������� �����ϰ� Ž��
		for (xs = 0; xs < N - 3; xs++)
			for (ys = 1; ys < N - 1; ys++)
				// ������������ Ž���� �׻� ������ �ϴ����� ����
				go(xs, ys, 0, 0);

		//��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}