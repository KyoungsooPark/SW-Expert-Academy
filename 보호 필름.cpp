#include <cstdio>
using namespace std;

int film[13][20], cpy[13][20], select[13];
int D, W, K, ans;

int min(int a, int b) { return a < b ? a : b; }

bool validation(void) {
	// 필름 카피
	for (int i = 0; i < D; i++) {
		if (select[i] == -1)	// i번째 행에 약품 투입 안함
			for (int j = 0; j < W; j++)
				cpy[i][j] = film[i][j];
		else	// i번째 행에 약품 투입
			for (int j = 0; j < W; j++)
				cpy[i][j] = select[i];
	}
	for (int j = 0; j < W; j++) {	// j번째 열 검사
		int cnt = 1;	// 특성이 연속되는 횟수
		for (int i = 1; i < D; i++) {	// i번째 행 검사
			if (cpy[i][j] == cpy[i - 1][j]) {	// 이전 행과 특성이 동일
				cnt++;
				if (cnt == K)	// j열 합격 기준 통과
					break;
			}
			else	// 특성이 연속되지 않음
				cnt = 1;	// 다시 카운트
		}
		if (cnt != K)	// j열 합격 기준 미달
			return false;
	}
	return true;	// 모든 열이 합격 기준 통과 시 true 반환
}

void go(int n, int num) {
	if (n == D) {
		if (validation())
			ans = min(ans, num);
		return;
	}
	if (ans == num)	return;	// ans보다 더 많은 투입이 필요한 경우 중단
	select[n] = -1; go(n + 1, num);		// 약품 투입 안함
	select[n] = 0;  go(n + 1, num + 1);	// 약품 A 투입
	select[n] = 1;  go(n + 1, num + 1);	// 약품 B 투입
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d %d %d", &D, &W, &K);
		for (int i = 0; i < D; i++)
			for (int j = 0; j < W; j++)
				scanf("%d", &film[i][j]);
		// 처리부
		ans = 2e9;
		go(0, 0);
		// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}