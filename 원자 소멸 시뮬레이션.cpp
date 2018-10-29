/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE
*/
#include <cstdio>
#define QUEUESIZE	100000
using namespace std;
typedef struct { int r, c, d, k; } atom;
atom q[QUEUESIZE];
int map[4001][4001];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int begin, end;

bool empty(void) {
	return begin == end;
}

void push(atom a) {
	q[end++] = a;
	if (end == QUEUESIZE)
		end = 0;
}

atom pop(void) {
	atom ret = q[begin++];
	if (begin == QUEUESIZE)
		begin = 0;
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, ans = 0;
		begin = end = 0;

		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int c, r, d, k;
			scanf("%d %d %d %d", &c, &r, &d, &k);
			// 1�� ������ 0.5�� ������ ����
			r = 4000 - (r + 1000) * 2;
			c = (c + 1000) * 2;
			map[r][c] = k;
			// �ʱ� ���ڵ��� ��ġ ť�� ����
			push({ r, c, d, k });
		}

		// ó����
		while (!empty()) {
			atom a = pop();
			if (map[a.r][a.c] > a.k)
				ans += map[a.r][a.c];
			else {
				int nr = a.r + dr[a.d], nc = a.c + dc[a.d];
				if (0 <= nr && nr < 4001 && 0 <= nc && nc < 4001) {
					// ���� ��ġ�� ���ڰ� �������� ������
					if (map[nr][nc] == 0)
						// ���� �̵��� ���� ť�� ����
						push({ nr, nc, a.d, a.k });
					// �����ϸ� �Ҹ�� ���� ť�� �������� �ʰ� ������ �������� �׾Ƶ�
					map[nr][nc] += map[a.r][a.c];
				}
			}
			// �̵� �� ��ġ�� �������� 0���� ����
			map[a.r][a.c] = 0;
		}

		// ��º�
		printf("#%d %d\n", t, ans);
	}

	return 0;
}