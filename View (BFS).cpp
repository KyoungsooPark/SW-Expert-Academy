/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV134DPqAA8CFAYh&categoryId=AV134DPqAA8CFAYh&categoryType=CODE&&&#none
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;
bool map[256][1000];

// view 검사
bool check(point p) {
	return !map[p.x][p.y - 2] && !map[p.x][p.y - 1] && !map[p.x][p.y + 1] && !map[p.x][p.y + 2];
}

int main(void) {
	for (int t = 1; t <= 10; t++) {
		int N, ans = 0;
		queue<point> q;
		// 입력부
		scanf("%d", &N);
		for (int w = 0; w < N; w++) {
			int h;
			scanf("%d", &h);
			if (h) {
				q.push({ h, w });	// w열의 h층 push
				for (int i = 0; i <= h; i++)
					map[i][w] = true;
			}
		}
		// 처리부
		while (!q.empty()) {
			point now = q.front(); q.pop();
			if (check(now)) {	// 각 빌딩의 꼭대기 층부터 검사
				ans++;
				if (now.x > 1)
					q.push({ now.x - 1, now.y });
			}
		}
		// 출력부
		printf("#%d %d\n", t, ans);
		memset(map, false, sizeof(map));
	}
	return 0;
}
