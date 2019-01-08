#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

string str;
map<string, bool> check[11];	// 방문 여부 체크
int N, ans;

void go(int n) {
	if (n == N) {
		ans = max(ans, stoi(str));
		return;
	}
	for (int i = 0; i < str.size() - 1; i++) {
		for (int j = i + 1; j < str.size(); j++) {
			swap(str[i], str[j]);
			if (!check[n + 1].count(str)) {	// n + 1회 교환으로 str을 방문한 적이 없는 경우
				check[n + 1][str] = true;
				go(n + 1);	// 적용 후 다음 교환 진행
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