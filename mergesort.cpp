#include<stdio.h>
#include<stdlib.h>
void merge(int R[], int low, int mid, int high) {
	int i = 0, j; int k = 0;
	int *R1;
	j = mid + 1;
	R1 = (int *)malloc(sizeof(high - low + 1));
	while(i <= mid && j <= high) {
		if(R[i] < R[j]) {
			R1[k++] = R[i++];
		}
		else {
			R1[k++] = R[j++];
		}
	}
	while(i <= mid) {
		R1[k++] = R[i++];
	}
	while(j <= high) {
		R1[k++] = R[j++];
	}
	for(i = 0; i < k; i++) {
		R[i] = R1[i];
	}
	free(R1);
} 
//Ò»ÌËÅÅÐò 
void MergePass(int R[], int length, int n) {
	int i;
	for(i = 0; i + 2 * length - 1 < n; i = i + 2 * length) {
		merge(R, i, i + length - 1, i + 2 * length - 1);
	} 
	if(i + length - 1 < n) {
		merge(R, i, i + length - 1, n - 1);
	}
} 
void MergeSort(int R[], int n) {
	int length;
	for(length = 1; length < n; length = length * 2) {
		MergePass(R, length, n);
	}
}
int main() {
	int data[9] = {1, 2, 3, 2, 4, 12, 1, 98, 77};
	MergeSort(data, 9);
	for(int i = 0; i < 9; i++)
		printf("%d ", data[i]);
}
