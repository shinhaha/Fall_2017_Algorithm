#include <stdio.h>
#include <stdlib.h>
#include<algorithm>
#include <iostream>
#include <string>
using namespace std;

struct Node {//huffman node struct
	char alphabet;//문자
	int freq;//빈도수
	struct Node* right = NULL;//오른쪽 자식
	struct Node* left = NULL;//왼쪽 자식
};

#define node struct Node
#define INF 2000000000//무한대

int MaxLen = -1;//맵핑문자의 최대길이
char* arr;//input배열
char** EncodeArr;//각 문자 맵핑 문자
node* table;//각 노드 테이블
int Heapsize = 0;//힙사이즈
int* frequency = NULL;//각 문자 빈도수
int* byte = NULL;//각 문자 byte길이

node* BuildMinHeap();
node* MinHeapify(node* A, int i, int heapsize);
void updateValue();
node* forestMerge();
node extractMinHeap(node* A);
void getHeight(const node* r, int height);
node* NodeSwap(node* input, int i, int j);
void Huffman(const node* r, int* arr, int top);
char* Encode();
void Decode(node* root, string s);

node* root = NULL;//forest Tree

node* BuildMinHeap() {//힙구조를 만든다.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		table = MinHeapify(table, i, Heapsize);
	return table;
}

node* MinHeapify(node* A, int i, int heapsize) {//작은값으로 힙어파이 해준다
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;
	if (l <= heapsize&&A[l].freq < A[i].freq)//왼쪽자식과 비교
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize&&A[r].freq<A[smallest].freq)//오른쪽 자식과 비교
		smallest = r;
	if (smallest != i) {//같지 않으면 자식과 바꿔주고 재귀적으로 실행
		table = NodeSwap(table, i, smallest);
		table = MinHeapify(table, smallest, heapsize);
	}
	return table;
}

node* NodeSwap(node* input, int i, int j) {//두개의 노드의 인자들을 스왑해준다
	node *tmp = (node *)malloc(sizeof(node));//임시 할당
	tmp->alphabet = (input + i)->alphabet;
	tmp->freq = (input + i)->freq;
	tmp->right = (input + i)->right;
	tmp->left = (input + i)->left;
	(input + i)->alphabet = (input + j)->alphabet;
	(input + i)->freq = (input + j)->freq;
	(input + i)->right = (input + j)->right;
	(input + i)->left = (input + j)->left;
	(input + j)->alphabet = tmp->alphabet;
	(input + j)->freq = tmp->freq;
	(input + j)->right = tmp->right;
	(input + j)->left = tmp->left;
	free(tmp);//free
	return input;
}

node extractMinHeap(node* A) {//가장작은값을 뽑는다
	int i = Heapsize;//i는 힙사이즈
	node temp = A[1];//리턴할 가장 작은 값 정점
	table = NodeSwap(A, 1, i);//Vertices 배열을 스왑한다 
	Heapsize--;//힙사이즈 줄인다
	A = MinHeapify(A, 1, Heapsize);
	return temp;//가장 작은값 리턴
}

void updateValue() {
	for (int i = 0; i <27; i++) {//초기화
		table[i].alphabet = (char)(i + 96);
		table[i].freq = INF;//초기화 무한대로
		table[i].left = NULL;
		table[i].right = NULL;
	}
	for (int i = 0; i < 100; i++)//freq
		frequency[(int)(arr[i]) - 96]++;
	for (int i = 0; i < 27; i++) {
		if (frequency[i] != 0)
			table[i].freq = frequency[i];
		if (table[i].freq != INF)
			Heapsize++;
	}
}

node* forestMerge() {
	BuildMinHeap();
	while (Heapsize >= 2) {//힙에 두개가 남을동안
		node* tmp = new node[2]();//2개의사이즈 만큼 할당
		node* left = new node();
		node* right = new node();

		//freq이 가장작은 2개의 노드를 뽑는다
		node* tmpa = &extractMinHeap(table);
		left->alphabet = tmpa->alphabet;
		left->freq = tmpa->freq;
		left->left = tmpa->left;
		left->right = tmpa->right;

		node *tmpb = &extractMinHeap(table);
		right->alphabet = tmpb->alphabet;
		right->freq = tmpb->freq;
		right->right = tmpb->right;
		right->left = tmpb->left;


		int a = left->freq;
		int b = right->freq;
		int sum = a + b;//두개의 노드의 freq를 합친 freq로
		tmp->freq = sum;//새노드 생성해서
		tmp->right = right;//각 노드를 right
		tmp->left = left;//left로 놓는다
		table[++Heapsize] = *tmp;//힙에 집어넣는다
		MinHeapify(table, 1, Heapsize);
		//BuildMinHeap();//힙구조 다시 맞춰준다.
	}
	return &extractMinHeap(table);
}

