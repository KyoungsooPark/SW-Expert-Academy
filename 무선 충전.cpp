/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo&categoryId=AWXRDL1aeugDFAUo&categoryType=CODE&&&
*/

#include <cstdio>
using namespace std;
typedef struct { int x, y; } person;
int map[11][11], move[2][101], p[8];
int dx[5] = { 0, -1, 0, 1, 0 };	// 이동하지 않음, 상, 우, 하, 좌
int dy[5] = { 0, 0, 1, 0, -1 };	// 이동하지 않음, 상, 우, 하, 좌

int abs(int num) { return num >= 0 ? num : -num; }
int max(int a, int b) { return a >= b ? a : b; }

// map 초기화
void reset(void) {
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
			map[i][j] = 0;
}

// map에 ap 번째 AP의 위치(x, y)로부터 충전 범위(c)를 bit로 표시
void set(int x_a, int y_a, int c, int ap) {
	for (int x_b = x_a - c; x_b <= x_a + c; x_b++) {
		for (int y_b = y_a - c; y_b <= y_a + c; y_b++) {
			// map에서 벗어나지 않는 범위 내에서
			if (1 <= x_b && x_b <= 10 && 1 <= y_b && y_b <= 10) {
				// 해당 위치가 충전 범위 c 내에 든다면
				if (abs(x_a - x_b) + abs(y_a - y_b) <= c)
					// bit로 표기 (서로 다른 AP간 충전 범위가 중첩될 수 있으므로)
					map[x_b][y_b] |= (1 << ap);
			}
		}
	}
}

// 한 사람만 충전 범위 내인 경우, 최대 충전량 리턴
int max_p(int num, int nAP) {
	int ret = 0;
	for (int i = 0; i < nAP; i++)
		if (num & (1 << i))
			ret = max(ret, p[i]);
	return ret;
}

// A, B 모두 충전 범위 내인 경우, 충전량 합의 최대값 리턴
int max_sum(int a, int b, int nAP) {

	int ret = 0;
	for (int i = 0; i < nAP; i++) {
		if (a & (1 << i)) {
			for (int j = 0; j < nAP; j++) {
				if (b & (1 << j)) {
					if (i == j)
						ret = max(ret, p[i]);
					else
						ret = max(ret, p[i] + p[j]);
				}
			}
		}
	}
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		person A = { 1, 1 }, B = { 10, 10 };	// A, B의 초기 위치 설정
		int M, AP, sum = 0;

		// 입력부
		scanf("%d %d", &M, &AP);
		for (int i = 0; i < 2; i++)	// A, B의 이동 경로 입력
			for (int m = 1; m <= M; m++)	// move[i][0]은 이동하지 않았을 때의 상태 검사를 위해
				scanf("%d", &move[i][m]);
		for (int ap = 0; ap < AP; ap++) {	// AP의 위치, 충전 범위, 충전 성능 입력
			int x, y, c;
			scanf("%d %d %d %d", &y, &x, &c, &p[ap]);
			set(x, y, c, ap);	// map에 ap 번째 AP의 충전 범위를 표시
		}

		// 처리부
		for (int m = 0; m <= M; m++) {
			// A, B의 위치 이동
			A.x += dx[move[0][m]], A.y += dy[move[0][m]];
			B.x += dx[move[1][m]], B.y += dy[move[1][m]];

			if (map[A.x][A.y] > 0) {
				// A, B 모두 무선 충전 범위
				if (map[B.x][B.y] > 0)
					sum += max_sum(map[A.x][A.y], map[B.x][B.y], AP);

				// A만 무선 충전 범위
				else
					sum += max_p(map[A.x][A.y], AP);
			}
			// B만 무선 충전 범위
			else if (map[B.x][B.y] > 0)
				sum += max_p(map[B.x][B.y], AP);
		}

		// 출력부
		printf("#%d %d\n", t, sum);
		reset();
	}
	return 0;
}
