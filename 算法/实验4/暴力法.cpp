#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;
int sum = 0;
int MaxCoins(int l, int r, vector<int>coins) {
	if (r - l == 0)
		return coins[r];
	int L = coins[l] - MaxCoins(l + 1, r, coins);
	int R = coins[r] - MaxCoins(l, r - 1, coins);
	if (L > R)
		return L;
	return R;
}
int main() {
	int n;
	cin >> n;
	for (int j = 0; j < 20; j++) {
		vector<int>coins;
		for (int i = 0; i < n; i++) {
			int num = rand() % 100;
			if (num == 0) {
				i--;
				continue;
			}
			else {
				sum += num;
				coins.push_back(num);
			}
		}
		_LARGE_INTEGER StartTime, EndTime, f;
		double F;
		QueryPerformanceFrequency(&f);
		F = (double)f.QuadPart;
		QueryPerformanceCounter(&StartTime);
		int ans = MaxCoins(0, n - 1, coins);
		int A = (sum + ans) / 2;
		int B = sum - A;
		QueryPerformanceCounter(&EndTime);
		int RunTime = 1000000 * (EndTime.QuadPart - StartTime.QuadPart) / F;
		if (ans >= 0)
			cout << "A is winner" << endl;
		else
			cout << "B is winner" << endl;
		cout << "A gets" << A << "coins" << endl;
		cout << "B gets" << B << "coins" << endl;
		cout << "Run Time:" << RunTime << "us" << endl;
		cout << endl;
	}
}