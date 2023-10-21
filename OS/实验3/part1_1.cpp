#include <stdio.h>
#include <stdlib.h>
int main() {
	int* p;
	p = (int*)malloc(10*sizeof(int));
	double* q;
	q = (double*)malloc(10 * sizeof(double));
	printf("%d %d\n", _msize(p), _msize(q));
	free(p);
	free(q);
	printf("%d %d\n", _msize(p), _msize(q));
	return 0;
}