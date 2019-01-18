/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5LrsUaDxcDFAXc&categoryId=AV5LrsUaDxcDFAXc&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int price[1000000], N;

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		long long ans = 0;
		// ÀÔ·ÂºÎ
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &price[i]);
		// Ã³¸®ºÎ
		for (int i = N - 2, max_price = price[N - 1]; i >= 0; i--) {
			if (price[i] > max_price)
				max_price = price[i];
			else
				ans += max_price - price[i];
		}
		// Ãâ·ÂºÎ
		printf("#%d %lld\n", t, ans);
	}
	return 0;
}
