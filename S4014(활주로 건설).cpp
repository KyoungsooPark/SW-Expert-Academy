/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20];
int N, X, ans;
// �� �˻�
// flag: ���� ��ġ�� ������ ���� ��ġ ����
void row(int x, int y, int flag) {
	if (y == N - 1) {	// Ȱ�ַ� ���� ����
		ans++;
		return;
	}
	if (y + X < N && map[x][y + X] == map[x][y] + 1) {	// ������ ���� ��ġ �˻�
		if (flag)	return;	// ���� ��ġ�� ������ ���ΰ� ��ġ�Ǿ� ������ ���� ��ġ �Ұ�
		for (int yy = y + 1; yy < y + X; yy++)
			if (map[x][yy] != map[x][y])	return;	// ���� ��ġ ������ ��ź���� ���� ���
		row(x, y + X, false);
	}
	else if (map[x][y + 1] == map[x][y])	// ���� �˻�
		row(x, y + 1, false);
	else if (y + X < N && map[x][y + X] == map[x][y] - 1) {	// ������ ���� ��ġ �˻�
		for (int yy = y + 1; yy < y + X; yy++)
			if (map[x][yy] != map[x][y + X])	return;	// ���� ��ġ ������ ��ź���� ���� ���
		row(x, y + X, true);
	}
}
// �� �˻�
// flag: ���� ��ġ�� ������ ���� ��ġ ����
void col(int x, int y, int flag) {
	if (x == N - 1) {	// Ȱ�ַ� ���� ����
		ans++;
		return;
	}
	if (x + X < N && map[x + X][y] == map[x][y] + 1) {	// ������ ���� ��ġ �˻�
		if (flag)	return;	// ���� ��ġ�� ������ ���ΰ� ��ġ�Ǿ� ������ ���� ��ġ �Ұ�
		for (int xx = x + 1; xx < x + X; xx++)
			if (map[xx][y] != map[x][y])	return;	// ���� ��ġ ������ ��ź���� ���� ���
		col(x + X, y, false);
	}
	else if (map[x + 1][y] == map[x][y])	// ���� �˻�
		col(x + 1, y, false);
	else if (x + X < N && map[x + X][y] == map[x][y] - 1) {	// ������ ���� ��ġ �˻�
		for (int xx = x + 1; xx < x + X; xx++)
			if (map[xx][y] != map[x + X][y])	return;	// ���� ��ġ ������ ��ź���� ���� ���
		col(x + X, y, true);
	}
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
		for (int i = 0; i < N; i++) {
			row(i, 0, false);
			col(0, i, false);
		}
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}