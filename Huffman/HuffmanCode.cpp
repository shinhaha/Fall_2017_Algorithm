#include <stdio.h>
#include <stdlib.h>
#include<algorithm>
#include <iostream>
#include <string>
using namespace std;

struct Node {//huffman node struct
	char alphabet;//����
	int freq;//�󵵼�
	struct Node* right = NULL;//������ �ڽ�
	struct Node* left = NULL;//���� �ڽ�
};

#define node struct Node
#define INF 2000000000//���Ѵ�

int MaxLen = -1;//���ι����� �ִ����
char* arr;//input�迭
char** EncodeArr;//�� ���� ���� ����
node* table;//�� ��� ���̺�
int Heapsize = 0;//��������
int* frequency = NULL;//�� ���� �󵵼�
int* byte = NULL;//�� ���� byte����

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

node* BuildMinHeap() {//�������� �����.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		table = MinHeapify(table, i, Heapsize);
	return table;
}

node* MinHeapify(node* A, int i, int heapsize) {//���������� �������� ���ش�
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;
	if (l <= heapsize&&A[l].freq < A[i].freq)//�����ڽİ� ��
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize&&A[r].freq<A[smallest].freq)//������ �ڽİ� ��
		smallest = r;
	if (smallest != i) {//���� ������ �ڽİ� �ٲ��ְ� ��������� ����
		table = NodeSwap(table, i, smallest);
		table = MinHeapify(table, smallest, heapsize);
	}
	return table;
}

