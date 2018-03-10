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
			for (int j = 0; j < 3; j++) {//�ߺ��� ������ �����ʱ� ����
				a[j] = rand() % (r-p+1)+p;//p�� r������ ������ �̴´�
				for (int k = 0; k < j; k++) { //�ι�°���ʹ� �� ���͵�� ��
					if (a[k] != a[j]) //���ڰ� ���� ������ ���� ���ڿ� �� ������ ������ �׳� ���� ���� ����
						continue;
					else {// ���� ���ڰ� �ִٸ� 
						j--;    // ���ڸ� �ٽû̱� ���� j���� ���̰�
						break;  // ���ϴ� for���� ����������
					}
				}
			}
			Swap(arr,findMedian(a,arr),r);//Medain�� r index Swap
			free(a);
		}
		if (p < r) {//�Ϲ� QuickSort
		int q = Partition(A, p, r);
		MedianQuicksort(A, p, q - 1);
		MedianQuicksort(A, q + 1, r);
	}
}

int findMedian(int* a,int* arr) {//�߰��� ã���Լ�
	int x = arr[a[0]]; int y = arr[a[1]]; int z = arr[a[2]];//���� 3���� �ε����� ����ִ� ����
	int k = min(x, y) ^ min(y, z) ^ min(z, x);//�߰� �� ã�� ������
	if (x == k)//�߰��� ���� �ε��� ����
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
		printf("���� �б� ����");

	srand((unsigned)time(NULL));
	float start = clock();
	MedianQuicksort(arr, 0, i - 1);
	float end = clock();
	float finish = end - start;
	//printf("MedianofQuickSort : %.12f\n", finish / CLOCKS_PER_SEC);
	printing(arr, i);
}
