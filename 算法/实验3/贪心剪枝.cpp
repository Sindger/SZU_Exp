#include<iostream>
#include<fstream>
#include<map>
using namespace std;

const int deep = 250;
typedef struct point {
    int id,degree;
    int *cl;	//	颜色邻接数组，颜色为索引值，存每个颜色的同色相邻点数量
    int avail;	//	剩余可着色方案
    int color;	//	自身颜色
    point(int color_num,int pos) {	//	构造
        cl = new int[color_num];
        for (int i = 0; i < color_num; i++){
            cl[i] = 0; //  默认为0，表示该颜色在相邻点中出现0次
        }
		id = pos;
        color = -1;
        avail = color_num;	//	剩余颜色初始化为颜色总数
		degree = 0;
    }
}matrix;

int len, type, sum;
int* rank;
int** arr;
int** connect;
matrix** points;
map<int, int> path;

void show_nect() {
	for (int i = 0; i < n; i++) {
		int flag = tree[i];
		for (int j = 0; j < flag; j++)
			cout << connect[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

void show_set() {
	for (int i = 0; i < n; i++) {
		cout << path[i] << ' ';
		if ((i + 1) % 25 == 0)
			cout << endl;
	}
	cout << endl;
}
void path() {
	map<int, int>::iterator it, end;
	end = points.end();
	for (it = points.begin(); it != end; it++)
		path[it->second] = it->first;
	int next = deep;
	for (int i = 0; i < n; i++) {
		if (points.find(i) == points.end()) {
			points[i] = next;
			path[next++] = i;
		}
	}
}

void init() {
	ifstream file;
	file.open("E:\\Experiment\\算法\\算法3\\地图数据\\le450_1.txt");
	cout << "reading" << endl;;

	int time;
	file >> len >> time >> type;
	//type =20;

	rank = new int[len];
	arr = new int* [len];
	connect = new int* [len];
	points = new matrix * [len];
	sum = 0;

	for (int i = 0; i < len; i++) {
		arr[i] = new int[len];
		connect[i] = new int[len];
		points[i] = new matrix(type, i);
		rank[i] = 0;

		for (int j = 0; j < len; j++) {
			arr[i][j] = 0;
			connect[i][j] = -1;
		}
	}

	cout << "reading" << endl;
	for (int i = 0; i < time; i++) {
		int p1, p2;
		file >> p1 >> p2;
		p1--; p2--;
		arr[p1][p2] = 1;
		arr[p2][p1] = 1;

		connect[p1][points[p1][0].degree] = p2;
		connect[p2][points[p2][0].degree] = p1;
		points[p1][0].degree++;	//	
		points[p2][0].degree++;
	}
	cout << "read finished" << endl;
	file.close();

}
void show_rank() {
	for (int i = 0; i < deep; i++) {
		cout << i << " : id: " << points[i][0].id << " degree: " << points[i][0].degree << ' ' << "follow :";
		int tmplen = points[i][0].degree;
		int tmppos = points[i][0].id;
		for (int j = 0; j < tmplen; j++)
			cout << connect[tmppos][j] << ' ';
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < len; i++) {
		cout << rank[i] << ' ';
		if ((i + 1) % 25 == 0)
			cout << endl;
	}
	cout << endl;
}

void show_nect() {
	for (int i = 0; i < len; i++) {
		int tmplen = points[i][0].degree;
		cout << i << " : " << tmplen << " next: ";
		cout << " cl:" << points[i][0].avail << endl;;
	}
}

void show_sol() {
	for (int i = 0; i < deep; i++) {
		cout << points[i][0].color << ' ';
		if ((i + 1) % 15 == 0)
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

void getback(int loc) {
	int tmplen = points[loc][0].degree;
	int now_color = points[loc][0].color;
	int pos;
	int id = points[loc][0].id;

	for (int i = 0; i < tmplen; i++) {
		pos = connect[id][i];
		if (points[pos][0].color != -1)
			continue;
	}
}

int dfs(int step, int pos) {
	if (step >= deep) {
		sum++;
		show_sol();
		return 1;
	}
	else {
		if (points[pos][0].avail == 0)
			return 0;

		for (int i = 0; i < type; i++) {
			int tmp_color = i;
			if (points[pos][0].cl[tmp_color])
				continue;

			points[pos][0].color = tmp_color;
			path[pos] = step;
			int flg = update(pos);
			if (flg) {
				getback(pos);
				points[pos][0].color = -1;
				path.erase(pos);
				continue;
			}

			int tmplen = points[pos][0].degree;
			int min_avail = type + 1;
			int min_index = -1;
			for (int j = 0; j < tmplen; j++) {
				int index = connect[pos][j];
				if (points[index][0].color == -1 && points[index][0].avail < min_avail) {
					min_index = index;
					min_avail = points[index][0].avail;
				}
			}

			if (min_avail == -1) {
				for (int j = 0; j < len; j++)
					if (points[j][0].color == -1) {
						dfs(step + 1, j);
						break;
					}
			}
			else
				flg = dfs(step + 1, min_index);

			getback(pos);
			points[pos][0].color = -1;
			path.erase(pos);
		}
	}
}

void test() {
	init();

	points[0][0].color = 0;
	update(0);

	int next = connect[0][0];

	dfs(1, next);
	cout << "sum : " << sum << endl;
}

int main()
{
	test();
    return 0;
}


