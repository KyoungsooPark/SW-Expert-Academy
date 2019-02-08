/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV134DPqAA8CFAYh&categoryId=AV134DPqAA8CFAYh&categoryType=CODE&&&#none
*/

#include <cstdio>
using namespace std;

int map[1000];

int max(int a, int b) { return a >= b ? a : b; }

int main(void) {
	for (int t = 1; t <= 10; t++) {
		int N, ans = 0;
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &map[i]);
		// ó����
		for (int i = 2; i < N - 2; i++) {
			// �Ÿ� 2 ���� �ֺ� �ְ��� �������� ���� �� ���
			int temp = map[i] - max(max(map[i - 2], map[i - 1]), max(map[i + 1], map[i + 2]));
			if (temp > 0)	// �ֺ� �������� �� ���� ���
				ans += temp;	// ���� �� ��ŭ�� ���� �� �ջ�
		}
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}