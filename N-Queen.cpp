/*
https://www.swexpertacademy.com/main/solvingProblem/solvingProblem.do
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

vector<point> v(10);
int N, ans;

int abs(int num) { return num >= 0 ? num : -num; }

bool isvalid(int x, int y) {
	for (int i = 0; i < x; i++)
		if (v[i].y == y || abs(v[i].x - x) == abs(v[i].y - y))
			return false;
	return true;
}

void go(int n) {
	if (n == N) {
		ans++;
		return;
	}
	for (int i = 0; i < N; i++) {
		if (isvalid(n, i)) {
			v[n] = { n, i };
			go(n + 1);
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		ans = 0;
		for (int i = 0; i < N; i++) {
			v[0] = { 0, i };
			go(1);
		}
		printf("#%d %d\n", t, ans);
	}
}