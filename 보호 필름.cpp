#include <cstdio>
using namespace std;

int film[13][20], film_cpy[13][20], change[13];
int D, W, K, ans;

bool test(void) {
	// 약품 투여
	for (int d = 0; d < D; d++) {
		// 약품 투여 안함
		if (change[d] == -1)
			for (int w = 0; w < W; w++)
				film_cpy[d][w] = film[d][w];
		// 약품 투여
		else
			for (int w = 0; w < W; w++)
				film_cpy[d][w] = change[d];
	}

	// 성능검사
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

	change[n] = -1; go(n + 1, cnt);	// n 번째 막에 약품 투여 안함
	// 현재까지 성능검사를 통과한 최소 약품 투입 횟수를
	// 초과할 경우 더이상 진행하지 않음
	if (cnt == ans)
		return;
	change[n] = 0; go(n + 1, cnt + 1);	// n 번째 막에 약품 A 투여
	change[n] = 1; go(n + 1, cnt + 1);	// n 번째 막에 약품 B 투여
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d %d", &D, &W, &K);
		for (int d = 0; d < D; d++)
			for (int w = 0; w < W; w++)
				scanf("%d", &film[d][w]);

		// 처리부
		if (K == 1) {
			printf("#%d %d\n", t, 0);
			continue;
		}
		ans = 2e9;
		go(0, 0);
		
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}