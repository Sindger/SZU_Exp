#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<fstream>
using namespace std;
ofstream fout("data.txt");
struct point{
	double x;
	double y;
	void setpoint(double xx, double yy) {
		x = xx;
		y = yy;
	}
};
double get_x(point& A, point& B) {
	return A.x - B.x;
}
double get_y(point& A, point& B) {
	return A.y - B.y;
}
double pointdistance(point& A, point& B) {
	return pow(get_x(A, B), 2) + pow(get_y(A, B), 2);
}
bool cmp(point a, point b) {
	return a.x < b.x;
}
double cloestPoint(point* points, int n) {
	double PointDist, MinDist = INT32_MAX;
	double x1, x2, y1, y2;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			PointDist = (points[i].x-points[j].x)* (points[i].x - points[j].x)+ (points[i].y - points[j].y)* (points[i].y - points[j].y);
			if (PointDist < MinDist) {
				MinDist = PointDist;
				x1 = points[i].x;
				y1 = points[i].y;
				x2 = points[j].x;
				y2 = points[j].y;
			}
		}
	}
	fout << endl << "数据个数：" << n << endl;
	fout << "最近点对为：(" << x1 << "," << y1 << ")  (" << x2 << "," << y2 << ")" << endl;      //输出坐标
	return MinDist;
}
double DCP(point* points, int n, point& a, point& b) {
	point a1, a2, b1, b2;
	double Dis;
	double d1, d2;
	if (n == 1)
		return INT32_MAX;
	if (n == 2) {
		a = points[0];
		b = points[1];
		return sqrt(pointdistance(points[0], points[1]));
	}
	point* p1 = new point[n];
	point* p2 = new point[n];
	int flag = 0;
	sort(points, points + n, cmp);
	double Xmid = points[(n - 1) / 2].x;
	for (int i = 0; i < n / 2; i++)
		p1[i] = points[i];
	for (int i = n / 2; i < n; i++)
		p2[flag++] = points[i];
	d1 = DCP(p1, n / 2, a1, b1);
	d2 = DCP(p2, n - n / 2, a2, b2);
	if (d1 < d2) {
		Dis = d1;
		a = a1; b = b1;
	}
	else {
		Dis = d2;
		a = a2; b = b2;
	}
	point* p3 = new point[n];
	int tmp = 0;
	for (int i = 0; i < n; i++) {
		if (abs(points[i].x - Xmid) <= Dis)
			p3[tmp++] = points[i];
	}
	for (int i = 0; i < tmp; i++) {
		for (int j = i + 1; j <= i + 6, j < tmp; j++) {
			if (pointdistance(p3[i], p3[j]) < Dis) {
				Dis = pointdistance(p3[i], p3[j]);
				a = p3[i];
				b = p3[j];
			}
		}
	}
	return Dis;
}
int main() {
	double x[100], y[100];
	double minDis;
	for (int i = 1; i <= 10; i++) {
		int PointNum = i*10000;
		point* points = new point[PointNum];
		for (int j = 0; j < PointNum; j++) {
			double x = rand();
			double y = rand();
			points[j].setpoint(x, y);
			for (int k = 0; k < j; k++) {
				if (points[j].x == points[k].x && points[j].y == points[k].y) {
					j--;
					break;
				}
			}
		}
		point a, b;
		clock_t StartTime, EndTime;
		StartTime = clock();
		minDis = DCP(points, PointNum, a, b);
		//minDis = cloestPoint(points, PointNum);
		EndTime = clock();
		double RunTime = EndTime - StartTime;
		fout << "数据个数：" << PointNum << endl;
		fout << "最近点对为：" << "(" << a.x << "," << a.y << ")与(" << b.x << "," << b.y << ")" << endl;
		fout << "距离为：" << sqrt(minDis) << endl;
		fout << "算法执行时间：" << RunTime << "ms" << endl<<endl;
	}
	return 0;
}