/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

int board[12][12];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int N, num, ans;
// �־��� core p���� ���� d���� ���� ��ġ ���� ���� �˻�
bool available(point p, int d) {
	int x = p.x + dx[d], y = p.y + dy[d];
	while (0 <= x && x < N && 0 <= y && y < N) {
		if (board[x][y])
			return false;
		x += dx[d], y += dy[d];
	}
	return true;
}
// �־��� core p���� ���� d�� ���� ��ġ(value=1) �Ǵ� ����(value=0)
int set(point p, int d, int value) {
	int ret = 0;
	int x = p.x + dx[d], y = p.y + dy[d];
	while (0 <= x && x < N && 0 <= y && y < N) {
		board[x][y] = value;
		ret++;
		x += dx[d], y += dy[d];
	}
	return ret;
}
// ��� ��쿡 ���� ���� ��ġ ��� �˻�
void go(const vector<point> &core, int n, int cnt, int sum) {
	if (n == core.size()) {	// ������ ���� ��ġ ����� ���� ��� core �˻簡 ���� ���
		if (num < cnt) {	// ������ ��ġ�� core�� ���� ��������� �ִ񰪺��� ū ���
			num = cnt;	// �ִ� ����
			ans = sum;	// ���� ������ �� ����
		}
		else if (num == cnt && ans > sum)	// ������ �ִ񰪰� ������ ���� ������ ���� �� ���� ���
			ans = sum;	// ���� ������ �� ����
		return;
	}
	for (int d = 0; d < 4; d++) {
		if (available(core[n], d)) {	// core[n]�� ���� ��ġ�� ������ ���
			int temp = set(core[n], d, 1);	// ���� ��ġ
			go(core, n + 1, cnt + 1, sum + temp);
			set(core[n], d, 0);	// ���� ����
		}
	}
	go(core, n + 1, cnt, sum);	// core[n]�� ������ ��ġ���� ����
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		vector<point> core;
		// �Էº�
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &board[i][j]);
				if (!board[i][j])
					continue;
				if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
					continue;
				core.push_back({ i, j });	// �����ڸ��� ������ ��ġ�� core�� push
			}
		}
		ans = 2e9;
		num = 0;
		// ó����
		go(core, 0, 0, 0);
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}