/**
 * @file mahojin.c
 * @brief The most foolproof program to solve the magic circle for n x n.
 * @param n : a number of squares in the magic circle (n x n)
 * @author Hiroki Tanioka
 * @date 2022.05.11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setnum(int*, int, int);
int check(int*, int, int, int);
int printvec(int*, int);
int calcsum(int*, int);

int main(int argc, char *argv[]) {
	int dim = 3;
	if (argc < 2) {
		return -1;
	}
	dim = atoi(argv[1]);
	printf("dim = %d\r\n", dim);
	int vector[dim * dim];
	memset(vector, 0, sizeof(int) * dim * dim);
	setnum(vector, 0, dim);
	printf("done.\r\n");
	return 0;
}

int calcsum(int* vector, int dim) {
	// vertical direction
	int prev = 0;
	int issame = 0;
	for (int i = 0; i < dim; i++) {
		int sum = 0;
		for (int j = i; j < dim * dim; j += dim) {
			sum += vector[j];
		}
		if (prev == 0) {
			prev = sum;
			continue;
		}
		if (prev == sum) {
			continue;
		} else {
			issame = 1;
			return 0;
		}
	}

	// lateral direction
	for (int i = 0; i < dim; i++) {
		int sum = 0;
		for (int j = i * dim; j < i * dim + dim; j++) {
			sum += vector[j];
		}
		if (prev == sum) {
			continue;
		} else {
			issame = 1;
			return 0;
		}
	}

	// oblique direction 1
	int sum = 0;
	for (int i = 0; i < dim; i++) {
		sum += vector[i * dim + i];
	}
	if (prev != sum) {
		issame = 1;
		return 0;
	}

	// oblique direction 2
	sum = 0;
	for (int i = 0; i < dim; i++) {
		sum += vector[i * dim + (dim - i - 1)];
	}
	if (prev != sum) {
		issame = 1;
		return 0;
	}
	if (issame == 0) {
		printvec(vector, dim);
	}
	return 1;
}

int setnum(int* vector, int index, int dim) {
	//printf("index: %d\r\n", index);
	if (index >= dim * dim) {
		calcsum(vector, dim);
	}
	for (int num = 1; num <= dim * dim; num++) {
		if (check(vector, num, index, dim) > 0) {
			continue;
		} else {
			vector[index] = num;
			if (setnum(vector, index + 1, dim) == 0) {
				return 0;
			}
			vector[index] = 0;
		}
	}
	return 1;
}

int check(int* vector, int num, int index, int dim) {
	if (index == 0) {
		return 0;
	}
	for (int i = 0; i < index; i++) {
		//printvec(vector, dim);
		if (vector[i] == num) {
			return num;
		}
	}
	return 0;
}

int printvec(int* vector, int dim) {
	for (int i = 0; i < dim * dim; i++) {
		printf("%d", vector[i]);
	}
	printf("\r\n");
	return 0;
}