void Huffman(const node* r, int* arr, int index) {//Huffman Table 생성
	if (r->right != NULL) {//오른쪽 자식이 있으면
		arr[index] = 1;//1을 쓰고
		Huffman(r->right, arr, index + 1);//다음 인덱스로
	}
	if (r->left != NULL) {//왼쪽 자식이 있으면
		arr[index] = 0;//0을 쓰고
		Huffman(r->left, arr, index + 1);//다음 인덱스로
	}
	if (!(r->left) && !(r->right)) {
		printf("%c:", r->alphabet);
		char* s = new char[MaxLen]();//문자를 누적하기 위한 s배열
		char* num = new char[MaxLen]();//숫자를 문자로 바꾸기 위한 num배열
		for (int i = 0; i < index; i++) {//문자 길이만큼
			sprintf(num, "%d", arr[i]);//숫자를 문자로 바꾸고
			strcat(s, num);//s에 누적
			cout << arr[i];
		}
		strcpy(EncodeArr[(int)r->alphabet - 96], s);//누적한걸 알파벳에 맵핑
		byte[(int)r->alphabet - 96] = (int)strlen(s);//알파벳 비트의 길이 써줌
		printf(" freq:%d", r->freq);
		cout << endl;
	}
}

void getHeight(const node* r, int height) {//높이를 구하는 함수
	if (r->right != NULL) {//right가 있으면
		getHeight(r->right, height + 1);//right로 높이+1
	}
	if (r->left != NULL) {//left가 있으면
		getHeight(r->left, height + 1);//left로 높이+1
	}
	if (!(r->left) && !(r->right)) {//리프면
		MaxLen = max(MaxLen, height);//최대 문자길이를 업데이트
	}
}

char* Encode() {
	cout << endl;
	char* str = new char[MaxLen * 100]();//인코딩 배열의 크기를(최대문자길이*인풋개수)만큼 할당
	for (int i = 0; i < 100; i++) {
		strcat(str, EncodeArr[(int)arr[i] - 96]);
		cout << EncodeArr[(int)arr[i] - 96] << " ";
	}
	cout << "\n\n(";
	double totalBit = 0.0;
	for (int i = 0; i < 100; i++) {//bit의 길이 구성을 출력
		totalBit += byte[(int)arr[i] - 96];//bit를 더해간다
		if (i != 99)
			cout << byte[(int)arr[i] - 96] << "+";
		else
			cout << byte[(int)arr[i] - 96] << "  " << totalBit << " bits => " << ceil(totalBit / 8.0) << " bytes)" << endl;//byte 나머지있으면 올림
	}

	return str;//encoding 문자열을 리턴
}

void Decode(node* root, string s) {
	node* curr = root;
	for (int i = 0; i<s.size(); i++) {//문자열의 길이만큼
		if (s[i] == '0')//0이면
			curr = curr->left;//왼쪽으로
		else//1이면
			curr = curr->right;//오른쪽으로
		if (curr->left == NULL && curr->right == NULL) {//리프면
			cout << curr->alphabet << " ";//알파벳 더한다
			curr = root;//다시 root로
		}
	}
}


int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\huffman_input.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			table = new node[27]();//알파벳 개수 +1 (heap structure)
			arr = new char[100]();
			fscanf(f, "%s", arr);
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");

	frequency = (int*)calloc(27, sizeof(int));//frequency 셀 배열
	byte = (int*)calloc(27, sizeof(int));//byte길이 셀 배열
	updateValue();//frequecny 업데이트
	node* tmp = forestMerge();//하나의 큰 forest를 만든다.

	root = new node();//root노드에 복사
	root->alphabet = tmp->alphabet;
	root->right = tmp->right;
	root->left = tmp->left;
	root->freq = tmp->freq;

	getHeight(root, 1);//트리의 최대높이를 구한다.

	EncodeArr = new char*[27]();//알파벳 개수+1 만큼(heap structure)
	for (int i = 0; i <27; i++)
		EncodeArr[i] = new char[MaxLen]();//최대문자 길이만큼

	int* blankarr = new int[MaxLen]();//문자당 맵핑 할 이진수 최대길이만큼 할당
	
	cout << "Homework3\n" << endl;

	Huffman(root, blankarr, 0);
	
	cout << "\nEncoding Result =>";
	char* str = Encode();//encoding 출력하고 str에 저장
	cout << "\nDecoding Result = >" << endl;
	Decode(root, str);//str encoding 결과를 decoding
	printf("\n\n원래 문자는=>\n%s\n", arr);//원래 문장을출력

	return 0;
}