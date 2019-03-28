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
int dx[5] = { 0, -1, 0, 1, 0 };	// 이동 안함, 상, 우, 하, 좌
int dy[5] = { 0, 0, 1, 0, -1 };	// 이동 안함, 상, 우, 하, 좌
int M, A, ans;

bool valid(int x, int y) { return 1 <= x && x <= 10 && 1 <= y && y <= 10; }
int max(int a, int b) { return a > b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
int range(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
// map에 AP의 충전 범위를 AP 번호로 표시
void check(void) {
	for (int i = 0; i < A; i++) {
		BC ap = AP[i];
		for (int x = ap.X - ap.C; x <= ap.X + ap.C; x++) {
			for (int y = ap.Y - ap.C; y <= ap.Y + ap.C; y++) {
				if (valid(x, y) && range(x, y, ap.X, ap.Y) <= ap.C)
					map[x][y] |= (1 << i);	// AP 번호를 bit로 표시
			}
		}
	}
}

void charge(void) {
	int temp = 0;
	if (map[psn[PA].X][psn[PA].Y]) {	// 사용자 A가 충전 범위
		if (map[psn[PB].X][psn[PB].Y]) {	// 사용자 B도 충전 범위
			for (int i = 0; i < A; i++)	// 사용자 A의 충전 가능 AP 탐색
				if (map[psn[PA].X][psn[PA].Y] & (1 << i))
					for (int j = 0; j < A; j++)	// 사용자 B의 충전 가능 AP 탐색
						if (map[psn[PB].X][psn[PB].Y] & (1 << j)) {
							if (i == j)	// 사용자 A와 B가 같은 AP에 접속하는 경우
								temp = max(temp, AP[j].P);
							else	// 사용자 A와 B가 다른 AP에 접속하는 경우
								temp = max(temp, AP[i].P + AP[j].P);
						}
		}
		else {	// 사용자 A만 충전 범위
			for (int i = 0; i < A; i++)
				if (map[psn[PA].X][psn[PA].Y] & (1 << i))
					temp = max(temp, AP[i].P);
		}
	}
	else if (map[psn[PB].X][psn[PB].Y]) {	// 사용자 B만 충전 범위
		for (int i = 0; i < A; i++)	// 충전 가능 AP 탐색
			if (map[psn[PB].X][psn[PB].Y] & (1 << i))
				temp = max(temp, AP[i].P);
	}
	ans += temp;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d", &M, &A);
		// 사용자 이동 정보
		for (int p = PA; p <= PB; p++)
			for (int m = 1; m <= M; m++)
				scanf("%d", &moving[p][m]);
		// AP 정보
		for (int i = 0; i < A; i++)
			scanf("%d %d %d %d", &AP[i].Y, &AP[i].X, &AP[i].C, &AP[i].P);
		// 처리부
		check();
		ans = 0, psn[PA] = { 1, 1 }, psn[PB] = { 10, 10 };
		for (int m = 0; m <= M; m++) {
			psn[PA].X += dx[moving[PA][m]], psn[PA].Y += dy[moving[PA][m]];
			psn[PB].X += dx[moving[PB][m]], psn[PB].Y += dy[moving[PB][m]];
			charge();
		}
		// 출력부
		printf("#%d %d\n", t, ans);
		for (int x = 1; x <= 10; x++)
			for (int y = 1; y <= 10; y++)
				map[x][y] = 0;
	}
	return 0;
}