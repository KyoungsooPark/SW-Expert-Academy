/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo&categoryId=AWXRDL1aeugDFAUo&categoryType=CODE&&&
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef struct { int x, y; } person;
int a[101], b[101], map[11][11], power[8];
int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

void init(int x, int y, int c, int ap) {
	for (int i = x - c; i <= x + c; i++) {
		for (int j = y - c; j <= y + c; j++) {
			if (1 <= i && i <= 10 && 1 <= j && j <= 10) {
				if (abs(i - x) + abs(j - y) <= c)
					map[i][j] |= (1 << ap);
			}
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		person A = { 1, 1 }, B = { 10, 10 };	// A, B�� �ʱ� ��ġ ����
		int M, AP, ans = 0;
		a[0] = b[0] = 0;	// A, B�� �ʱ� ��ġ���� ���� ���� ���θ� �˻��ϱ� ����
		memset(map, 0, sizeof(map));

		// �Էº�
		scanf("%d %d", &M, &AP);
		for (int m = 1; m <= M; m++)
			scanf("%d", &a[m]);
		for (int m = 1; m <= M; m++)
			scanf("%d", &b[m]);
		for (int ap = 0; ap < AP; ap++) {
			int x, y, c;
			scanf("%d %d %d %d", &y, &x, &c, &power[ap]);
			init(x, y, c, ap);
		}

		// ó����
		for (int m = 0; m <= M; m++) {
			int temp = 0;
			// A, B�� ��ġ �̵�
			A.x += dx[a[m]], A.y += dy[a[m]];
			B.x += dx[b[m]], B.y += dy[b[m]];

			if (map[A.x][A.y] > 0) {
				// A, B ��� ���� ���� ����
				if (map[B.x][B.y] > 0) {
					int cmp;
					for (int i = 0; i < AP; i++) {
						for (int j = 0; j < AP; j++) {
							if (map[A.x][A.y] & (1 << i) && map[B.x][B.y] & (1 << j)) {
								if (i == j)
									cmp = power[i];
								else
									cmp = power[i] + power[j];
								if (temp < cmp)
									temp = cmp;
							}
						}
					}
				}
				// A�� ���� ���� ����
				else {
					for (int i = 0; i < AP; i++) {
						if (map[A.x][A.y] & (1 << i)) {
							if (temp < power[i])
								temp = power[i];
						}
					}
				}
			}
			// B�� ���� ���� ����
			else if (map[B.x][B.y] > 0) {
				for (int i = 0; i < AP; i++) {
					if (map[B.x][B.y] & (1 << i)) {
						if (temp < power[i])
							temp = power[i];
					}
				}
			}
			ans += temp;
		}

		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}