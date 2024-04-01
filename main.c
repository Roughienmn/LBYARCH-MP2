//x86-64 floating point caller program
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX 100.0f

void fillDoubleArray(double* a, int n) {
	for (int i = 0; i < n; i++) {
		a[i] = ((double)(rand() % (RAND_MAX * 100)) / RAND_MAX);
		//a[i] = ((float)rand() / (float)(RAND_MAX)) * MAX;
		//a[i] = (int)(a[i] * MAX) / MAX;
	}
}

extern void daxpy_c(int n, double A, double* X, double* Y, double* Z);
extern void daxpy_asm(int n, double A, double* X, double* Y, double* Z);

void printOutput(int n, double A, double* X, double* Y, double* Z_asm, double* Z_c, int exp) {
	printf("n: 2^%d (%d)\n", exp, n);
	printf("A: %f\n", A);
	printf("Array X:\n%f", X[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %f", X[i]);
	}
	printf("\n");

	printf("Array Y:\n%f", Y[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %f", Y[i]);
	}
	printf("\n");

	printf("Array Z_c:\n%f", Z_c[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %f", Z_c[i]);
	}
	printf("\n");

	printf("Array Z_asm:\n%f", Z_asm[0]);
	for (int i = 1; i < 10; i++) {
		printf(", %f", Z_asm[i]);
	}
	printf("\n");
}

void printTime(double* T_c, double* T_asm, int j, double acc) {
	int i;
	double cAve = 0;
	double asmAve = 0;
	double aveDiff = 0;

	printf("Time (C): %.2f", T_c[0]);

	for (i = 1; i < j; i++) {
		printf(", %.2fms", T_c[i]);
		cAve += T_c[i];
	}
	cAve /= j;
	
	printf("\nTime (Asm): %.2f", T_asm[0]);
	for (i = 1; i < j; i++) {
		printf(", %.2fms", T_asm[i]);
		asmAve += T_asm[i];
	}
	asmAve /= j;
	printf("\nAverage Time (C): %.2fms", cAve);
	printf("\nAverage Time (Asm): %.2fms", asmAve);

	aveDiff = ((asmAve - cAve) / (cAve + asmAve)) * 100;
	double absAve = abs(aveDiff);

	printf("\nTime Difference: %.2f%%", absAve);
	if (aveDiff > 0) {
		printf(" increase in time from C to Assembly");
	}
	else if (aveDiff < 0) {
		printf(" decrease in time from C to Assembly");
	}

	printf("\nAccuracy: %.0f%%\n\n\n", acc);
}

double runKernel(int n, double* T_c, double* T_asm, int Index, double A, double* X, double* Y, double* Z_c, double* Z_asm) {
	double acc = 0;
	double total = 0;
	int i;

	double startTime;
	double endTime;

	startTime = clock(NULL);
	daxpy_c(n, A, X, Y, Z_c);
	endTime = clock(NULL);
	T_c[Index] = endTime - startTime;

	startTime = clock(NULL);
	daxpy_asm(n, A, X, Y, Z_asm);
	endTime = clock(NULL);
	T_asm[Index] = endTime - startTime;

	for (i = 0; i < n; i++) {
		acc += abs(Z_c[i] - Z_asm[i]);
		total += Z_c[i];
	}
	acc = ((total - acc) / total) * 100;

	return acc;
}

void runTests(int n, int exp) {
	int j = 30;
	int i = 1;
	double acc = 0;

	double A = 2.0;
	double* X, * Y, * Z_c, * Z_asm;

	X = (double*)malloc(n * sizeof(double));
	Y = (double*)malloc(n * sizeof(double));
	Z_c = (double*)malloc(n * sizeof(double));
	Z_asm = (double*)malloc(n * sizeof(double));

	fillDoubleArray(X, n);
	fillDoubleArray(Y, n);

	double* T_c = (double*)malloc(n * sizeof(double));
	double* T_asm = (double*)malloc(n * sizeof(double));
	
	for (i = 0; i < j; i++) {
		acc += runKernel(n, T_c, T_asm, i, A, X, Y, Z_c, Z_asm);
	}
	acc /= j;
	printOutput(n, A, X, Y, Z_asm, Z_c, exp);
	printf("\n");
	printTime(T_c, T_asm, j, acc);
}

int initializeN(int exp) {
	int n = 1;
	int i;
	for (i = 0; i < exp; i++) {
		n *= 2;
	}

	return n;
}

int main() {
	int i;
	int exp;
	int n;

	for (i = 0; i < 3; i++) {
		exp = 20 + i * 4;
		n =	initializeN(exp);
		runTests(n, exp);
	}

	return 0;
}