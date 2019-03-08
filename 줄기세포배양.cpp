/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef struct { int x, y, t; } cell;

// K가 최대값(300)이고 증식 속도가 가장 빠른 세포(생명력 = 1)의 경우 각 방향마다
// 최대 150칸(300 / 2) 만큼 증식. 따라서, 150 + N, M 최대값 50 + 150 = 350
int map[350][350];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, M, K;
// 세포 증식
void proliferate(queue<cell> q[], cell p) {
	for (int d = 0; d < 4; d++) {
		int nx = p.x + dx[d], ny = p.y + dy[d];
		if (!map[nx][ny]) {	// 다른 세포가 존재하지 않는 경우
			map[nx][ny] = p.t;	// 경과 시간이 생명력과 같을 때, 동일한 생명력의 세포 증식
			q[p.t].push({ nx, ny, p.t * 2 });	// 새롭게 증식된 세포 큐에 삽입
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		queue<cell> q[11];
		int ans = 0;

		// 입력부
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 150; i < N + 150; i++) {
			for (int j = 150; j < M + 150; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j])
					q[map[i][j]].push({ i, j, map[i][j] * 2 });
			}
		}
		// 처리부
		while (K--) {
			for (int life = 10; life > 0; life--) {	// 생명력 수치가 높은 세포 우선
				int size = q[life].size();
				while (size--) {	// 새롭게 증식되는 세포를 제외하고 수행
					cell now = q[life].front(); q[life].pop();
					if (now.t == life)	// 현재까지의 경과 시간이 세포의 생명력과 동일한 경우
						proliferate(q, now);	// 증식
					if (--now.t)	// 시간 경과 후 아직 살아있으면
						q[life].push(now);	// 큐에 삽입
				}
			}
		}
		//출력부
		for (int life = 10; life > 0; life--)
			ans += q[life].size();		// 현재까지 살아있는 (큐에 존재하는) 세포 수 합산
		printf("#%d %d\n", t, ans);
		memset(map, 0, sizeof(map));	// 다음 테스트를 위한 초기화
	}
	return 0;
}