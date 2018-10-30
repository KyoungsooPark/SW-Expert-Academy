/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&categoryId=AV5V61LqAf8DFAWu&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20], K[25];
int N, M;

int abs(int num) { return num < 0 ? -num : num; }

// 주어진 x, y에서 거리(|x - x1| + |y - y1|)가 k 미만인 마름모꼴 범위 검사
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
	// 집의 개수 리턴
	return sum;
}

int main(void) {
	// k 크기에 따른 운영 비용 미리 계산
	for (int k = 1; k < 25; k++)
		K[k] = k * k + (k - 1) * (k - 1);
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int ans = 0;
		
		// 입력부
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		// 처리부
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 1; k < 25; k++) {
					int temp = calculate(i, j, k);
					// 손해를 보지 않는 조건에서 더 많은 집에 서비스가 가능한 경우
					if (M * temp - K[k] >= 0 && temp > ans)
						ans = temp;
				}
			}
		}

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}