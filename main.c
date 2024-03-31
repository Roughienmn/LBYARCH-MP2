//x86-64 floating point caller program
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 100.0f

void fillDoubleArray(double* a, int n) {
	for (int i = 0; i < n; i++) {
		//a[i] = ((double)(rand() % (RAND_MAX * 100)) / RAND_MAX);
		a[i] = ((float)rand() / (float)(RAND_MAX)) * MAX;
		a[i] = (int)(a[i] * MAX) / MAX;
	}
}

extern void daxpy_c(int n, double A, double* X, double* Y, double* Z);
extern void daxpy_asm(int n, double A, double* X, double* Y, double* Z);

int main() {
	int n = 20;
	double A = 2.0;
	double* X,* Y, * Z_c, * Z_asm;
	X = (double*)malloc(n * sizeof(double));
	Y = (double*)malloc(n * sizeof(double));
	Z_c = (double*)malloc(n * sizeof(double));
	Z_asm = (double*)malloc(n * sizeof(double));

	fillDoubleArray(X, n);
	fillDoubleArray(Y, n);

	daxpy_c(n, A, X, Y, Z_c);
	daxpy_asm(n, A, X, Y, Z_asm);

	printf("Array X:\n");
	for (int i = 0; i < n; i++) {
		printf("%.2f ", X[i]);
	}
	printf("\n");

	printf("Array Y:\n");
	for (int i = 0; i < n; i++) {
		printf("%.2f ", Y[i]);
	}
	printf("\n");

	printf("Array Z_c:\n");
	for (int i = 0; i < n; i++) {
		printf("%.2f ", Z_c[i]);
	}
	printf("\n");

	printf("Array Z_asm:\n");
	for (int i = 0; i < n; i++) {
		printf("%.2f ", Z_asm[i]);
	}
	printf("\n");

	return 0;
}