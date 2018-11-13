/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
*/

/*
����: http://2youngjae.tistory.com/72

1�� or 1�� / 3�� / 1�� ---> 3������ ����

dMonth: �� ���� min( �ϼ� x 1�� �̿��, 1�� �̿�� ) ����
d[n]  : n ��° ���� ���� �ּҰ� ����

ex) 4���� ���� �ּҰ� d[4]�� ���� 3���� ��� �� �ּҰ�

	1. dMonth[1] + dMonth[2] + dMonth[3] + dMonth[4]
	2. 3��(1, 2, 3) �̿�� + dMonth[4];
	3. dMonth[1] + 3��(2, 3, 4) �̿��

 ���⼭ 1���� 2����

	d[3] + dMonth[4]

�̰�, 3����

	d[1] + 3�� �̿��

����,

	d[4] = min( d[3] + dMonth[4], d[1] + 3�� �̿��)

�̸� ���� ��ȭ���� ��������,

	d[n] = min( d[n-1] + dMonth[n], d[n-3] + 3�� �̿�� )

ex) n = 7	: d[6] + dMonth[7] : 6�������� �ּҺ�� + 7�� �ּҺ��
			: d[4] + 3���̿�� : 4�������� �ּҺ�� + 3��(5, 6, 7) �̿�� ���

���������� d[12]�� 1�� �̿�� ��
*/

#include <cstdio>
using namespace std;

int price[4], table[13];
int dMonth[13];	// ���� �ּҰ�
int d[13];		// N ��° ���� ���� �ּҰ�

int min(int a, int b) { return (a < b) ? a : b; }

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		for (int i = 0; i < 4; i++)
			scanf("%d", &price[i]);
		for (int i = 1; i <= 12; i++)
			scanf("%d", &table[i]);

		// ó����
		for (int i = 1; i <= 12; i++)
			// min(1�� �̿�� ��� x �ϼ�, 1�� �̿�� ���)
			dMonth[i] = min(price[0] * table[i], price[1]);

		for (int i = 1; i <= 12; i++) {
			d[i] = d[i - 1] + dMonth[i];
			if (i >= 3)
				d[i] = min(d[i], d[i - 3] + price[2]);
		}
		if (d[12] > price[3])
			d[12] = price[3];

		// ��º�
		printf("#%d %d\n", t, d[12]);
	}
	return 0;
}
