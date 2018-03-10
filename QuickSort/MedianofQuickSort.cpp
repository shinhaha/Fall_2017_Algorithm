#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
using namespace std;
int* arr;
void Swap(int* A, int x, int y);
int Partition(int*A, int p, int r);
void printing(int* A, int n);
void MedianQuicksort(int* A, int p, int r);
int findMedian(int* a,int* arr);

void MedianQuicksort(int* A, int p, int r) {	
		if (p + 2<r){
			int* a = (int*)malloc(sizeof(int)*3);
			for (int j = 0; j < 3; j++) {//중복된 랜덤값 뽑지않기 위해
				a[j] = rand() % (r-p+1)+p;//p와 r까지의 랜덤값 뽑는다
				for (int k = 0; k < j; k++) { //두번째부터는 그 전것들과 비교
					if (a[k] != a[j]) //숫자가 같지 않으면 다음 숫자와 비교 끝까지 없으면 그냥 다음 숫자 선택
						continue;
					else {// 같은 숫자가 있다면 
						j--;    // 숫자를 다시뽑기 위해 j값을 줄이고
						break;  // 비교하는 for문을 빠져나간다
					}
				}
			}
			Swap(arr,findMedian(a,arr),r);//Medain과 r index Swap
			free(a);
		}
		if (p < r) {//일반 QuickSort
		int q = Partition(A, p, r);
		MedianQuicksort(A, p, q - 1);
		MedianQuicksort(A, q + 1, r);
	}
}

int findMedian(int* a,int* arr) {//중간값 찾는함수
	int x = arr[a[0]]; int y = arr[a[1]]; int z = arr[a[2]];//랜덤 3개의 인덱스에 들어있는 값들
	int k = min(x, y) ^ min(y, z) ^ min(z, x);//중간 값 찾는 연산자
	if (x == k)//중간값 갖는 인덱스 리턴
		return a[0];
	else if (y == k)
		return a[1];
	else if (z == k)
		return a[2];
}

int Partition(int*A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			Swap(A, i, j);
		}
	}
	Swap(A, i + 1, r);
	return i + 1;
}

void Swap(int* A, int x, int y) {
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++) 
		printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\test2.txt", "r");
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
		printf("파일 읽기 실패");

	srand((unsigned)time(NULL));
	float start = clock();
	MedianQuicksort(arr, 0, i - 1);
	float end = clock();
	float finish = end - start;
	//printf("MedianofQuickSort : %.12f\n", finish / CLOCKS_PER_SEC);
	printing(arr, i);
}
