#include <cstdio>
using namespace std;

int film[13][20], cpy[13][20], select[13];
int D, W, K, ans;

int min(int a, int b) { return a < b ? a : b; }

bool validation(void) {
	// �ʸ� ī��
	for (int i = 0; i < D; i++) {
		if (select[i] == -1)	// i��° �࿡ ��ǰ ���� ����
			for (int j = 0; j < W; j++)
				cpy[i][j] = film[i][j];
		else	// i��° �࿡ ��ǰ ����
			for (int j = 0; j < W; j++)
				cpy[i][j] = select[i];
	}
	for (int j = 0; j < W; j++) {	// j��° �� �˻�
		int cnt = 1;	// Ư���� ���ӵǴ� Ƚ��
		for (int i = 1; i < D; i++) {	// i��° �� �˻�
			if (cpy[i][j] == cpy[i - 1][j]) {	// ���� ��� Ư���� ����
				cnt++;
				if (cnt == K)	// j�� �հ� ���� ���
					break;
			}
			else	// Ư���� ���ӵ��� ����
				cnt = 1;	// �ٽ� ī��Ʈ
		}
		if (cnt != K)	// j�� �հ� ���� �̴�
			return false;
	}
	return true;	// ��� ���� �հ� ���� ��� �� true ��ȯ
}

void go(int n, int num) {
	if (n == D) {
		if (validation())
			ans = min(ans, num);
		return;
	}
	if (ans == num)	return;	// ans���� �� ���� ������ �ʿ��� ��� �ߴ�
	select[n] = -1; go(n + 1, num);		// ��ǰ ���� ����
	select[n] = 0;  go(n + 1, num + 1);	// ��ǰ A ����
	select[n] = 1;  go(n + 1, num + 1);	// ��ǰ B ����
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		// �Էº�
		scanf("%d %d %d", &D, &W, &K);
		for (int i = 0; i < D; i++)
			for (int j = 0; j < W; j++)
				scanf("%d", &film[i][j]);
		// ó����
		ans = 2e9;
		go(0, 0);
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}