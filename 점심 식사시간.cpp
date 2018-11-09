/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&categoryId=AV5-BEE6AK0DFAVl&categoryType=CODE
*/

#include <cstdio>
#define QUEUESIZE	1000
using namespace std;
typedef struct { int idx, x, y, dst, delay; } person;
typedef struct { int x, y, n; } stairs;

person queue[2][QUEUESIZE]; // queue[0]: ����� �������� �ο�, queue[1]: ������� �̵� �Ǵ� ��� ��� �ο�
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
	// ��� ��ġ�� �̵�
	if (psn.x > s[psn.dst].x)
		psn.x--;
	else if (psn.x < s[psn.dst].x)
		psn.x++;
	else if (psn.y > s[psn.dst].y)
		psn.y--;
	else if (psn.y < s[psn.dst].y)
		psn.y++;
	// ��ܿ� �ִ� ���
	else {
		// ��� �Ա��� �ִ� ���
		if (psn.delay == -1) {
			// ����� �������� ����� 3�� �̸��� ���
			if (s[psn.dst].n < 3) {
				// ��� �������� ����
				psn.delay = map[psn.x][psn.y];
				// ��� �������� ��� �� ����
				s[psn.dst].n++;
			}
		}
		// ����� �������� �ִ� ���
		else if (psn.delay > 0) {
			// ���� �ð� ����
			psn.delay--;
			// �� ������ ���
			if (psn.delay == 0)
				// ��� �������� ��� �� ����
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

		// �Էº�
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

		// ó����
		// ������ ����� �����ϴ� ��� ����� ���� ���� ����
		for (int i = 0; i < (1 << nPerson); i++) {
			for (int j = 0; j < nPerson; j++) {
				if (i & (1 << j))
					// �� ��° ��� ����
					p[j].dst = 1;
				else
					// ù ��° ��� ����
					p[j].dst = 0;
			}

			// ����� ������ 
			for (int k = 0; k < nPerson; k++)
				push(p[k], 1);

			time = 0;
			cnt = nPerson;
			// ��� ����� ����� ������ ������
			while (cnt) {
				// ����� �������� �ִ� ����� �켱 ����
				for (int priority = 0; priority < 2; priority++) {
					int qsize = size(priority);
					while (qsize--) {
						person psn = pop(priority);
						// �̵�
						move(psn);
						// ����� �������� �ִ� ���
						if (psn.delay > 0)
							// �켱������ ���� queue�� ����
							push(psn, 0);
						// ����� �������� ���� ���� ���
						else if (psn.delay == -1)
							// �켱������ ���� queue�� ����
							push(psn, 1);
						// ����� �� ������ ���
						else
							// �ο� �� ����
							cnt--;
					}
				}
				// ��� �ο��� �� ���� ������ ��� �ð� ����
				time++;
			}
			if (ans > time)
				ans = time;
		}
		
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}