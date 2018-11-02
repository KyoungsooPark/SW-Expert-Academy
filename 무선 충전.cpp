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

// map에 ap 번째 AP의 위치(x, y)로부터 충전 범위(c)를 bit로 표시
void init(int x, int y, int c, int ap) {
	for (int i = x - c; i <= x + c; i++) {
		for (int j = y - c; j <= y + c; j++) {
			// map에서 벗어나지 않는 범위 내에서
			if (1 <= i && i <= 10 && 1 <= j && j <= 10) {
				// 해당 위치가 충전 범위 c 내에 든다면
				if (abs(i - x) + abs(j - y) <= c)
					// bit로 표기 (서로 다른 AP간 충전 범위가 중첩될 수 있으므로)
					map[i][j] |= (1 << ap);
			}
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		person A = { 1, 1 }, B = { 10, 10 };	// A, B의 초기 위치 설정
		int M, AP, ans = 0;
		a[0] = b[0] = 0;	// A, B의 초기 위치부터 충전 가능 여부를 검사하기 위해
		memset(map, 0, sizeof(map));

		// 입력부
		scanf("%d %d", &M, &AP);
		// A의 이동 경로
		for (int m = 1; m <= M; m++)
			scanf("%d", &a[m]);
		// B의 이동 경로
		for (int m = 1; m <= M; m++)
			scanf("%d", &b[m]);
		// AP의 위치, 충전 범위, 충전 성능 입력
		for (int ap = 0; ap < AP; ap++) {
			int x, y, c;
			scanf("%d %d %d %d", &y, &x, &c, &power[ap]);
			// map에 ap 번째 AP의 충전 범위를 표시
			init(x, y, c, ap);
		}

		// 처리부
		for (int m = 0; m <= M; m++) {
			int temp = 0;
			// A, B의 위치 이동
			A.x += dx[a[m]], A.y += dy[a[m]];
			B.x += dx[b[m]], B.y += dy[b[m]];

			if (map[A.x][A.y] > 0) {
				// A, B 모두 무선 충전 범위
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
				// A만 무선 충전 범위
				else {
					for (int i = 0; i < AP; i++) {
						if (map[A.x][A.y] & (1 << i)) {
							if (temp < power[i])
								temp = power[i];
						}
					}
				}
			}
			// B만 무선 충전 범위
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

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
