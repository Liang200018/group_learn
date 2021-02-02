#include<stdio.h>
int main() {
	int d; int i, j; int n; int temp;
	int data[10] = {9, 81, 7, 61, 51, 4, 31, 233, 1, 0};
	d = 10 / 2;
	n = 10;
	while(d > 0) {
		for(i = d; i < n; i++) {
			if(data[i] < data[i - d]) {
				temp = data[i];
				for(j = i - d; j >= 0; j = j - d) {
					if(temp < data[j])
						data[j + d] = data[j];
					else break;
				}
				data[j + d] = temp;				
			}
		}
		d = d / 2;
	}
	for(i = 0; i < 10; i++)
		printf("%d ", data[i]);
} 
