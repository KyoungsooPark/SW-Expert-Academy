/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do
*/

#include <cstdio>
using namespace std;

int wheel[4][8], top_idx[4];
// wheel_idx 번째 톱니바퀴의 왼쪽 자성
int left_tip(int wheel_idx) {
	int idx = top_idx[wheel_idx] - 2;
	if (idx < 0)
		idx += 8;
	return wheel[wheel_idx][idx];
}
// wheel_idx 번째 톱니바퀴의 오른쪽 자성
int right_tip(int wheel_idx) {
	int idx = top_idx[wheel_idx] + 2;
	if (idx > 7)
		idx -= 8;
	return wheel[wheel_idx][idx];
}
// wheel_idx 번째 톱니바퀴의 top 위치 변경
void change_top(int wheel_idx, int direction) {
	top_idx[wheel_idx] -= direction;
	if (top_idx[wheel_idx] == -1)
		top_idx[wheel_idx] = 7;
	else if (top_idx[wheel_idx] == 8)
		top_idx[wheel_idx] = 0;
}
// 톱니바퀴 회전
void rotate(int wheel_idx, int direction) {
	int dir_info[4];
	dir_info[wheel_idx] = direction;
	// 왼쪽 톱니바퀴의 회전 방향 설정
	for (int left = wheel_idx - 1; left >= 0; left--) {
		if (dir_info[left + 1] && right_tip(left) != left_tip(left + 1))
			dir_info[left] = dir_info[left + 1] * (-1);
		else
			dir_info[left] = 0;
	}
	// 오른쪽 톱니바퀴의 회전 방향 설정
	for (int right = wheel_idx + 1; right <= 3; right++) {
		if (dir_info[right - 1] && left_tip(right) != right_tip(right - 1))
			dir_info[right] = dir_info[right - 1] * (-1);
		else
			dir_info[right] = 0;
	}
	// 전체 톱니바퀴 회전
	for (int wh = 0; wh < 4; wh++)
		if (dir_info[wh])
			change_top(wh, dir_info[wh]);
}
// 점수 계산
int score(void) {
	int ret = 0;
	for (int wh = 0, s = 1; wh < 4; wh++, s <<= 1) {
		ret += wheel[wh][top_idx[wh]] * s;
	}
	return ret;
}

int main(void) {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		int K; scanf("%d", &K);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++)
				scanf("%d", &wheel[i][j]);
			top_idx[i] = 0;
		}

		// 처리부
		while (K--) {
			int wh, d;
			scanf("%d %d", &wh, &d);
			rotate(wh - 1, d);
		}

		//출력부
		printf("#%d %d\n", t, score());
	}
	return 0;
}
