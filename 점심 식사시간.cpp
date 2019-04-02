/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&categoryId=AV5-BEE6AK0DFAVl&categoryType=CODE
*/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef struct { int x, y, nPerson; } stairs;
typedef struct { int x, y, dst, time; } person;
enum { DOWN, WAIT, MOVE };
vector<stairs> S;
vector<person> v;
queue<person> q[3];	// 시뮬레이션을 위한 우선순위큐
int map[10][10];
int N, ans;

int min(int a, int b) { return a < b ? a : b; }
// 우선순위큐 empty 여부 반환
bool empty(void) { return q[DOWN].empty() && q[WAIT].empty() && q[MOVE].empty(); }
// person p의 목표 계단으로 이동
void move(person &p) {
	if (S[p.dst].x < p.x)		p.x--;
	else if (S[p.dst].x > p.x)	p.x++;
	else if (S[p.dst].y < p.y)	p.y--;
	else if (S[p.dst].y > p.y)	p.y++;
}
// 이동 및 지정된 계단 내려가는 시뮬레이션
void simulation(void) {
	int time = 0;
	for (person p : v)	// 모든 사람을 우선순위큐에 삽입
		q[MOVE].push(p);
	while (!empty()) {
		time++;
		// 우선순위(DOWN, WAIT, MOVE)에 따라 수행
		for (int priority = DOWN; priority <= MOVE; priority++) {
			int size = q[priority].size();
			while (size--) {
				person p = q[priority].front(); q[priority].pop();
				switch (priority) {
				case DOWN:	// 계단
					if (--p.time == 0) S[p.dst].nPerson--;	// 계단 내려가는 시간이 모두 지난 경우
					else q[DOWN].push(p);
					break;
				case WAIT:	// 계단에서 대기
							// 계단을 내려가는 인원이 3명 미만인 경우 계단 내려가기 시작
					if (S[p.dst].nPerson < 3) { p.time = map[p.x][p.y]; S[p.dst].nPerson++; q[DOWN].push(p); }
					else q[WAIT].push(p);
					break;
				case MOVE:	// 계단으로 이동
					move(p);	// person p의 목표 계단으로 이동
					if (p.x == S[p.dst].x && p.y == S[p.dst].y) q[WAIT].push(p);	// 계단 도착
					else q[MOVE].push(p);	// 도착 못한 경우 계속 move 수행
					break;
				}
			}
		}
	}
	ans = min(ans, time);
}
// 계단을 선택하는 모든 경우 탐색
void go(int n) {
	if (n == v.size()) { simulation(); return; }	// 계단 선택 완료 시 시뮬레이션 수행
	for (int i = 0; i < 2; i++) { v[n].dst = i; go(n + 1); }
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// 입력부
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1)	v.push_back({ i, j, 0 });	// 사람
				else if (map[i][j] > 1)	S.push_back({ i, j, 0 });	// 계단
			}
		// 처리부
		ans = 2e9;
		go(0);
		S.clear(), v.clear();	// 다음 테스트를 위한 벡터 초기화
								// 출력부
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
