#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

string str;
map<string, bool> check[11];	// �湮 ���� üũ
int N, ans;

void go(int n) {
	if (n == N) {
		ans = max(ans, stoi(str));
		return;
	}
	for (int i = 0; i < str.size() - 1; i++) {
		for (int j = i + 1; j < str.size(); j++) {
			swap(str[i], str[j]);
			if (!check[n + 1].count(str)) {	// n + 1ȸ ��ȯ���� str�� �湮�� ���� ���� ���
				check[n + 1][str] = true;
				go(n + 1);	// ���� �� ���� ��ȯ ����
			}
			swap(str[i], str[j]);
		}
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> str >> N;
		ans = 0;
		go(0);
		cout << "#" << t << " " << ans << endl;
	}
	return 0;
}