/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&categoryId=AV5V61LqAf8DFAWu&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20], K[25];
int N, M;

int abs(int num) { return num < 0 ? -num : num; }

// �־��� x, y���� �Ÿ�(|x - x1| + |y - y1|)�� k �̸��� ������� ���� �˻�
int calculate(int x, int y, int k) {
	int sum = 0;
	for (int i = x - k + 1; i <= x + k - 1; i++) {
		for (int j = y - k + 1; j <= y + k - 1; j++) {
			if (abs(x - i) + abs(y - j) < k) {
				if (0 <= i && i < N && 0 <= j && j < N) {
					if (map[i][j])
						sum += map[i][j];
				}
			}
		}
	}
	// ���� ���� ����
	return sum;
}

int main(void) {
	// k ũ�⿡ ���� � ��� �̸� ���
	for (int k = 1; k < 25; k++)
		K[k] = k * k + (k - 1) * (k - 1);
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int ans = 0;
		
		// �Էº�
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		// ó����
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 1; k < 25; k++) {
					int temp = calculate(i, j, k);
					// ���ظ� ���� �ʴ� ���ǿ��� �� ���� ���� ���񽺰� ������ ���
					if (M * temp - K[k] >= 0 && temp > ans)
						ans = temp;
				}
			}
		}

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}