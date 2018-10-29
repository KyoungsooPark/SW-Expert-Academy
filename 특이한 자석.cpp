/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do
*/
#include <cstdio>
#define CLOCKWISE	1
#define COUNTERCLOCKWISE	-1
using namespace std;

typedef struct { int wheel_num, direction; } turn;
turn turn_info[20];
int wheel[4][8], top_idx[4];

int left_tooth(int wheel_num) {
	int idx = top_idx[wheel_num] - 2;
	if (idx < 0)
		idx += 8;
	return wheel[wheel_num][idx];
}

int right_tooth(int wheel_num) {
	int idx = top_idx[wheel_num] + 2;
	if (idx >= 8)
		idx -= 8;
	return wheel[wheel_num][idx];
}

void rotate(int wheel_num, int direction) {
	if (direction == CLOCKWISE) {
		top_idx[wheel_num]--;
		if (top_idx[wheel_num] < 0)
			top_idx[wheel_num] += 8;
	}
	else if (direction == COUNTERCLOCKWISE) {
		top_idx[wheel_num]++;
		if (top_idx[wheel_num] >= 8)
			top_idx[wheel_num] -= 8;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int K, ans = 0;
		// 입력부
		scanf("%d", &K);
		for (int wheel_num = 0; wheel_num < 4; wheel_num++) {
			for (int tooth_num = 0; tooth_num < 8; tooth_num++)
				scanf("%1d", &wheel[wheel_num][tooth_num]);
			top_idx[wheel_num] = 0;
		}
		for (int k = 0; k < K; k++) {
			scanf("%d %d", &turn_info[k].wheel_num, &turn_info[k].direction);
			turn_info[k].wheel_num--;
		}

		// 처리부
		for (int k = 0; k < K; k++) {
			int wheel_num = turn_info[k].wheel_num;
			int direction = turn_info[k].direction;
			int dir_arr[4];
			// 전체 톱니바퀴의 회전 방향 설정
			dir_arr[wheel_num] = direction;
			// 왼쪽 톱니바퀴의 회전 방향 설정
			for (int lw = wheel_num - 1; lw >= 0; lw--) {
				if (dir_arr[lw + 1] != 0 && right_tooth(lw) != left_tooth(lw + 1))
					dir_arr[lw] = dir_arr[lw + 1] * (-1);
				else
					dir_arr[lw] = 0;
			}
			// 오른쪽 톱니바퀴의 회전 방향 설정
			for (int rw = wheel_num + 1; rw < 4; rw++) {
				if (dir_arr[rw - 1] != 0 && right_tooth(rw - 1) != left_tooth(rw))
					dir_arr[rw] = dir_arr[rw - 1] * (-1);
				else
					dir_arr[rw] = 0;
			}
			// 전체 톱니바퀴 회전
			for (int w = 0; w < 4; w++)
				rotate(w, dir_arr[w]);
		}

		// 출력부
		for (int w = 0; w < 4; w++) {
			if (wheel[w][top_idx[w]] == 1)
				ans += (1 << w);
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}