#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <cstdbool>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input������ �ε���
	int s;//���۽ð�
	int f;//����ð�
	int v;//value
	bool visit;//�湮 ����
};

#define ver struct Ver

ver* act;//Ver node �迭
int number = 0;//�Ѱ���

void Iterative_Greedy_algorithm(int i) {
	
	int n = i;//�� ����
	int minf = INF;//���� �ִ� �������� f
	int minfIndex = -1;//���� �ִ� �������� f�� �ε���

	for (int x = 1; x <= n; x++) {
		if (minf >= act[x].f && !act[x].visit) {//�湮���ѰŰ� ���������Ÿ�
			minf = act[x].f;//���̶� �ε��� ������Ʈ
			minfIndex = act[x].i;
		}
	}

	act[minfIndex].visit = true;//�湮�ߴٰ� ��ũ�ϰ�
	printf("���õ� Activity�� input������ index = > %d\n", minfIndex);//���
	number++;//���� ����

	while (true) {
		int thanminfs = INF + 1;//�ʱ�ȭ
		int thanminff = INF + 1;
		int thanminfsIndex = -1;

		for (int x = 1; x <= n; x++) {//���Ұ�����ŭ ���鼭
			if (thanminfs >=act[x].s&&thanminff>=act[x].f &&!act[x].visit&&act[x].s >=minf) {//�����Ű� �湮���ѰŰ� �������� ���� �������� ũ�ų����� thanminfs�� �ε����� ���� act�迭�� f�� �� ������
				thanminfs = act[x].s;//������Ʈ
				thanminff = act[x].f;
				thanminfsIndex = x;//k�� m���� �ϴ� �ε����� ã�´ٿ� ����.
			}
		}

		if (thanminfsIndex == -1)//��������=>������Ʈ �ȵ�����
			break;

		minf = act[thanminfsIndex].f;//�������������� ������Ʈ�Ѵ�
		act[thanminfsIndex].visit = true;//�湮�ߴٰ� ��ũ�Ѵ�

		printf("���õ� Activity�� input������ index = > %d\n",thanminfsIndex);//���
		number++;//���� ++
	}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\activity_input.txt", "r");
	int size;//�������
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			act = (ver*)realloc(act, sizeof(ver)*(i + 2));
			if (i == 0) {
				act[0].i = 0;
				act[0].s = 0;
				act[0].f = 0;
				act[0].v = 0;
				act[0].visit = false;
			}
			act[i + 1].i = i + 1;//input������ index�� ���
			act[i + 1].visit = false;//�湮����
			fscanf(file,"%d", &act[i+1].s);//input �޴´�
			fscanf(file, "%d",&act[i+1].f);
			fscanf(file, "%d",&act[i+1].v);
			i++;
		}
		act[i+1].s = INF;
		fclose(file);
	}
	else
		printf("���� �б� ����");
	cout << "Homework1_5\n" << endl;
	Iterative_Greedy_algorithm(i);//���ľȵ� activity select �׸��� �˰���
	cout << "�� ����: " << number;
	
	return 0;
}