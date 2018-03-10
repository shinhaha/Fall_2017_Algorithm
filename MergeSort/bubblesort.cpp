#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
int* arr;
void BubbleSort(int *arr, int length);
void printing(int* A, int n);

void BubbleSort(int *arr,int length) {
	for(int i=length-1; i>0; i--)
		for(int j=0; j<i; j++)
			if (arr[j] > arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\test_10000.txt", "r");
	int i = 0;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			fscanf(f, "%d", (arr + i));
			i++;
		}
		fclose(f);
	}
	else
		printf("Read Fail");
	BubbleSort(arr,i);
	printing(arr, i);
}