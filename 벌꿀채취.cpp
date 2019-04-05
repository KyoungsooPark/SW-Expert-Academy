/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu
*/

#include <cstdio>
using namespace std;

int map[10][10];
int N, M, C, x1, y1, x2, y2, ans;

int max(int a, int b) { return a > b ? a : b; }
// �־��� ��������(x, y)���� M���� ���� �� ������ ���� �ִ밪 ���
int cal(int x, int y) {
	int ret = 0, temp1, temp2;
	for (int i = 1; i < (1 << M); i++) {
		temp1 = temp2 = 0;
		for (int j = 0; j < M; j++)
			if (i & (1 << j))
				temp1 += map[x][y + j], temp2 += map[x][y + j] * map[x][y + j];
		if (temp1 <= C)
			ret = max(ret, temp2);
	}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d %d %d", &N, &M, &C);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		// ó����
		ans = 0;
		for (x1 = 0; x1 < N; x1++)
			for (y1 = 0; y1 <= N - M; y1++)	// �ϲ�1�� ������
				for (x2 = x1; x2 < N; x2++)
					for (y2 = x1 == x2 ? y1 + M : 0; y2 <= N - M; y2++)	// �ϲ�2�� ������
						if (y2 <= N - M)
							ans = max(ans, cal(x1, y1) + cal(x2, y2));
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}