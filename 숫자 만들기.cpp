/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH&categoryId=AWIeRZV6kBUDFAVH&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int num[12], optr[4], opt_cmb[11];
int N, max, min;

int calculate(void) {
	int ret = num[0];
	for (int i = 0; i < N - 1; i++) {
		switch (opt_cmb[i]) {
		case 0: ret += num[i + 1]; break;
		case 1: ret -= num[i + 1]; break;
		case 2: ret *= num[i + 1]; break;
		case 3: ret /= num[i + 1]; break;
		}
	}
	return ret;
}

void go(int n) {
	if (n == N - 1) {
		int temp = calculate();
		if (max < temp)
			max = temp;
		if (min > temp)
			min = temp;
		return;
	}

	for (int j = 0; j < 4; j++) {
		// ������ ������ �����ִ� ���
		if (optr[j] > 0) {
			// ������ �ϳ� ���̰�
			optr[j]--;
			// �ش� �����ڸ� �Է�
			opt_cmb[n] = j;
			// ���� ���� ����
			go(n + 1);
			// ���� ��ȯ
			optr[j]++;
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		max = -2e9, min = 2e9;

		// �Էº�
		scanf("%d", &N);
		// optr[0]: + ������ ����
		// optr[1]: - ������ ����
		// optr[2]: * ������ ����
		// optr[3]: / ������ ����
		for (int i = 0; i < 4; i++)
			scanf("%d", &optr[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &num[i]);

		// ó����
		go(0);

		// ��º�
		printf("#%d %d\n", t, max - min);
	}
	return 0;
}