#include<iostream> 
#include<time.h>
#include<stdlib.h>
using namespace std;
int len, type, sum, num_child;
int** arr, * color;
int deep;
void init() {
	cin >> len >> num_child;
	arr = new int* [len];
	color = new int[len];
	sum = 0;
	type = 4;
	deep = len;

	for (int i = 0; i < len; i++) {
		arr[i] = new int[len];
		for (int j = 0; j < len; j++)
			arr[i][j] = 0;

		color[i] = -1;
	}
}

void show_arr() {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int check(int step) {
	for (int i = 0; i < step; i++)
		if (arr[step][i] && color[step] == color[i])
			return -1;
	return 1;
}
void get_graph(int depth, int par, int rank, int gap) {
	int child[num_child];
	int limi = (gap * num_child * num_child - 1) / (num_child - 1);
	int start = (gap * num_child - 1) / (num_child - 1);
	rank *= num_child;

	for (int i = 1; i <= num_child; i++)
		child[i - 1] = start + rank + i;

	for (int i = 0; i < num_child; i++) {
		if (child[i] > len)
			return;

		arr[par - 1][child[i] - 1] = 1;
		arr[child[i] - 1][par - 1] = 1;
		if (child[i] + 1 <= limi && child[i] < len) {

			arr[child[i] - 1][child[i]] = 1;
			arr[child[i]][child[i] - 1] = 1;
		}
		get_graph(depth + 1, child[i], rank + i, gap * num_child);
	}

}

void DFS(int step, int start) {	
	int tmpcolor;
	if (step >= deep) {
		sum++;
	}
	else
		for (int i = 0; i < type; i++) {
			tmpcolor = (start + i) % type; 
			color[step] = tmpcolor;
			if (check(step) != -1)
				DFS(step + 1, tmpcolor);
			color[step] = -1;
		}
}

void test() {
	init();
	get_graph(1, 1, 0, 1);
	//		show_arr();

	color[0] = 0;
	cout << "test times:\n";
	int times, cost = 0;
	int start, end;
	cin >> times;

	start = clock();
	color[0] = 0;
	while (times--) {
		sum = 0;
		DFS(1, 1);
	}
	end = clock();
	cost = end - start;
	cout << "cost : " << cost << " sum : " << sum << endl << endl;
}

int main()
{
	test();
	return 0;
}
