#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

typedef struct Node {
	int studentNum;
	int score;
	struct Node *next = NULL;
	struct Node *prev = NULL;
};

Node *start;

void addNode(struct Node** start, int score, int studentNum) {
	Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->score = score;
	newNode->studentNum = studentNum;
	if ((*start) == NULL)
	{
		newNode->prev = newNode;
		newNode->next = newNode;
		(*start) = newNode;
	}
	else {
		newNode->prev = (*start);
		newNode->next = (*start)->next;
		(*start)->next->prev = newNode;
		(*start)->next = newNode;
	}
}

void insertionSort(Node** start){
	if ((*start) == NULL)
		;
	else if ((*start)->next==NULL)
		;
	else {
		for (Node* p = (*start)->next; p != (*start); p = p->next) {
			int key = p->score;
			int key1 = p->studentNum;
			Node* newNode = p->prev;
			while(newNode->next!=(*start)&&(newNode->score>key)){
				newNode->next->score = newNode->score;
				newNode->next->studentNum = newNode->studentNum;
				newNode = newNode->prev;
			}
			newNode->next->score = key;
			newNode->next->studentNum = key1;
		}
	}
}

void printNode() {
	struct Node *temp = start;
	do {
		printf("%d %d , ", temp->studentNum, temp->score);
		temp = temp->next;
	} while (temp != start);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f,"C:\\test3.txt", "r");
	if (f != NULL) {
		char temp[20];
		char temp1[10];
		int StuNum = 0;;
		int score = 0;
		while (!feof(f)) {
			fscanf(f,"%s %s", temp, temp1);
			StuNum = atoi(temp);
			score = atoi(temp1);
			addNode(&start, score, StuNum);
		}
		fclose(f);
	}
	else
		printf("Read Fail.");
	insertionSort(&start);
	printNode();
	free(start);
}