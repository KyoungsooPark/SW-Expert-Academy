/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int price[4], table[14], pay[14];
int ans;

void go(int n) {
	if (n >= 12) {
		int temp = 0;
		for (int i = 0; i < 12; i++)
			temp += pay[i];
		if (ans > temp)
			ans = temp;
		return;
	}

	// 1일 이용권
	pay[n] = table[n] * price[0];
	go(n + 1);

	// 1달 이용권
	pay[n] = table[n] ? price[1] : 0;
	go(n + 1);

	// 3달 이용권
	if (table[n] || table[n + 1] || table[n + 2])
		pay[n] = price[2];
	else
		pay[n] = 0;
	pay[n + 1] = pay[n + 2] = 0;
	go(n + 3);
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		for (int i = 0; i < 4; i++)
			scanf("%d", &price[i]);
		for (int i = 0; i < 12; i++)
			scanf("%d", &table[i]);

		// 처리부
		ans = price[3];	// 1년 이용권
		go(0);

		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
