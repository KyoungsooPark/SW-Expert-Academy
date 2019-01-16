#include <cstdio>
using namespace std;

bool check[19], selected[9];
int table[19][19], card_a[9], card_b[9];
int win, lose;

void go(int n, int score) {
	if (n == 9) {
		if (score > 0)
			win++;
		else if (score < 0)
			lose++;
		return;
	}
	for (int i = 0; i < 9; i++) {
		if (!selected[i]) {
			selected[i] = true;
			go(n + 1, score + table[card_a[n]][card_b[i]]);
			selected[i] = false;
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	// table 초기화
	for (int i = 1; i <= 18; i++) {
		for (int j = 1; j <= 18; j++) {
			if (i >= j)
				table[i][j] = i + j;
			else
				table[i][j] = -(i + j);
		}
	}
	for (int t = 1; t <= T; t++) {
		// check 배열 초기화
		for (int i = 1; i <= 18; i++)
			check[i] = false;
		// 입력부
		for (int i = 0; i < 9; i++) {
			scanf("%d", &card_a[i]);
			check[card_a[i]] = true;
		}
		// 처리부
		for (int i = 1, j = 0; i <= 18; i++)
			if (!check[i])
				card_b[j++] = i;
		win = lose = 0;
		go(0, 0);
		// 출력부
		printf("#%d %d %d\n", t, win, lose);
	}
	return 0;
}