#include<iostream>
#include<fstream>
using namespace std;
const int MapNum=500;
class Map {
public:
	int len;
	int** matrix, * color;
	int colornum;
	int ans = 0;
	Map() {}
	void test() {
		matrix = new int* [10];
		for (int i = 0; i < 10; i++)
			matrix[i] = new int[10];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				matrix[i][j] = 0;
			}
		}
		color = new int[10];
		for (int i = 1; i < 10; i++) {
			color[i] = 0;
		}
		matrix[1][2] = 1;
		matrix[1][5] = 1;
		matrix[1][6] = 1;

		matrix[2][1] = 1;
		matrix[2][3] = 1;
		matrix[2][5] = 1;
		matrix[2][6] = 1;

		matrix[3][2] = 1;
		matrix[3][4] = 1;
		matrix[3][6] = 1;
		matrix[3][7] = 1;

		matrix[4][3] = 1;
		matrix[4][7] = 1;
		matrix[4][9] = 1;

		matrix[5][1] = 1;
		matrix[5][2] = 1;
		matrix[5][6] = 1;

		matrix[6][1] = 1;
		matrix[6][2] = 1;
		matrix[6][3] = 1;
		matrix[6][5] = 1;
		matrix[6][7] = 1;
		matrix[6][8] = 1;

		matrix[7][3] = 1;
		matrix[7][4] = 1;
		matrix[7][6] = 1;
		matrix[7][8] = 1;
		matrix[7][9] = 1;

		matrix[8][6] = 1;
		matrix[8][7] = 1;
		matrix[8][9] = 1;

		matrix[9][4] = 1;
		matrix[9][7] = 1;
		matrix[9][8] = 1;
		dfs_test(1);
		cout << "Answer:" << ans << endl;
	}
	bool check_test(int x) {
		for (int i = 0; i <= 9; i++) {
			if (matrix[x][i] == 1 && color[i] == color[x])
				return false;
		}
		return true;
	}
	void dfs_test(int x) {
		if (x > 9) {
			ans++;//找到解法
			return;//回溯，继续查找解
		}
		for (int i = 1; i <= 4; i++) {
			color[x] = i;
			if (check_test(x))
				dfs_test(x + 1);//向下拓展
			color[x] = 0;//颜色归位
		}
	}
	void show() {
		cout << "Answer:" << ans << endl;
	}
};
int main() {
	clock_t startTime, endTime;
	Map M;
	startTime = clock();
	M.test();
	endTime = clock();
	int time = endTime - startTime;
	cout << "Run Time:" << time << "ms" << endl;
}