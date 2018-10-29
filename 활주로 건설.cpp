/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20];
int N, X, ans;

int row(int x, int y, bool flag) {
	if (y == N - 1)
		return 1;

	// ������
	// �������� ���� ���̸�ŭ �������� �˻��ؾ� �ϹǷ� ���� ���� ����
	if (y + X < N && map[x][y] - map[x][y + X] == -1) {
		// ���� ��ġ�� ������ ���ΰ� ������ �ִ� ���
		if (flag)
			return 0;
		for (int i = y + 1; i < y + X; i++)
			// ���θ� ���� �� ���� ���
			if (map[x][y] != map[x][i])
				return 0;
		return row(x, y + X, false);
	}
	// ����
	else if (map[x][y] == map[x][y + 1])
		return row(x, y + 1, false);

	// ������
	else if (y + X < N && map[x][y] - map[x][y + X] == 1) {
		for (int i = y + 1; i < y + X; i++)
			// ���θ� ���� �� ���� ���
			if (map[x][y + X] != map[x][i])
				return 0;
		return row(x, y + X, true);
	}
	return 0;
}

int col(int x, int y, bool flag) {
	if (x == N - 1)
		return 1;

	// ������
	// �������� ���� ���̸�ŭ �������� �˻��ؾ� �ϹǷ� ���� ���� ����
	if (x + X < N && map[x][y] - map[x + X][y] == -1) {
		// ���� ��ġ�� ������ ���ΰ� ������ �ִ� ���
		if (flag)
			return 0;
		for (int i = x + 1; i < x + X; i++)
			// ���θ� ���� �� ���� ���
			if (map[x][y] != map[i][y])
				return 0;
		return col(x + X, y, false);
	}

	else if (map[x][y] == map[x + 1][y])
		return col(x + 1, y, false);

	// ������
	else if (x + X < N && map[x][y] - map[x + X][y] == 1) {
		for (int i = x + 1; i < x + X; i++)
			// ���θ� ���� �� ���� ���
			if (map[x + X][y] != map[i][y])
				return 0;
		return col(x + X, y, true);
	}
	return 0;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d %d", &N, &X);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		// ó����
		ans = 0;
		for (int r = 0; r < N; r++)
			ans += row(r, 0, false);
		for (int c = 0; c < N; c++)
			ans += col(0, c, false);

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}