/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV134DPqAA8CFAYh&categoryId=AV134DPqAA8CFAYh&categoryType=CODE&&&#none
*/

#include <cstdio>
using namespace std;

int map[1000];

int max(int a, int b) { return a >= b ? a : b; }

int main(void) {
	for (int t = 1; t <= 10; t++) {
		int N, ans = 0;
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &map[i]);
		// 처리부
		for (int i = 2; i < N - 2; i++) {
			// 거리 2 이하 주변 최고층 빌딩과의 높이 차 계산
			int temp = map[i] - max(max(map[i - 2], map[i - 1]), max(map[i + 1], map[i + 2]));
			if (temp > 0)	// 주변 빌딩보다 더 높은 경우
				ans += temp;	// 높은 층 만큼의 세대 수 합산
		}
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}