node* NodeSwap(node* input, int i, int j) {//�ΰ��� ����� ���ڵ��� �������ش�
	node *tmp = (node *)malloc(sizeof(node));//�ӽ� �Ҵ�
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

node extractMinHeap(node* A) {//������������ �̴´�
	int i = Heapsize;//i�� ��������
	node temp = A[1];//������ ���� ���� �� ����
	table = NodeSwap(A, 1, i);//Vertices �迭�� �����Ѵ� 
	Heapsize--;//�������� ���δ�
	A = MinHeapify(A, 1, Heapsize);
	return temp;//���� ������ ����
}

void updateValue() {
	for (int i = 0; i <27; i++) {//�ʱ�ȭ
		table[i].alphabet = (char)(i + 96);
		table[i].freq = INF;//�ʱ�ȭ ���Ѵ��
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
	while (Heapsize >= 2) {//���� �ΰ��� ��������
		node* tmp = new node[2]();//2���ǻ����� ��ŭ �Ҵ�
		node* left = new node();
		node* right = new node();

		//freq�� �������� 2���� ��带 �̴´�
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
		int sum = a + b;//�ΰ��� ����� freq�� ��ģ freq��
		tmp->freq = sum;//����� �����ؼ�
		tmp->right = right;//�� ��带 right
		tmp->left = left;//left�� ���´�
		table[++Heapsize] = *tmp;//���� ����ִ´�
		MinHeapify(table, 1, Heapsize);
		//BuildMinHeap();//������ �ٽ� �����ش�.
	}
	return &extractMinHeap(table);
}

void Huffman(const node* r, int* arr, int index) {//Huffman Table ����
	if (r->right != NULL) {//������ �ڽ��� ������
		arr[index] = 1;//1�� ����
		Huffman(r->right, arr, index + 1);//���� �ε�����
	}
	if (r->left != NULL) {//���� �ڽ��� ������
		arr[index] = 0;//0�� ����
		Huffman(r->left, arr, index + 1);//���� �ε�����
	}
	if (!(r->left) && !(r->right)) {
		printf("%c:", r->alphabet);
		char* s = new char[MaxLen]();//���ڸ� �����ϱ� ���� s�迭
		char* num = new char[MaxLen]();//���ڸ� ���ڷ� �ٲٱ� ���� num�迭
		for (int i = 0; i < index; i++) {//���� ���̸�ŭ
			sprintf(num, "%d", arr[i]);//���ڸ� ���ڷ� �ٲٰ�
			strcat(s, num);//s�� ����
			cout << arr[i];
		}
		strcpy(EncodeArr[(int)r->alphabet - 96], s);//�����Ѱ� ���ĺ��� ����
		byte[(int)r->alphabet - 96] = (int)strlen(s);//���ĺ� ��Ʈ�� ���� ����
		printf(" freq:%d", r->freq);
		cout << endl;
	}
}

void getHeight(const node* r, int height) {//���̸� ���ϴ� �Լ�
	if (r->right != NULL) {//right�� ������
		getHeight(r->right, height + 1);//right�� ����+1
	}
	if (r->left != NULL) {//left�� ������
		getHeight(r->left, height + 1);//left�� ����+1
	}
	if (!(r->left) && !(r->right)) {//������
		MaxLen = max(MaxLen, height);//�ִ� ���ڱ��̸� ������Ʈ
	}
}

char* Encode() {
	cout << endl;
	char* str = new char[MaxLen * 100]();//���ڵ� �迭�� ũ�⸦(�ִ빮�ڱ���*��ǲ����)��ŭ �Ҵ�
	for (int i = 0; i < 100; i++) {
		strcat(str, EncodeArr[(int)arr[i] - 96]);
		cout << EncodeArr[(int)arr[i] - 96] << " ";
	}
	cout << "\n\n(";
	double totalBit = 0.0;
	for (int i = 0; i < 100; i++) {//bit�� ���� ������ ���
		totalBit += byte[(int)arr[i] - 96];//bit�� ���ذ���
		if (i != 99)
			cout << byte[(int)arr[i] - 96] << "+";
		else
			cout << byte[(int)arr[i] - 96] << "  " << totalBit << " bits => " << ceil(totalBit / 8.0) << " bytes)" << endl;//byte ������������ �ø�
	}

	return str;//encoding ���ڿ��� ����
}

void Decode(node* root, string s) {
	node* curr = root;
	for (int i = 0; i<s.size(); i++) {//���ڿ��� ���̸�ŭ
		if (s[i] == '0')//0�̸�
			curr = curr->left;//��������
		else//1�̸�
			curr = curr->right;//����������
		if (curr->left == NULL && curr->right == NULL) {//������
			cout << curr->alphabet << " ";//���ĺ� ���Ѵ�
			curr = root;//�ٽ� root��
		}
	}
}


int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\huffman_input.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			table = new node[27]();//���ĺ� ���� +1 (heap structure)
			arr = new char[100]();
			fscanf(f, "%s", arr);
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");

	frequency = (int*)calloc(27, sizeof(int));//frequency �� �迭
	byte = (int*)calloc(27, sizeof(int));//byte���� �� �迭
	updateValue();//frequecny ������Ʈ
	node* tmp = forestMerge();//�ϳ��� ū forest�� �����.

	root = new node();//root��忡 ����
	root->alphabet = tmp->alphabet;
	root->right = tmp->right;
	root->left = tmp->left;
	root->freq = tmp->freq;

	getHeight(root, 1);//Ʈ���� �ִ���̸� ���Ѵ�.

	EncodeArr = new char*[27]();//���ĺ� ����+1 ��ŭ(heap structure)
	for (int i = 0; i <27; i++)
		EncodeArr[i] = new char[MaxLen]();//�ִ빮�� ���̸�ŭ

	int* blankarr = new int[MaxLen]();//���ڴ� ���� �� ������ �ִ���̸�ŭ �Ҵ�
	
	cout << "Homework3\n" << endl;

	Huffman(root, blankarr, 0);
	
	cout << "\nEncoding Result =>";
	char* str = Encode();//encoding ����ϰ� str�� ����
	cout << "\nDecoding Result = >" << endl;
	Decode(root, str);//str encoding ����� decoding
	printf("\n\n���� ���ڴ�=>\n%s\n", arr);//���� ���������

	return 0;
}