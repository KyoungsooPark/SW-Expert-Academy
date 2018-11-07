/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE
*/

#include <cstdio>
using namespace std;
enum { RECEPTION_WAIT, REPAIR_WAIT };
typedef struct { int arrival_time, rec_num, rep_num; } customer;
typedef struct { int cstmr_num, processing_time; } desk;
customer cstmr[1001];
desk reception[10], repair[10];
int wait_queue[2][1001], begin[2], end[2];

bool empty(int queue_num) { return begin[queue_num] == end[queue_num]; }
void push(int queue_num, int cstmr_num) { wait_queue[queue_num][end[queue_num]++] = cstmr_num; }
int pop(int queue_num) { return wait_queue[queue_num][begin[queue_num]++]; }

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K, A, B, ans = 0;
		begin[0] = begin[1] = end[0] = end[1] = 0;

		// 입력부
		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		for (int n = 1; n <= N; n++)
			scanf("%d", &reception[n].processing_time);
		for (int m = 1; m <= M; m++)
			scanf("%d", &repair[m].processing_time);
		for (int k = 1; k <= K; k++) {
			scanf("%d", &cstmr[k].arrival_time);
			cstmr[k].rec_num = cstmr[k].rep_num = 0;
		}

		// 처리부
		for (int time = 0, done = 0; done < K; time++) {
			// 도착시간이 현재 시간과 동일한 고객을 RECEPTION_WAIT queue에 삽입
			for (int k = 1; k <= K; k++)
				if (cstmr[k].arrival_time == time)
					push(RECEPTION_WAIT, k);

			// RECEPTION 완료 시간이 현재 시간과 동일한 고객을 REPAIR_WAIT queue에 삽입
			for (int n = 1; n <= N; n++) {
				int cstmr_num = reception[n].cstmr_num;
				if (cstmr_num != 0 && cstmr[cstmr_num].arrival_time + reception[n].processing_time == time) {
					push(REPAIR_WAIT, cstmr_num);
					reception[n].cstmr_num = 0;
				}
			}

			// REPAIR까지 모두 마친 고객이 있으면 done 증가
			for (int m = 1; m <= M; m++) {
				int cstmr_num = repair[m].cstmr_num;
				if (cstmr_num != 0 && cstmr[cstmr_num].arrival_time + repair[m].processing_time == time) {
					repair[m].cstmr_num = 0;
					done++;
				}
			}

			// RECEPTION_WAIT 중인 고객이 있으면 빈 RECEPTION 창구에서 처리
			for (int n = 1; n <= N; n++) {
				if (empty(RECEPTION_WAIT))
					break;
				if (reception[n].cstmr_num == 0) {
					int cstmr_num = pop(RECEPTION_WAIT);
					reception[n].cstmr_num = cstmr_num;
					cstmr[cstmr_num].arrival_time = time;
					cstmr[cstmr_num].rec_num = n;
				}
			}

			// REPAIR_WAIT 중인 고객이 있으면 빈 REPAIR 창구에서 처리
			for (int m = 1; m <= M; m++) {
				if (empty(REPAIR_WAIT))
					break;
				if (repair[m].cstmr_num == 0) {
					int cstmr_num = pop(REPAIR_WAIT);
					repair[m].cstmr_num = cstmr_num;
					cstmr[cstmr_num].arrival_time = time;
					cstmr[cstmr_num].rep_num = m;
				}
			}
		}

		// 출력부
		for (int k = 1; k <= K; k++)
			if (cstmr[k].rec_num == A && cstmr[k].rep_num == B)
				ans += k;
		printf("#%d %d\n", t, ans > 0 ? ans : -1);
	}
	return 0;
}