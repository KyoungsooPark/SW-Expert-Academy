/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

int board[12][12];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, num, ans;
// 주어진 core p에서 방향 d로의 전선 설치 가능 여부 검사
bool available(point p, int d) {
	int x = p.x + dx[d], y = p.y + dy[d];
	while (0 <= x && x < N && 0 <= y && y < N) {
		if (board[x][y])
			return false;
		x += dx[d], y += dy[d];
	}
	return true;
}
// 주어진 core p에서 방향 d로 전선 설치(value=1) 또는 해제(value=0)
int set(point p, int d, int value) {
	int ret = 0;
	int x = p.x + dx[d], y = p.y + dy[d];
	while (0 <= x && x < N && 0 <= y && y < N) {
		board[x][y] = value;
		ret++;
		x += dx[d], y += dy[d];
	}
	return ret;
}
// 모든 경우에 대한 전선 설치 방법 검사
void go(const vector<point> &core, int n, int cnt, int sum) {
	if (n == core.size()) {	// 현재의 전선 설치 방법에 대해 모든 core 검사가 끝난 경우
		if (num < cnt) {	// 전선이 설치된 core의 수가 현재까지의 최댓값보다 큰 경우
			num = cnt;	// 최댓값 갱신
			ans = sum;	// 전선 길이의 합 갱신
		}
		else if (num == cnt && ans > sum)	// 이전의 최댓값과 같으나 전선 길이의 합이 더 작은 경우
			ans = sum;	// 전선 길이의 합 갱신
		return;
	}
	for (int d = 0; d < 4; d++) {
		if (available(core[n], d)) {	// core[n]에 전선 설치가 가능한 경우
			int temp = set(core[n], d, 1);	// 전선 설치
			go(core, n + 1, cnt + 1, sum + temp);
			set(core[n], d, 0);	// 전선 해제
		}
	}
	go(core, n + 1, cnt, sum);	// core[n]에 전선을 설치하지 않음
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		vector<point> core;
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &board[i][j]);
				if (!board[i][j])
					continue;
				if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
					continue;
				core.push_back({ i, j });	// 가장자리를 제외한 위치의 core를 push
			}
		}
		ans = 2e9;
		num = 0;
		// 처리부
		go(core, 0, 0, 0);
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}