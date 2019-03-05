/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PTeo6AHUDFAUq&categoryId=AV5PTeo6AHUDFAUq&categoryType=CODE
*/

#include <cstdio>
using namespace std;

int d[1001] = { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 };

void fill(int num, int unit, int most) {
	if (most % 3)
		for (int i = num, j = 0; i < num + unit; i++, j++)
			d[i] = d[j];
	else
		for (int i = num; i < num + unit; i++)
			d[i] = d[i - unit] + 1;
}

int main(void) {
	int n, unit = 10, most;
	scanf("%d", &n);
	for (int i = 10; i <= n; i += unit) {
		if (i == 100)	unit = 100;
		fill(i, unit, i / unit);
	}
	printf("1");
	for (int i = 2; i <= n; i++) {
		printf(" ");
		if (!d[i])
			printf("%d", i);
		else
			for (int j = 0; j < d[i]; j++)
				printf("-");
	}
	printf("\n");
	return 0;
}