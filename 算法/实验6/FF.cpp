#include<iostream>
#include<queue>
#include<time.h>
#include<cstring>
#include<Windows.h>
#include<algorithm>
using namespace std;
#define INF INT32_MAX
#define Max 1500 
int matrix[Max][Max];
int visit[Max];
class graph {
	int e, v;
	int n, k, D, c;
public:
	graph(){}
	void test() {
		cout << "Please input the number of doctor:";
		cin >> n;
		cout << "Please input the number of holiday:";
		cin >> k;
		cout << "Please input the number of days in a holiday:";
		cin >> D;
		cout << "Please input the number of days a doctor can count:";
		cin >> c;
		v = 2 + n + k;
		e = n + k + n * k;
		for (int i = 2; i <= n + 1; i++)
			matrix[1][i] += c;
		for (int i = 2; i <= n + 1; i++) {
			for (int j = 2 + n; j <= n + k + 1; j++) {
				matrix[i][j] += 1;
			}
		}
		for (int i = 2 + n; i <= k + 1 + n; i++) {
			matrix[i][v] += D;
		}
		int all = k * D;
		int maxflow;
		double RunTime;
		_LARGE_INTEGER StartTime;	//开始时间
		_LARGE_INTEGER EndTime;	//结束时间
		double dqFreq;		//计时器频率
		LARGE_INTEGER f;	//计时器频率
		QueryPerformanceFrequency(&f);
		dqFreq = (double)f.QuadPart;
		QueryPerformanceCounter(&StartTime);	//计时开始
		maxflow = FF(1);
		QueryPerformanceCounter(&EndTime);	//计时结束
		RunTime = 1000000 * (EndTime.QuadPart - StartTime.QuadPart) / dqFreq;
		cout << "Max Flow:" << maxflow << endl;
		if (all <= maxflow) {
			cout << "There is at least one solution" << endl;
		}
		else{
			cout << "There is no solution" << endl;
		}
		cout << "Run Time:" << RunTime << "us" << endl;
	}
	int dfs(int start, int flow) {
		if (start == v)
			return flow;
		for (int i = 1; i <= v; i++) {
			if (matrix[start][i] > 0 && !visit[i]) {
				visit[i] = 1;
				int flag = dfs(i, min(flow, matrix[start][i]));
				if (flag > 0) {
					matrix[start][i] -= flag;
					matrix[i][start] += flag;
					return flag;
				}
			}
		}
		return 0;
	}
	int FF(int start) {
		int maxflow = 0;
		while (1) {
			for (int i = 0; i < Max; i++)
				visit[i] = 0;
			int res = dfs(start, INF);
			if (res == 0)
				return maxflow;
			maxflow += res;
		}
	}
};
int main() {
	graph G;
	G.test();
}