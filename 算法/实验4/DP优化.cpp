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
int DP(int** dp, vector<int>coins, int n) {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			int L = coins[i] - dp[i + 1][j];
			int R = coins[j] - dp[i][j - 1];
			if (L > R)
				dp[i][j] = L;
			else
				dp[i][j] = R;
		}
	}
	return dp[0][n-1];
}
int DP_Op(int* dp, vector<int>coins, int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			int L = coins[i] - dp[j];
			int R = coins[j] - dp[j - 1];
			if (L > R) {
				dp[j] = L;
			}
			else {
				dp[j] = R;
			}
		}
	}
	return dp[n - 1];
}
int main() {
	int n;
	cin >> n;
	for (int j = 0; j < 10; j++) {
		int* DP_ = new int[n+1];
		vector<int>coins;
		for (int i = 0; i < n; i++) {
			int num = rand() % 100;
			if (num == 0) {
				i--;
				continue;
			}
			else {
				DP_[i] = num;
				sum += num;
				coins.push_back(num);
			}
		}
		/*for (int i : coins)
			cout << i << " ";*/
		cout << endl;
		/*int** dp;
		dp = new int* [n + 2];
		for (int i = 0; i <= n + 2; i++)
			dp[i] = new int[n + 2];
		for (int i = 0; i < n; i++)
			dp[i][i] = coins[i];*/
		_LARGE_INTEGER StartTime, EndTime, f;
		double F;
		QueryPerformanceFrequency(&f);
		F = (double)f.QuadPart;
		QueryPerformanceCounter(&StartTime);
		int ans = DP_Op(DP_, coins, n);
		//int ans = DP(dp, coins, n);
		//int ans = MaxCoins(0, n - 1, coins);
		long int A = (sum + ans) / 2;
		long int B = sum - A;
		delete DP_;
		QueryPerformanceCounter(&EndTime);
		int RunTime = 1000000 * (EndTime.QuadPart - StartTime.QuadPart) / F;
		if (ans >= 0)
			cout << "A is winner" << endl;
		else
			cout << "B is winner" << endl;
		cout << "A gets " << A << " coins" << endl;
		cout << "B gets " << B << " coins" << endl;
		cout << "Run Time:" << RunTime << "us" << endl;
		cout << endl;
	}
}