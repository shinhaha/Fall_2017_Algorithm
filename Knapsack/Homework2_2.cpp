#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

double* w;//weight input arr
int* b;//benefit input arr
double **B;//dp 저장 배열

double W;//가방 크기


void knapsackPrint(int n, double** B) {//출력하는 함수
	int i = n;
	double weight = W;
	int maxbenefit = B[i][(int)((weight)*100.0) + 1];//내가 만든 최대 benefit
	while (i > 0 && maxbenefit>=0) {//i만큼 하는데 max가 0이상인 동안
		if (B[i][(int)((weight)*100.0) +1] != B[i - 1][(int)((weight)*100.0) + 1]){//소수점 2째 자리이므로 100곱하고 앞에꺼와 같으면 그대로 옮긴것이므로 그대로 옮긴게 아니라면
			cout << "선택된 item:" << i << endl;//출력
			maxbenefit = maxbenefit - b[i];//benefit에서 빼준다
			weight = weight - (w[i]);//가방 무게를 줄여준다
			i--;
		}
		else
			i--;//그냥 왼쪽으로 이동
	}
}

void Knapsack(int n) {
	for (int i = 1; i <= n; i++){//앞의 문제와 동일하게 해결하지만 소수점을 해결하기위해 *100을 처리해준다
		for (int j = 1;j <= W*100.0+1; j++){
			if ((w[i] * 100.0) < (double)(j))//-범위 아니라면
				if (b[i] + B[i - 1][(int)((j - w[i] * 100.0))] >B[i-1][j])//큰거 비교해서 넣어준다
					B[i][j] = b[i] + B[i - 1][(int)((j - w[i] * 100.0))];
				else
					B[i][j] = B[i - 1][j];
			else B[i][j] = B[i - 1][j];//아니면 옆으로 옮김
		}
	}


	cout << "max->" <<B[n][(int)((W)*100.0)+1]<<endl;//최대 benefit 저장된 위치 출력
	knapsackPrint(n, B);//출력
}



int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\신하람\\Desktop\\knapsack_input_2.txt", "r");
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			w= (double*)realloc(w, sizeof(double)*(i + 2));
			b= (int*)realloc(b, sizeof(int)*(i + 2));
			if (i == 0) {
				w[0] = 0;
				b[0] = 0;
			}
			fscanf(file,"%lf", &w[i+1]);//index 1부터 weight와 benefit을 입력받는다
			fscanf(file,"%d",&b[i+1]);
			i++;
		}
		W = 1.00;//가방 크기

		B = (double**)calloc((i+1),sizeof(double*));
		for (int k = 0; k <(i+1); k++)
			B[k] = (double*)calloc((W*100+2),sizeof(double));//소수아래 2째짜리 까지이므로 100을 곱해준다 그리고 필요한 공간 1을 더해준다->W+1까지 쓰기 떄문에
		
		fclose(file);
	}
	else
		printf("파일 읽기 실패");
	cout << "Homework2_2\n" << endl;
	Knapsack(i);//knapsack 0-1 problem

	return 0;
}