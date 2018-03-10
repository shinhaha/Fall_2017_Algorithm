#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000


int* arr;//인자받을 배열
int RecursiveCutRod(int n);
int BottomupCutRod(int n);
void PrintCutRod(int* s, int n);

int* rem;//recursive 어떻게 잘랐는지 알기위한 저장배열

int RecursiveCutRod(int n) {//재귀적 CutRod
	if (n == 0)//종료조건
		return 0;
	int q = -INF;//초기화
	for (int i = 1; i <= n; i++) {
		if (q < arr[i] + RecursiveCutRod(n - i)) {//n을 i랑 n-i로 자른게 더 비싸면
			q = arr[i] + RecursiveCutRod(n - i);//업데이트 recursive로 n-i는 어떻게 자를인가를 호출
			rem[n] = i;//저장
		}
	}
	return q;//max 리턴
}

int BottomupCutRod(int n) {//Bottomup Cutrod
	int *r = (int*)malloc(sizeof(int)*(n + 1));//dp
	int *s = (int*)malloc(sizeof(int)*(n + 1));//어떻게 잘랐는지 기억배열
	r[0] = 0;
	for (int j = 1; j <= n; j++) {
		int q = -INF;//초기화
		for (int i = 1; i <= j; i++)
			if (q < arr[i] +r[j-i]) {//j길이를 i랑 j-i로 자른게 더 비싸면
				q=arr[i] + r[j-i];//업데이트
				s[j] = i;//기억
			}
		r[j] = q;//최대값 저장
	}
	PrintCutRod(s,n);//How bottom Cut 출력
	cout << "<=Bottomup CutRod";
	return r[n];//최대값 리턴
}


void PrintCutRod(int* s,int n) {//어떻게 잘랐는지 출력
	int temp = n;
	cout << "( ";
	while (temp> 0){
		cout << s[n]<<" ";//어떻게 잘랐나 출력하고
		temp = temp - s[n];//전체에서 빼서 출력
	}
	cout << ")로 잘림";
	cout << "cost는";
	temp = n;
	cout << "( ";
	while (temp> 0) {//같은 방식으로 cost 출력
		cout << arr[s[temp]] << " ";
		temp =temp - s[temp];
	}
	cout << " )";
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\rod_cutting.txt", "r");
	int size;//막대길이
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d",&size);//주어진 막대길이
			int index = -1;
			for (int k = 1; k<=size; k++) {
				fscanf(f, "%d",&index);
				arr = (int*)realloc(arr, sizeof(int)*(index + 1));
				fscanf(f, "%d", &arr[index]);//원소에 값을 넣는다
			}
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");

	rem= (int*)malloc(sizeof(int)*(size + 1));
	cout <<"RecursiveCutRod=>"<<RecursiveCutRod(size)<< endl;
	PrintCutRod(rem, size);//How recursive Cut 출력
	cout <<"<=recursive CutRod"<<endl;
	cout << endl<<"BottomupCutRod=>" <<BottomupCutRod(size) << endl;
	return 0;
}