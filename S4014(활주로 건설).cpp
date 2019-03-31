/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20];
int N, X, ans;
// 행 검사
// flag: 현재 위치의 내리막 경사로 설치 여부
void row(int x, int y, int flag) {
	if (y == N - 1) {	// 활주로 끝에 도달
		ans++;
		return;
	}
	if (y + X < N && map[x][y + X] == map[x][y] + 1) {	// 오르막 경사로 설치 검사
		if (flag)	return;	// 현재 위치에 내리막 경사로가 설치되어 오르막 경사로 설치 불가
		for (int yy = y + 1; yy < y + X; yy++)
			if (map[x][yy] != map[x][y])	return;	// 경사로 설치 지점이 평탄하지 않은 경우
		row(x, y + X, false);
	}
	else if (map[x][y + 1] == map[x][y])	// 평지 검사
		row(x, y + 1, false);
	else if (y + X < N && map[x][y + X] == map[x][y] - 1) {	// 내리막 경사로 설치 검사
		for (int yy = y + 1; yy < y + X; yy++)
			if (map[x][yy] != map[x][y + X])	return;	// 경사로 설치 지점이 평탄하지 않은 경우
		row(x, y + X, true);
	}
}
// 열 검사
// flag: 현재 위치의 내리막 경사로 설치 여부
void col(int x, int y, int flag) {
	if (x == N - 1) {	// 활주로 끝에 도달
		ans++;
		return;
	}
	if (x + X < N && map[x + X][y] == map[x][y] + 1) {	// 오르막 경사로 설치 검사
		if (flag)	return;	// 현재 위치에 내리막 경사로가 설치되어 오르막 경사로 설치 불가
		for (int xx = x + 1; xx < x + X; xx++)
			if (map[xx][y] != map[x][y])	return;	// 경사로 설치 지점이 평탄하지 않은 경우
		col(x + X, y, false);
	}
	else if (map[x + 1][y] == map[x][y])	// 평지 검사
		col(x + 1, y, false);
	else if (x + X < N && map[x + X][y] == map[x][y] - 1) {	// 내리막 경사로 설치 검사
		for (int xx = x + 1; xx < x + X; xx++)
			if (map[xx][y] != map[x + X][y])	return;	// 경사로 설치 지점이 평탄하지 않은 경우
		col(x + X, y, true);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d", &N, &X);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		// 처리부
		ans = 0;
		for (int i = 0; i < N; i++) {
			row(i, 0, false);
			col(0, i, false);
		}
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}