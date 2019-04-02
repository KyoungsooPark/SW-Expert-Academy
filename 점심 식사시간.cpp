/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&categoryId=AV5-BEE6AK0DFAVl&categoryType=CODE
*/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef struct { int x, y, nPerson; } stairs;
typedef struct { int x, y, dst, time; } person;
enum { DOWN, WAIT, MOVE };	// ��� �̵� ��, ��� ��, 
vector<stairs> S;
vector<person> v;
queue<person> q[3];	// �ùķ��̼��� ���� �켱����ť
int map[10][10];
int N, ans;

int min(int a, int b) { return a < b ? a : b; }
// �켱����ť empty ���� ��ȯ
bool empty(void) { return q[DOWN].empty() && q[WAIT].empty() && q[MOVE].empty(); }
// person p�� ��ǥ ������� �̵�
void move(person &p) {
	if (S[p.dst].x < p.x)		p.x--;
	else if (S[p.dst].x > p.x)	p.x++;
	else if (S[p.dst].y < p.y)	p.y--;
	else if (S[p.dst].y > p.y)	p.y++;
}
// �̵� �� ������ ��� �������� �ùķ��̼�
void simulation(void) {
	int time = 0;
	for (person p : v)	// ��� ����� �켱����ť�� ����
		q[MOVE].push(p);
	while (!empty()) {
		time++;
		// �켱����(DOWN, WAIT, MOVE)�� ���� ����
		for (int priority = DOWN; priority <= MOVE; priority++) {
			int size = q[priority].size();
			while (size--) {
				person p = q[priority].front(); q[priority].pop();
				switch (priority) {
				case DOWN:	// ���
					if (--p.time == 0) S[p.dst].nPerson--;	// ��� �������� �ð��� ��� ���� ���
					else q[DOWN].push(p);
					break;
				case WAIT:	// ��ܿ��� ���
							// ����� �������� �ο��� 3�� �̸��� ��� ��� �������� ����
					if (S[p.dst].nPerson < 3) { p.time = map[p.x][p.y]; S[p.dst].nPerson++; q[DOWN].push(p); }
					else q[WAIT].push(p);
					break;
				case MOVE:	// ������� �̵�
					move(p);	// person p�� ��ǥ ������� �̵�
					if (p.x == S[p.dst].x && p.y == S[p.dst].y) q[WAIT].push(p);	// ��� ����
					else q[MOVE].push(p);	// ���� ���� ��� ��� move ����
					break;
				}
			}
		}
	}
	ans = min(ans, time);
}
// ����� �����ϴ� ��� ��� Ž��
void go(int n) {
	if (n == v.size()) { simulation(); return; }	// ��� ���� �Ϸ� �� �ùķ��̼� ����
	for (int i = 0; i < 2; i++) { v[n].dst = i; go(n + 1); }
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1)	v.push_back({ i, j, 0 });	// ���
				else if (map[i][j] > 1)	S.push_back({ i, j, 0 });	// ���
			}
		// ó����
		ans = 2e9;
		go(0);
		S.clear(), v.clear();	// ���� �׽�Ʈ�� ���� ���� �ʱ�ȭ
								// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}