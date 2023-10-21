#include<iostream>
#include<queue>
#include<vector>
#include<windows.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
class node {
public:
	int flag;//连通标识
	int data;
	node* next;
	node* edge;//对称边指针
	node() {
		flag = 0;
		data = -1;
		next = NULL;
		edge = NULL;
	}
	node(int n) {
		flag = 1;
		data = n;
		next = NULL;
		edge = NULL;
	}
};
class graph{
	int* tree;
	int n, e;
	int* depth;
	int* circle;
	int cir, repeat;
	node** list;//邻接矩阵储存
	vector<vector<int>>bridge;//存储桥的信息
public:
	graph(){}
	void init() {
		/*streambuf* backin = cin.rdbuf();
		ifstream file("C:/Users/Sindger/Desktop/largeG.txt");
		cin.rdbuf(file.rdbuf());*/
		cin >> n >> e;
		list = new node * [n + 2];
		tree = new int[n + 2];
		depth = new int[n + 2];
		circle = new int[n + 2];
		for (int i = 0; i < n; i++) {
			list[i] = new node(i);
			tree[i] = -1;
			depth[i] = 1;
			circle[i] = 0;
		}
		/*for (int i = 1; i <= n; i++) {
			cout << list[i]->data << endl;
		}*/
		int x, y;
		for (int i = 0; i < e; i++) {
			x = (RAND_MAX * rand() + rand()) % n;
			y = (RAND_MAX * rand() + rand()) % n;
			if (x == y) {
				cir++;
				continue;
			}
			int flg = create(x, y);
			if (flg) {
				repeat++;
				continue;
			}
			create(y, x);
			setedge(x, y);
		}
		/*cin.rdbuf(backin);
		file.close();
		cout << "Read file finished" << endl;*/
	}
	void setedge(int x,int y) {
		node* head1 = new node();
		head1 = list[x];
		while (head1->next != NULL) {
			head1 = head1->next;
		}
		node* head2 = new node();
		head2 = list[y];
		while (head2->next != NULL) {
			head2 = head2->next;
		}
		head1->edge = head2;
		head2->edge = head1;
		head1->edge->next = NULL;
		head2->edge->next = NULL;
	}
	int create(int x, int y) {
		node* head = new node();
		head = list[x];
		while (head->next!=NULL) {
			if (head->data==y)
				return 1;
			head = head->next;
		}
		if (head->data == y)
			return 1;
		node* p = new node();
		p->data = y;
		p->flag = 1;
		p->next = NULL;
		head->next = p;
		return 0;
	}
	void createTree() {
		for (int i = 0; i < n; i++) {
			if (tree[i] == -1) {
				tree[i] = i;
				BFS_quickly(i);
			}
		}
	}
	void BFS_quickly(int pos) {
		tree[pos] = pos;
		queue<int>q;
		q.push(pos);
		while (!q.empty()) {
			int par = q.front();
			q.pop();
			node* p = list[par]->next;
			while (p) {
				int tmp = p->data;
				if (tree[tmp] == -1) {
					q.push(tmp);
					tree[tmp] = par;
					depth[tmp] = depth[par] + 1;
					p->flag = 0;
					if (p->edge)
						p->edge->flag = 0;
				}
				p = p->next;
			}
		}
	}
	void count_quickly() {
		int Union = 0, cur = 0;
		int depth1, depth2;
		_LARGE_INTEGER StartTime, EndTime, f;//计时器
		double F;
		QueryPerformanceFrequency(&f);
		F = (double)f.QuadPart;
		QueryPerformanceCounter(&StartTime);
		for (int i = 0; i < n; i++) {
			node* p = list[i]->next;
			while (p) {
				int child = p->data;
				if (p->flag == 1) {
					p->flag = 2;
					if(p->edge)
						p->edge->flag = 2;
					Union++;
					depth1 = depth[i];
					depth2 = depth[child];
					int tmppar1 = i, tmppar2 = child;
					while (depth1 > depth2) {
						if (!circle[tmppar1]) {
							cur++;
							circle[tmppar1] = 1;
						}
						tmppar1 = tree[tmppar1];
						depth1--;
					}
					while (depth1 < depth2) {
						if (!circle[tmppar2]) {
							cur++;
							circle[tmppar2] = 1;
						}
						tmppar2 = tree[tmppar2];
						depth2--;
					}
					while (tmppar1 != tmppar2) {
						if (!circle[tmppar1]) {
							cur++;
							circle[tmppar1] = 1;
						}
						if (!circle[tmppar2]) {
							cur++;
							circle[tmppar2] = 1;
						}
						tmppar1 = tree[tmppar1];
						tmppar2 = tree[tmppar2];
					}
				}
				p = p->next;
			}
		}
		QueryPerformanceCounter(&EndTime);
		int RunTime = 1000000 * (EndTime.QuadPart - StartTime.QuadPart) / F;
		cout << "All Edges:" << e << endl << "Repeat:" << repeat << endl << "Circle:" << cir << endl
			<< "Not in tree:" << Union << endl << "Cur:" << cur << endl << "Result:"
			<< e - repeat - cir - Union - cur << endl;
		cout << "Run Time:" << RunTime << "us" << endl;
	}
	void print() {
		for (int i = 0; i < n; i++) {
			printlist(i);
			cout << endl;
		}
	}
	void printlist(int line) {
		node* head = new node();
		head = list[line];
		while (head) {
			cout << head->data << " ";
			head = head->next;
		}
		cout << endl;
		head = list[line]->next;
		while (head) {
			cout << head->edge->flag << " ";
			head = head->next;
		}
		cout << endl;
	}
	/*void printbridge() {
		cout << "There are " << bridge.size() << " bridge." << endl;
		for (int i = 0; i < bridge.size(); i++) {
			cout << bridge[i][0] << " " << bridge[i][1] << endl;
		}
	}*/
};
int main() {
	int n, e;
	graph G;
	G.init();
	//G.print();  //检查邻接表的构建是否正确
	//G.test();
	G.createTree();
	G.count_quickly();
	//G.print();
	//G.printbridge();//打印桥的信息
}