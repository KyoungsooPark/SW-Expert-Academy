#include <cstdio>
using namespace std;
int map[10][10];
int N, M, C;

// ���� ���� ���� ������ ä���� �� �ִ� ���� �ִ� �� �˻�
int search(int r, int c) {
	int square_sum = 0;
	for (int i = 1; i < (1 << M); i++) {
		int sum = 0, temp_square_sum = 0;
		for (int j = 0; j < M; j++) {
			if (i & (1 << j)) {
				sum += map[r][c + j];
				temp_square_sum += map[r][c + j] * map[r][c + j];
			}
		}
		if (sum <= C && square_sum < temp_square_sum)
			square_sum = temp_square_sum;
	}
	return square_sum;
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
		int ans = 0, A = 0, B = 0;
		for (int r1 = 0; r1 < N; r1++) {
			for (int c1 = 0; c1 <= N - M; c1++) {
				int square_sum = search(r1, c1);
				// �ϲ� A�� �� ���� ���� ä���� �� �ִ� ������ ������ ���
				if (A < square_sum) {
					A = square_sum;
					B = 0;
					// �ϲ� B�� ������ ���� Ž��
					for (int r2 = r1; r2 < N; r2++) {
						for (int c2 = 0; c2 <= N - M; c2++) {
							if (r2 == r1) {
								if (c2 < c1 + M || N - (c1 + M) < M)
									continue;
							}
							square_sum = search(r2, c2);
							if (B < square_sum)
								B = square_sum;
						}
					}
					if (ans < A + B)
						ans = A + B;
				}
			}
		}

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}