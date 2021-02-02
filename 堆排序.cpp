#include<stdio.h>
int sift(int *data, int k, int n) {
	int i = k;
	int j = 2 * i; int temp;
	temp = data[i];
	while(j <= n) {
		if(j < n && data[j + 1] > data[j]) j++;
		if(temp < data[j]) {
			data[i] = data[j];//父节点用大子节点代替
			i = j;
			j = 2 * i; 
		}
		else break;
	}
	data[i] = temp; 
	return data[k];
}
void HeapSort(int *data, int n) {
	int i; int temp;
	for(i = n / 2; i > 0; i--) {
		sift(data, i, n);
	}
		
	for(i = n; i >= n - 2; i--) {
		temp = data[i];
		data[i] = data[1];
		data[1] = temp;
		sift(data, 1, i - 1);
	}
	//return data;
}
int main() {
	int data[11] = {-1, 8, 7, 6, 5, 4, 1, 2, 3, 9, 0};
	int i;
	HeapSort(data, 10);
	for(i = 0; i <= 10; i++)
		printf("%d ", data[i]);
} 
