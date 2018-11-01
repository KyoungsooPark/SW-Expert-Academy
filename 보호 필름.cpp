#include <cstdio>
using namespace std;

int film[13][20], film_cpy[13][20], change[13];
int D, W, K, ans;

bool test(void) {
	// ��ǰ ����
	for (int d = 0; d < D; d++) {
		// ��ǰ ���� ����
		if (change[d] == -1)
			for (int w = 0; w < W; w++)
				film_cpy[d][w] = film[d][w];
		// ��ǰ ����
		else
			for (int w = 0; w < W; w++)
				film_cpy[d][w] = change[d];
	}

	// ���ɰ˻�
	for (int w = 0; w < W; w++) {
		int cnt = 1;
		for (int d = 1; d < D; d++) {
			cnt = film_cpy[d][w] == film_cpy[d - 1][w] ? cnt + 1 : 1;
			if (cnt >= K)
				break;
		}
		if (cnt < K)
			return false;
	}
	return true;
}

void go(int n, int cnt) {
	if (n == D) {
		if (test() && cnt < ans)
			ans = cnt;
		return;
	}

	change[n] = -1; go(n + 1, cnt);	// n ��° ���� ��ǰ ���� ����
	// ������� ���ɰ˻縦 ����� �ּ� ��ǰ ���� Ƚ����
	// �ʰ��� ��� ���̻� �������� ����
	if (cnt == ans)
		return;
	change[n] = 0; go(n + 1, cnt + 1);	// n ��° ���� ��ǰ A ����
	change[n] = 1; go(n + 1, cnt + 1);	// n ��° ���� ��ǰ B ����
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d %d %d", &D, &W, &K);
		for (int d = 0; d < D; d++)
			for (int w = 0; w < W; w++)
				scanf("%d", &film[d][w]);

		// ó����
		if (K == 1) {
			printf("#%d %d\n", t, 0);
			continue;
		}
		ans = 2e9;
		go(0, 0);
		
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}