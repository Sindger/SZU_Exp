#include<iostream>
#include<queue>
#include<time.h>
#include<cstring>
#include<Windows.h>
#include<algorithm>
using namespace std;
#define INF INT32_MAX
#define Max 100000 
int matrix[1500][1500];
int deep[Max];
int con[Max];
struct node {
	int begin, end;
	int flow, next;
}edge[Max];
class graph {
	int e=0, v;
	int n, k, D, c;
	int start=1;
public:
	graph(){}
	void addegde(int begin, int end, int flow) {
		e++;
		edge[e].begin = begin;
		edge[e].end = end;
		edge[e].flow = flow;
		edge[e].next = con[begin];
		con[begin] = e;
	}
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
		memset(matrix, 0, sizeof(matrix));
		memset(con, 0, sizeof(con));
		for (int i = 2; i <= n + 1; i++) {
			if (matrix[1][i] == 0) {
				addegde(1, i, c);
				matrix[1][i] = e;
				addegde(i, 1, 0);
				matrix[i][1] = e;
			}
			else
				edge[matrix[1][i]].flow += c;
		}
		for (int i = 2; i <= n + 1; i++) {
			for (int j = 2 + n; j <= n + k + 1; j++) {
				if (matrix[i][j] == 0) {
					addegde(i, j, 1);
					matrix[i][j] = e;
					addegde(j, i, 0);
					matrix[j][i] = e;
				}
				else
					edge[matrix[i][j]].flow = 1;
			}
		}
		for (int i = 2 + n; i <= k + 1 + n; i++) {
			if (matrix[i][v] == 0) {
				addegde(i, v, D);
				matrix[i][v] = e;
				addegde(v, i, D);
				matrix[v][i] = e;
			}
			else
				edge[matrix[i][v]].flow = 1;
		}
		int all = k * D;
		int maxflow = 0;
		double RunTime;
		_LARGE_INTEGER StartTime;	//开始时间
		_LARGE_INTEGER EndTime;	//结束时间
		double dqFreq;		//计时器频率
		LARGE_INTEGER f;	//计时器频率
		QueryPerformanceFrequency(&f);
		dqFreq = (double)f.QuadPart;
		QueryPerformanceCounter(&StartTime);	//计时开始
		while (bfs()) {
			maxflow += dfs(start, INF);
		}
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
	bool bfs() {
		memset(deep, 0, sizeof(deep));
		deep[start] = 1;
		queue<int>q;
		q.push(start);
		while (!q.empty()) {
			int front = q.front();
			q.pop();
			for (int i = con[front]; i != 0; i = edge[i].next) {
				int end = edge[i].end;
				if (deep[end] == 0 && edge[i].flow != 0) {
					deep[end] = deep[front] + 1;
					if (end == v) {
						return true;
					}
					q.push(end);
				}
			}
		}
		if (deep[v] != 0)
			return true;
		return false;
	}
	int dfs(int begin, int flow) {
		if (begin == v)
			return flow;
		int sum = 0;
		int right = flow;
		for (int i = con[begin]; i != 0 && right != 0; i = edge[i].next) {
			int end = edge[i].end;
			if (deep[end] == deep[begin] + 1 && edge[i].flow != 0) {
				int key = dfs(end, min(right, edge[i].flow));
				if (key == 0)
					deep[end] = 0;
				edge[i].flow -= key;
				edge[i + 1].flow += key;
				right -= key;
				sum += key;
			}
		}
		return sum;
	}
};
int main() {
	graph G;
	G.test();
}