#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
int Left[100000], Right[100000];
int Intmax = INT_MAX;
void print(vector<int>num, int n) {
	for (int i = 0; i < n; i++) {
		cout << num[i] << " ";
	}
	cout << endl;
}
void bubblesort(vector<int>num, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n - i; j++) {
			if (num[j] < num[j - 1]) {
				swap(num[j], num[j - 1]);
			}
		}
	}
}
void insertsort(vector<int>num, int n) {
	for (int i = 1; i < n; i++) {
		int key = num[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (num[j] > key)
				num[j + 1] = num[j];
			else
				break;
		}
		num[j + 1] = key;
	}
}
void selectsort(vector<int>num, int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (num[j] < num[min])
				min = j;
		}
		swap(num[i], num[min]);
	}
}
void merge(vector<int>num, int n, int left, int mid, int right)
{
	int n1 = mid - left, n2 = right - mid;
	for (int i = 0; i < n1; i++)
		Left[i] = num[left + i];
	for (int i = 0; i < n2; i++)
		Right[i] = num[mid + i];
	Left[n1] = Right[n2] = Intmax;
	int i = 0, j = 0;
	for (int k = left; k < right; k++)
	{
		if (Left[i] <= Right[j])
			num[k] = Left[i++];
		else
			num[k] = Right[j++];
	}
}
void mergesort(vector<int>num, int n, int left, int right) {
	if (left + 1 < right)
	{
		int mid = (left + right) / 2;
		mergesort(num, n, left, mid);
		mergesort(num, n, mid, right);
		merge(num, n, left, mid, right);
	}
}
void quicksort(vector<int>num, int left, int right) {
	if (left > right)
		return;
	int tmp = num[left];
	int i = left;
	int j = right;
	while (i != j) {
		while (num[j] >= tmp && j > i)
			j--;
		while (num[i] <= tmp && j > i)
			i++;
		if (j > i)
			swap(num[i], num[j]);
	}
	num[left] = num[i];
	num[i] = tmp;
	quicksort(num, left, i - 1);
	quicksort(num, i + 1, right);
}
int main() {
	int n;
	int random = 123456;
	ofstream fout("data.txt");
	cin >> n;
	int number = 20;
	while (number--) {
		for (int i = 1; i <= n; i++) {
			int Num = i * 10000;
			int random = rand();   //�������ȡ����
			vector<int>num;        //�������
			for (int j = 0; j < Num; j++)
				num.push_back(rand() % random);  //���ɴ���������
			clock_t startTime, endTime;
			startTime = clock();  //����ʼʱ��
			bubblesort(num, Num);
			endTime = clock();   //�������ʱ��
			double t1 = (double)(endTime - startTime);
			startTime = clock();
			insertsort(num, Num);
			endTime = clock();
			double t2 = (double)(endTime - startTime);
			startTime = clock();
			mergesort(num, Num, 0, Num);
			endTime = clock();
			double t3 = (double)(endTime - startTime);
			startTime = clock();
			selectsort(num, Num);
			endTime = clock();
			double t4 = (double)(endTime - startTime);
			startTime = clock();
			quicksort(num, 0, Num - 1);
			endTime = clock();
			double t5 = (double)(endTime - startTime);
			fout << "ð������" << i << ": " << t1 << endl;
			fout << "��������" << i << ": " << t2 << endl;
			fout << "�ϲ�����" << i << ": " << t3 << endl;
			fout << "ѡ������" << i << ": " << t4 << endl;
			fout << "��������" << i << ": " << t5 << endl;
		}
	}
}