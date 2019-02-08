#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef struct { int x, y; } point;
bool map[256][1000];

bool check(point p) {
	return !map[p.x][p.y - 2] && !map[p.x][p.y - 1] && !map[p.x][p.y + 1] && !map[p.x][p.y + 2];
}

int main(void) {
	for (int t = 1; t <= 10; t++) {
		int N, ans = 0;
		queue<point> q;
		scanf("%d", &N);
		for (int w = 0; w < N; w++) {
			int h;
			scanf("%d", &h);
			if (h) {
				q.push({ h, w });
				for (int i = 0; i <= h; i++)
					map[i][w] = true;
			}
		}

		while (!q.empty()) {
			point now = q.front(); q.pop();
			if (check(now)) {
				ans++;
				if (now.x > 1)
					q.push({ now.x - 1, now.y });
			}
		}

		printf("#%d %d\n", t, ans);
		memset(map, false, sizeof(map));
	}
	return 0;
}