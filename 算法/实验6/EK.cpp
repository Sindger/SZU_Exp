#include<iostream>
#include<queue>
#include<time.h>
#include<cstring>
#include<Windows.h>
#include<algorithm>
using namespace std;
#define INF 0x7f7f7f7f
#define Max 1500
int matrix[Max][Max], flow[Max][Max];
int tree[Max], residual[Max];
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
		maxflow = EK(1, v);
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
	int EK(int start,int end) {
		int maxflow = 0;
		memset(flow, 0, sizeof(flow));
		memset(tree, 0, sizeof(tree));
		queue<int>q;
		while (1) {
			memset(residual, 0, sizeof(residual));
			residual[start] = INF;
			q.push(start);
			while (!q.empty()) {
				int front = q.front();
				q.pop();
				for (int i = 1; i <= end; i++) {
					if (!residual[i] && matrix[front][i] > flow[front][i]) {
						residual[i] = min(residual[front], matrix[front][i] - flow[front][i]);
						tree[i] = front;
						q.push(i);
					}
				}
			}
			if (residual[end] == 0)
				return maxflow;
			for (int step = end; step != start; step = tree[step]) {
				flow[tree[step]][step] += residual[end];
				flow[step][tree[step]] -= residual[end];
			}
			maxflow += residual[end];
		}
	}
};
int main() {
	graph G;
	G.test();
}