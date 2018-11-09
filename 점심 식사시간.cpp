/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&categoryId=AV5-BEE6AK0DFAVl&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	1000
using namespace std;
typedef struct { int idx, x, y, dst, delay; } person;
typedef struct { int x, y, n; } stairs;

person queue[2][QUEUESIZE]; // queue[0]: 계단을 내려가는 인원, queue[1]: 계단으로 이동 또는 계단 대기 인원
person p[10];
stairs s[2];
int map[10][10];
int N, begin[2], end[2];

bool empty(int priority) {
	return begin[priority] == end[priority];
}
int size(int priority) {
	int ret = end[priority] - begin[priority];
	return ret >= 0 ? ret : QUEUESIZE + ret;
}
void push(person psn, int priority) {
	queue[priority][end[priority]++] = psn;
	if (end[priority] == QUEUESIZE)
		end[priority] = 0;
}
person pop(int priority) {
	person psn = queue[priority][begin[priority]++];
	if (begin[priority] == QUEUESIZE)
		begin[priority] = 0;
	return psn;
}

void move(person &psn) {
	// 계단 위치로 이동
	if (psn.x > s[psn.dst].x)
		psn.x--;
	else if (psn.x < s[psn.dst].x)
		psn.x++;
	else if (psn.y > s[psn.dst].y)
		psn.y--;
	else if (psn.y < s[psn.dst].y)
		psn.y++;
	// 계단에 있는 경우
	else {
		// 계단 입구에 있는 경우
		if (psn.delay == -1) {
			// 계단을 내려가는 사람이 3명 미만인 경우
			if (s[psn.dst].n < 3) {
				// 계단 내려가기 시작
				psn.delay = map[psn.x][psn.y];
				// 계단 내려가는 사람 수 증가
				s[psn.dst].n++;
			}
		}
		// 계단을 내려가고 있는 경우
		else if (psn.delay > 0) {
			// 남은 시간 감소
			psn.delay--;
			// 다 내려간 경우
			if (psn.delay == 0)
				// 계단 내려가는 사람 수 감소
				s[psn.dst].n--;
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int nPerson = 0, nStairs = 0, time, cnt, ans = 2e9;
		begin[0] = begin[1] = end[0] = end[1] = 0;

		// 입력부
		scanf("%d", &N);
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				scanf("%d", &map[r][c]);
				if (map[r][c] == 1)
					p[nPerson++] = { nPerson, r, c, 0, -1 };
				else if (map[r][c] > 1)
					s[nStairs++] = { r, c, 0 };
			}
		}

		// 처리부
		// 내려갈 계단을 선택하는 모든 경우의 수에 대해 수행
		for (int i = 0; i < (1 << nPerson); i++) {
			for (int j = 0; j < nPerson; j++) {
				if (i & (1 << j))
					// 두 번째 계단 선택
					p[j].dst = 1;
				else
					// 첫 번째 계단 선택
					p[j].dst = 0;
			}

			// 경우의 수마다 최초 시작 시 queue[1]에 삽입
			for (int k = 0; k < nPerson; k++)
				push(p[k], 1);

			time = 0;
			cnt = nPerson;
			// 모든 사람이 계단을 내려갈 때까지
			while (cnt) {
				// 계단을 내려가고 있는 사람을 우선 수행
				for (int priority = 0; priority < 2; priority++) {
					int qsize = size(priority);
					while (qsize--) {
						person psn = pop(priority);
						// 이동
						move(psn);
						// 계단을 내려가고 있는 경우
						if (psn.delay > 0)
							// 우선순위가 높은 queue에 삽입
							push(psn, 0);
						// 계단을 내려가고 있지 않은 경우
						else if (psn.delay == -1)
							// 우선순위가 낮은 queue에 삽입
							push(psn, 1);
						// 계단을 다 내려간 경우
						else
							// 인원 수 감소
							cnt--;
					}
				}
				// 모든 인원이 한 번씩 수행한 경우 시간 증가
				time++;
			}
			if (ans > time)
				ans = time;
		}
		
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
