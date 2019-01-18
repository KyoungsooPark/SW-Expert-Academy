/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV7IzvG6EksDFAXB&categoryId=AV7IzvG6EksDFAXB&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int arr[20];

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, k, ans = 0;
		// 입력부
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		// 처리부
		for (int i = 1; i < (1 << n); i++) {
			int temp = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					temp += arr[j];
					if (temp > k)	// 실행 시간을 줄이는 핵심
						break;
				}
			}
			if (temp == k)
				ans++;
		}
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
