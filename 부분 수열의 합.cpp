#include <cstdio>
using namespace std;

int arr[20];

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, k, ans = 0;
		// �Էº�
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		// ó����
		for (int i = 1; i < (1 << n); i++) {
			int temp = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					temp += arr[j];
					if (temp > k)	// ���� �ð��� ���̴� �ٽ�
						break;
				}
			}
			if (temp == k)
				ans++;
		}
		// ��º�
		printf("#%d %d\n", t, ans);
	}
	return 0;
}