#include <cstdio>
using namespace std;

int arr[10][10];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

// ������ �迭 ����
void snail_array(int N) {
	int x = 0, y = -1, cnt, d = 0, n = 1;
	cnt = 2 * N - 1;
	while (cnt--) {
		for (int i = 0; i < N; i++) {
			x += dx[d], y += dy[d];
			arr[x][y] = n++;
		}
		d == 3 ? d = 0 : d++;
		if (d % 2)
			N--;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		// �Էº�
		scanf("%d", &N);
		// ó����
		snail_array(N);
		// ��º�
		printf("#%d\n", t);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%d ", arr[i][j]);
			printf("\n");
		}
	}
	return 0;
}