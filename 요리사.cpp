/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH&categoryId=AWIeUtVakTMDFAVH&categoryType=CODE
*/

#include <cstdio>
#include <vector>
using namespace std;

int table[16][16];
bool visited[16];
vector<int> A;
int N, ans;

int calculate(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i] != visited[j])
				continue;
			// A �丮�� ���
			if (visited[i])
				ret += table[i][j];
			// B �丮�� ���
			else
				ret -= table[i][j];
		}
	}
	// ���밪 ��ȯ
	return ret > 0 ? ret : -ret;
}

void go(int n, int cur) {
	if (n == N / 2) {
		int temp = calculate();
		if (ans > temp)
			ans = temp;
		return;
	}
	
	// nC(n/2) ������ ���� ����
	for (int i = cur; i <= N / 2 + n; i++) {
		// A �丮�� ��� ����
		visited[i] = true;
		go(n + 1, i + 1);
		visited[i] = false;
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &table[i][j]);

		// ó����
		ans = 2e9;
		go(0, 0);

		//��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}