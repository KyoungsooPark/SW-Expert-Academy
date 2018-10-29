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

		// �Էº�
		scanf("%d %d", &n, &k);
		cin >> str;

		// ó����
		// ù ��° ������ ���������� �� ��° 16�������� �̾� ����
		for (int i = 0; i < (n / 4) - 1; i++)
			str += str.at(i);
		
		// ��� ������ 16������ 10������ ��ȯ�Ͽ� ����
		for (int i = 0; i < n; i++)
			v.push_back(stol(str.substr(i, n / 4), nullptr, 16));
		
		// �������� ����
		//sort(v.begin(), v.end(), greater<int>());
		sort(v.begin(), v.end(), desc);

		// �ߺ��� ���ڸ� �����ϰ� ī��Ʈ�Ͽ� �ش� ���� ��ȯ
		for (int i = 0, j = 0; j < v.size(); j++) {
			if (v[j] != temp) {
				temp = v[j];
				i++;
			}
			if (i == k)
				break;
		}

		// ��º�
		printf("#%d %d\n", t, temp);
	}

	return 0;
}