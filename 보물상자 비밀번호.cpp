/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo&categoryId=AWXRUN9KfZ8DFAUo&categoryType=CODE
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

bool desc(int a, int b) {
	return a > b;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, k, temp = 0;
		string str;
		vector<int> v;

		// 입력부
		scanf("%d %d", &n, &k);
		cin >> str;

		// 처리부
		// 첫 번째 조합의 마지막에서 두 번째 16진수까지 이어 붙임
		for (int i = 0; i < (n / 4) - 1; i++)
			str += str.at(i);
		
		// 모든 조합의 16진수를 10진수로 변환하여 저장
		for (int i = 0; i < n; i++)
			v.push_back(stol(str.substr(i, n / 4), nullptr, 16));
		
		// 내림차순 정렬
		//sort(v.begin(), v.end(), greater<int>());
		sort(v.begin(), v.end(), desc);

		// 중복된 숫자를 제외하고 카운트하여 해당 숫자 반환
		for (int i = 0, j = 0; j < v.size(); j++) {
			if (v[j] != temp) {
				temp = v[j];
				i++;
			}
			if (i == k)
				break;
		}

		// 출력부
		printf("#%d %d\n", t, temp);
	}

	return 0;
}