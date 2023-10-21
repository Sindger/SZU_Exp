#include<iostream> 
#include<fstream>
#include<map> 
using namespace std;
const int deep = 420;
const int depth = 450; 
int** arr, * color, ** connect, * degree, * path;
int type, len, sum, way;
map<int, int> points;
int check(int step) {
	for (int i = 0; i < step; i++)
		if (arr[step][i] && color[step] == color[i])
			return -1;
	return 1;
}
void show_nect() {
	for (int i = 0; i < len; i++) {
		int tmplen = degree[i];
		for (int j = 0; j < tmplen; j++)
			cout << connect[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}
int update(int loc) {
	int none_color = 0;
	int tmplen = points[loc][0].degree;
	int now_color = points[loc][0].color;
	int pos;
	int id = points[loc][0].id;

	for (int j = 0; j < tmplen; j++) {
		pos = connect[id][j];
		if (points[pos][0].color != -1)
			continue;

		points[pos][0].cl[now_color]++;

		if (points[pos][0].cl[now_color] == 1) {
			points[pos][0].avail--;

			if (points[pos][0].avail < 1)
				none_color++;
		}
	}
	return none_color;
}
void set_path() {
	map<int, int>::iterator it, end;
	end = points.end();

	for (it = points.begin(); it != end; it++)
		path[it->second] = it->first;

	int next = deep;
	for (int i = 0; i < len; i++) {
		if (points.find(i) == points.end()) {
			points[i] = next;
			path[next++] = i;
		}
	}
}

void DFS(int step, int start) {	
	int tmpcolor;
	if (step >= depth) {
		sum++;
		show_color();
	}
	else {
		int parent_pos = path[step - 1];
		int now_pos = path[step];

		for (int i = 0; i < type; i++) {
			tmpcolor = (start + i) % type;
			if (arr[parent_pos][now_pos] && tmpcolor == color[parent_pos])
				continue;

			color[now_pos] = tmpcolor;
			if (check(now_pos) != -1) {
				DFS(step + 1, tmpcolor + 1);
			}

			color[now_pos] = -1;
			if (sum > 0)
				return;
		}
	}
}

void init() {
	ifstream file;
	file.open("E:\\Experiment\\算法\\算法3\\地图数据\\le450_1.txt");
	cout << "opening\n";

	int time;
	file >> len >> time >> type;

	arr = new int* [len];
	connect = new int* [len];
	color = new int[len];
	degree = new int[len];
	path = new int[len];
	sum = 0; way = 0;

	for (int i = 0; i < len; i++) {
		arr[i] = new int[len];
		connect[i] = new int[len];
		for (int j = 0; j < len; j++)
			arr[i][j] = 0;

		degree[i] = 0;
		path[i] = 0;
		color[i] = -1;
	}

	cout << "reading\n";
	for (int i = 0; i < time; i++) {
		int p1, p2;
		file >> p1 >> p2;
		p1--; p2--;
		//			cin>>p1>>p2;
		arr[p1][p2] = 1;
		arr[p2][p1] = 1;

		connect[p1][degree[p1]] = p2;
		connect[p2][degree[p2]] = p1;
		degree[p2]++;
		degree[p1]++;
	}
	cout << "read finished\n";
	file.close();
}

void find(int step, int pos) {
	if (step >= deep) {
		way++;
		set_path();
		show_set();
	}
	else {
		int tmplen = degree[pos];
		for (int i = 0; i < tmplen; i++) {
			int next = connect[pos][i];

			if (points.find(next) == points.end()) {
				points[next] = step;
				find(step + 1, next);

				points.erase(next);
			}
			else
				continue;

			if (way > 0)
				return;
		}
	}
}

void test() {
	init();

	points[0] = 0;
	find(1, 0);

	color[0] = 0;
	DFS(1, 1);
}
int main()
{
	test();
	return 0;
}