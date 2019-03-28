/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo
*/

#include <cstdio>
using namespace std;
typedef struct { int X, Y, C, P; } BC;
typedef struct { int X, Y; } person;
enum { PA, PB };

BC AP[8];
person psn[2];
int map[11][11], moving[2][101];
int dx[5] = { 0, -1, 0, 1, 0 };	// �̵� ����, ��, ��, ��, ��
int dy[5] = { 0, 0, 1, 0, -1 };	// �̵� ����, ��, ��, ��, ��
int M, A, ans;

bool valid(int x, int y) { return 1 <= x && x <= 10 && 1 <= y && y <= 10; }
int max(int a, int b) { return a > b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
int range(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
// map�� AP�� ���� ������ AP ��ȣ�� ǥ��
void check(void) {
	for (int i = 0; i < A; i++) {
		BC ap = AP[i];
		for (int x = ap.X - ap.C; x <= ap.X + ap.C; x++) {
			for (int y = ap.Y - ap.C; y <= ap.Y + ap.C; y++) {
				if (valid(x, y) && range(x, y, ap.X, ap.Y) <= ap.C)
					map[x][y] |= (1 << i);	// AP ��ȣ�� bit�� ǥ��
			}
		}
	}
}

void charge(void) {
	int temp = 0;
	if (map[psn[PA].X][psn[PA].Y]) {	// ����� A�� ���� ����
		if (map[psn[PB].X][psn[PB].Y]) {	// ����� B�� ���� ����
			for (int i = 0; i < A; i++)	// ����� A�� ���� ���� AP Ž��
				if (map[psn[PA].X][psn[PA].Y] & (1 << i))
					for (int j = 0; j < A; j++)	// ����� B�� ���� ���� AP Ž��
						if (map[psn[PB].X][psn[PB].Y] & (1 << j)) {
							if (i == j)	// ����� A�� B�� ���� AP�� �����ϴ� ���
								temp = max(temp, AP[j].P);
							else	// ����� A�� B�� �ٸ� AP�� �����ϴ� ���
								temp = max(temp, AP[i].P + AP[j].P);
						}
		}
		else {	// ����� A�� ���� ����
			for (int i = 0; i < A; i++)
				if (map[psn[PA].X][psn[PA].Y] & (1 << i))
					temp = max(temp, AP[i].P);
		}
	}
	else if (map[psn[PB].X][psn[PB].Y]) {	// ����� B�� ���� ����
		for (int i = 0; i < A; i++)	// ���� ���� AP Ž��
			if (map[psn[PB].X][psn[PB].Y] & (1 << i))
				temp = max(temp, AP[i].P);
	}
	ans += temp;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d %d", &M, &A);
		// ����� �̵� ����
		for (int p = PA; p <= PB; p++)
			for (int m = 1; m <= M; m++)
				scanf("%d", &moving[p][m]);
		// AP ����
		for (int i = 0; i < A; i++)
			scanf("%d %d %d %d", &AP[i].Y, &AP[i].X, &AP[i].C, &AP[i].P);
		// ó����
		check();
		ans = 0, psn[PA] = { 1, 1 }, psn[PB] = { 10, 10 };
		for (int m = 0; m <= M; m++) {
			psn[PA].X += dx[moving[PA][m]], psn[PA].Y += dy[moving[PA][m]];
			psn[PB].X += dx[moving[PB][m]], psn[PB].Y += dy[moving[PB][m]];
			charge();
		}
		// ��º�
		printf("#%d %d\n", t, ans);
		for (int x = 1; x <= 10; x++)
			for (int y = 1; y <= 10; y++)
				map[x][y] = 0;
	}
	return 0;
}