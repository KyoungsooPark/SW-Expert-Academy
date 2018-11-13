/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&categoryId=AV597vbqAH0DFAVl&categoryType=CODE
*/

/*
참고: http://2youngjae.tistory.com/72

1일 or 1달 / 3달 / 1년 ---> 3가지로 분할

dMonth: 각 월별 min( 일수 x 1일 이용권, 1달 이용권 ) 저장
d[n]  : n 번째 달의 누적 최소값 저장

ex) 4월의 누적 최소값 d[4]은 다음 3가지 경우 중 최소값

	1. dMonth[1] + dMonth[2] + dMonth[3] + dMonth[4]
	2. 3달(1, 2, 3) 이용권 + dMonth[4];
	3. dMonth[1] + 3달(2, 3, 4) 이용권

 여기서 1번과 2번은

	d[3] + dMonth[4]

이고, 3번은

	d[1] + 3달 이용권

따라서,

	d[4] = min( d[3] + dMonth[4], d[1] + 3달 이용권)

이를 토대로 점화식을 세워보면,

	d[n] = min( d[n-1] + dMonth[n], d[n-3] + 3달 이용권 )

ex) n = 7	: d[6] + dMonth[7] : 6월까지의 최소비용 + 7월 최소비용
			: d[4] + 3달이용권 : 4월까지의 최소비용 + 3달(5, 6, 7) 이용권 비용

마지막으로 d[12]와 1년 이용권 비교
*/

#include <cstdio>
using namespace std;

int price[4], table[13];
int dMonth[13];	// 월간 최소값
int d[13];		// N 번째 달의 누적 최소값

int min(int a, int b) { return (a < b) ? a : b; }

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		for (int i = 0; i < 4; i++)
			scanf("%d", &price[i]);
		for (int i = 1; i <= 12; i++)
			scanf("%d", &table[i]);

		// 처리부
		for (int i = 1; i <= 12; i++)
			// min(1일 이용권 요금 x 일수, 1달 이용권 요금)
			dMonth[i] = min(price[0] * table[i], price[1]);

		for (int i = 1; i <= 12; i++) {
			d[i] = d[i - 1] + dMonth[i];
			if (i >= 3)
				d[i] = min(d[i], d[i - 3] + price[2]);
		}
		if (d[12] > price[3])
			d[12] = price[3];

		// 출력부
		printf("#%d %d\n", t, d[12]);
	}
	return 0;
}
