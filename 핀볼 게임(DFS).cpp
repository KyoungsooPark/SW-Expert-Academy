/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
*/

#include <cstdio>
using namespace std;
enum { UP, DOWN, LEFT, RIGHT };
typedef struct { int x, y; } point;

point wormhole[5][2];
int map[102][102];
int dx[4] = { -1, 1, 0, 0 };	// 상, 하, 좌, 우
int dy[4] = { 0, 0, -1, 1 };	// 상, 하, 좌, 우
int bounce[6][4] = {	// 진출 방향[블록 번호][진입 방향]
	{ 0, 0, 0, 0 },
	{ DOWN, RIGHT, UP, LEFT },	// 1번 블록
	{ RIGHT, UP, DOWN, LEFT },	// 2번 블록
	{ LEFT, UP, RIGHT, DOWN },	// 3번 블록
	{ DOWN, LEFT, RIGHT, UP },	// 4번 블록
	{ DOWN, UP, RIGHT, LEFT }	// 5번 블록
};
int N, ans;

int max(int a, int b) { return a > b ? a : b; }
// 진입 방향(od : old direction)과 진출 방향(nd: new direction)이 서로 반대인지 검사
bool isopposite(int od, int nd) { return od % 2 ? nd == od - 1 : nd == od + 1; }
// 핀볼 이동
void move(int &x, int &y, int d) {
	while (true) {
		x += dx[d], y += dy[d];
		if (map[x][y] == 0)	// 빈 공간인 경우
			continue;	// 계속 진행
		if (map[x][y] <= 5)	// 출발 위치나 블랙홀 (-1) 또는 블록 (1 ~ 5) 인 경우
			return;
		else if (map[x][y] > 5) {	// 웜홀인 경우 반대편 웜홀에서 계속 진행
			int idx = map[x][y] - 6;
			if (x == wormhole[idx][0].x && y == wormhole[idx][0].y)
				x = wormhole[idx][1].x, y = wormhole[idx][1].y;
			else
				x = wormhole[idx][0].x, y = wormhole[idx][0].y;
		}
	}
}

void go(int x, int y, int d, int cnt) {
	move(x, y, d);	// 출발 위치나 블랙홀 또는 블록까지 이동
	switch (map[x][y]) {
	case -1: ans = max(ans, cnt); return;	// 출발 위치나 블랙홀인 경우
	case 1: case 2: case 3: case 4: case 5:	// 블록인 경우
		if (isopposite(d, bounce[map[x][y]][d])) {	// 진출 방향이 진입 방향과 반대인 경우
			ans = max(ans, cnt * 2 + 1);	// 지금까지의 점수(cnt)의 두배와 현재 블록 점수 (+1)
			return;
		}
		go(x, y, bounce[map[x][y]][d], cnt + 1);	// 반대가 아니면 계속 진행
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < 5; i++)
			wormhole[i][0].x = -1;	// 웜홀 초기화
		for (int i = 0; i <= N + 1; i++) {
			for (int j = 0; j <= N + 1; j++) {
				if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
					map[i][j] = 5;	// 맵의 테두리에 5번 블록 설치
				else {
					scanf("%d", &map[i][j]);
					if (map[i][j] > 5) {	// 웜홀인 경우
						int idx = map[i][j] - 6;
						if (wormhole[idx][0].x == -1)
							wormhole[idx][0] = { i, j };
						else
							wormhole[idx][1] = { i, j };
					}
				}
			}
		}
		// 처리부
		ans = 0;
		for (int x0 = 1; x0 <= N; x0++) {
			for (int y0 = 1; y0 <= N; y0++) {
				if (map[x0][y0] == 0) {
					map[x0][y0] = -1;	// 출발 위치 체크
					for (int d = 0; d < 4; d++)
						go(x0, y0, d, 0);
					map[x0][y0] = 0;	// 출발 위치 체크 해제
				}
			}
		}
		// 출력부
		setbuf(stdout, NULL);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}