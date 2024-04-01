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

void printOutput(int n, double A, double* X, double* Y, double* Z_asm, double* Z_c) {
	printf("n: %d\n", n);
	printf("A: %.2f\n", A);
	printf("Array X:\n%.2f", X[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %.2f", X[i]);
	}
	printf("\n\n");

	printf("Array Y:\n%.2f", Y[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %.2f", Y[i]);
	}
	printf("\n\n");

	printf("Array Z_c:\n%.2f", Z_c[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %.2f", Z_c[i]);
	}
	printf("\n\n");

	printf("Array Z_asm:\n%.2f", Z_asm[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %.2f", Z_asm[i]);
	}
	printf("\n\n");
}

void runKernel(int n) {
	double A = ((double)rand() / (double)(RAND_MAX)) * MAX;
	double* X, * Y, * Z_c, * Z_asm;
	X = (double*)malloc(n * sizeof(double));
	Y = (double*)malloc(n * sizeof(double));
	Z_c = (double*)malloc(n * sizeof(double));
	Z_asm = (double*)malloc(n * sizeof(double));

	fillDoubleArray(X, n);
	fillDoubleArray(Y, n);

	daxpy_c(n, A, X, Y, Z_c);
	daxpy_asm(n, A, X, Y, Z_asm);

	printOutput(n, A, X, Y, Z_asm, Z_c);
}

void runTests() {
	int n = 1073741824;
	int i = 1;
	for (i = 1; i <= n; i++) {
		runKernel(i);
		printf("\n");
	}
}

int main() {
	runTests();
}