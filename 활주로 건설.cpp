/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int map[20][20];
int N, X, ans;

int row(int x, int y, bool flag) {
	if (y == N - 1)
		return 1;

	// 오르막
	// 오르막은 경사로 길이만큼 이전에서 검사해야 하므로 가장 먼저 수행
	if (y + X < N && map[x][y] - map[x][y + X] == -1) {
		// 현재 위치에 내리막 경사로가 놓여져 있는 경우
		if (flag)
			return 0;
		for (int i = y + 1; i < y + X; i++)
			// 경사로를 놓을 수 없는 경우
			if (map[x][y] != map[x][i])
				return 0;
		return row(x, y + X, false);
	}
	// 평지
	else if (map[x][y] == map[x][y + 1])
		return row(x, y + 1, false);

	// 내리막
	else if (y + X < N && map[x][y] - map[x][y + X] == 1) {
		for (int i = y + 1; i < y + X; i++)
			// 경사로를 놓을 수 없는 경우
			if (map[x][y + X] != map[x][i])
				return 0;
		return row(x, y + X, true);
	}
	return 0;
}

int col(int x, int y, bool flag) {
	if (x == N - 1)
		return 1;

	// 오르막
	// 오르막은 경사로 길이만큼 이전에서 검사해야 하므로 가장 먼저 수행
	if (x + X < N && map[x][y] - map[x + X][y] == -1) {
		// 현재 위치에 내리막 경사로가 놓여져 있는 경우
		if (flag)
			return 0;
		for (int i = x + 1; i < x + X; i++)
			// 경사로를 놓을 수 없는 경우
			if (map[x][y] != map[i][y])
				return 0;
		return col(x + X, y, false);
	}

	else if (map[x][y] == map[x + 1][y])
		return col(x + 1, y, false);

	// 내리막
	else if (x + X < N && map[x][y] - map[x + X][y] == 1) {
		for (int i = x + 1; i < x + X; i++)
			// 경사로를 놓을 수 없는 경우
			if (map[x + X][y] != map[i][y])
				return 0;
		return col(x + X, y, true);
	}
	return 0;
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
		for (int r = 0; r < N; r++)
			ans += row(r, 0, false);
		for (int c = 0; c < N; c++)
			ans += col(0, c, false);

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}