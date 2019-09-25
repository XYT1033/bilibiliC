
-- 01 冒泡排序

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

#define MAX 20

long getSystemTime(){
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//交换函数
void Swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int flag = 0; //0 标识没有排序好
//冒泡排序
void BubbleSort(int arr[],int length){

	for (int i = 0; i < length && flag == 0; i++){
		flag = 1; //认为已经排序好
		for (int j =  length - 1; j > i;j--){
			if (arr[j-1] < arr[j]){		
				flag = 0;
				Swap(&arr[j - 1],&arr[j]);
			}
		}
	}

}

//打印函数
void PrintArray(int arr[],int length){
	for (int i = 0; i < length; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}	

int main(void){
	
	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX;i++){
		arr[i] = rand() % MAX;
	}

	printf("排序前:\n");
	//PrintArray(arr,MAX);
	long t_start = getSystemTime();
	BubbleSort(arr,MAX);
	long t_end = getSystemTime();
	printf("冒泡排序%d个元素，所需时间:%ld\n", MAX, t_end- t_start);
	printf("排序后:\n");
	for (int i = 0; i < MAX; i++) {
		printf("NUM:%d\n", arr[i]);
	}
	//PrintArray(arr, MAX);




	system("pause");
	return 0;
}


-- 02 选择排序

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>

#define MAX 10000

long getSystemTime(){
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//交换函数
void Swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

//打印函数
void PrintArray(int arr[], int length){
	for (int i = 0; i < length; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}


//冒泡排序改进版
void BubbleSort(int arr[], int length){
	int flag = 0;
	for (int i = 0; i < length && flag == 0; i++){
		flag = 1; //认为已经排序好
		for (int j = length - 1; j > i; j--){
			if (arr[j - 1] < arr[j]){
				flag = 0;
				Swap(&arr[j - 1], &arr[j]);
			}
		}
	}

}


//选择排序
void SelectSort(int arr[],int length){
	
	//选择排序是不是减少交换次数 
	for (int i = 0; i < length;i ++){
		int min = i;
		for (int j = i + 1; j < length; j++){
			if (arr[j] < arr[min]){
				min = j;
			}
		}
		if (min != i){
			Swap(&arr[min],&arr[i]);
		}
	}
}


int main(void){
	

	int arr[MAX];
	int arr2[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i ++){
		int randNum = rand() % MAX;
		arr[i] = randNum;
		arr2[i] = randNum;
	}

	//冒泡排序
	long tbubble_start = getSystemTime();
	BubbleSort(arr, MAX);
	long tbubble_end = getSystemTime();
	printf("冒泡排序%d个元素,所需时间:%ld\n", MAX, tbubble_end - tbubble_start);


	//选择排序
	long tselect_start = getSystemTime();
	SelectSort(arr2, MAX);
	long tselect_end = getSystemTime();
	printf("选择排序%d个元素,所需时间:%ld\n", MAX, tselect_end - tselect_start);

	system("pause");
	return 0;
}



-- 03 插入排序 

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>

#define MAX 10

long getSystemTime(){
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//交换函数
void Swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

//打印函数
void PrintArray(int arr[], int length){
	for (int i = 0; i < length; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void InsertSort(int arr[],int length){
	
	int j;
	for (int i = 1; i < length;i ++){
		
		if (arr[i] < arr[i-1]){
			
			int temp = arr[i];
			for (j = i - 1; j >= 0 && temp < arr[j];j--){
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}

	}

}


int main(void){

	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		int randNum = rand() % MAX;
		arr[i] = randNum;
	}

	PrintArray(arr, MAX);
	InsertSort(arr,MAX);
	PrintArray(arr, MAX);
	

	system("pause");
	return 0;
}


-- 04 希尔排序

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>

#define MAX 100000

long getSystemTime(){
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//交换函数
void Swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

//打印函数
void PrintArray(int arr[], int length){
	for (int i = 0; i < length; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//从小到大
void ShellSort(int arr[], int length){

	int increasement = length;
	int i, j,k;

	do{

		//确定分组的增量
		increasement = increasement / 3 + 1;
		for (i = 0; i<increasement;i++){
			
			for (j = i + increasement; j < length; j += increasement){		
				
				if (arr[j] < arr[j-increasement] ){
					
					int temp = arr[j];
					for (k = j - increasement; k >= 0 && temp < arr[k];k-=increasement){
						arr[k + increasement] = arr[k];
					}
					arr[k + increasement] = temp;
				}

			}

		}
	} while (increasement > 1);

}

void InsertSort(int arr[], int length){

	int j;
	for (int i = 1; i < length; i++){

		if (arr[i] < arr[i - 1]){

			int temp = arr[i];
			for (j = i - 1; j >= 0 && temp < arr[j]; j--){
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}

	}

}


int main(void){
	
	int arr[MAX];
	int arr2[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		int randNum = rand() % MAX;
		arr[i] = randNum;
		arr2[i] = randNum;
	}

	//PrintArray(arr, MAX);
	long tshell_start = getSystemTime();
	ShellSort(arr, MAX);
	long tshell_end = getSystemTime();
	printf("希尔排序%d个元素所需时间:%ld\n",MAX,tshell_end - tshell_start);
	//PrintArray(arr, MAX);

	long tinsert_start = getSystemTime();
	InsertSort(arr2, MAX);
	long tinsert_end = getSystemTime();
	printf("插入排序%d个元素所需时间:%ld\n", MAX, tinsert_end - tinsert_start);


	
	system("pause");
	return 0;
}


-- 04 二叉树编程实战_非递归遍历 

--  LinkStack.h 

#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stdlib.h>
#include <stdio.h>

//链式栈的结点
typedef struct LINKNODE{
	struct LINKNODE* next;
}LinkNode;

//链式栈
typedef struct LINKSTACK{
	LinkNode head;
	int size;
}LinkStack;

//初始化函数
LinkStack* Init_LinkStack();
//入栈
void Push_LinkStack(LinkStack* stack, LinkNode* data);
//出栈
void Pop_LinkStack(LinkStack* stack);
//返回栈顶元素
LinkNode* Top_LinkStack(LinkStack* stack);
//返回栈元素的个数
int Size_LinkStack(LinkStack* stack);
//清空栈
void Clear_LinkStack(LinkStack* stack);
//销毁栈
void FreeSpace_LinkStack(LinkStack* stack);


#endif

--  LinkStack.c 

#include"LinkStack.h"
//初始化函数
LinkStack* Init_LinkStack(){

	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	stack->head.next = NULL;
	stack->size = 0;

	return stack;
}
//入栈
void Push_LinkStack(LinkStack* stack, LinkNode* data){

	if (stack == NULL){
		return;
	}

	if (data == NULL){
		return;
	}
	
	data->next = stack->head.next;
	stack->head.next = data;
	stack->size++;
}
//出栈
void Pop_LinkStack(LinkStack* stack){
	if (stack == NULL){
		return;
	}

	if (stack->size == 0){
		return;
	}
	
	//第一个有效结点
	LinkNode* pNext = stack->head.next;
	stack->head.next = pNext->next;

	stack->size--;
}
//返回栈顶元素
LinkNode* Top_LinkStack(LinkStack* stack){
	if (stack == NULL){
		return NULL;
	}
	if (stack->size == 0){
		return NULL;
	}
	return stack->head.next;
}
//返回栈元素的个数
int Size_LinkStack(LinkStack* stack){
	if (stack == NULL){
		return -1;
	}
	return stack->size;
}
//清空栈
void Clear_LinkStack(LinkStack* stack){
	if (stack == NULL){
		return;
	}
	stack->head.next = NULL;
	stack->size = 0;
}
//销毁栈
void FreeSpace_LinkStack(LinkStack* stack){
	if (stack == NULL){
		return;
	}
	free(stack);
}



--

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkStack.h"

#define MY_FALSE 0
#define MY_TRUE 1


//二叉树结点
typedef struct BINARYNODE{
	char ch;
	struct BINARYNODE* lchild;
	struct BINARYNODE* rchild;
}BinaryNode;

//二叉树的非递归遍历
typedef struct BITREESTACKNODE{
	LinkNode node;
	BinaryNode* root;
	int flag;
}BiTreeStackNode;

//创建栈中的结点
BiTreeStackNode* CreateBiTreeStackNode(BinaryNode* node,int flag){
	BiTreeStackNode* newnode = (BiTreeStackNode*)malloc(sizeof(BiTreeStackNode));
	newnode->root = node;
	newnode->flag = flag;
	return newnode;
}

//非递归遍历
void NonRecursion(BinaryNode* root){

	//创建栈
	LinkStack* stack = Init_LinkStack();
	//把根节点扔到栈里
	Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(root, MY_FALSE));

	while (Size_LinkStack(stack) > 0){
		
		//先弹出栈顶元素
		BiTreeStackNode* node = (BiTreeStackNode*)Top_LinkStack(stack);
		Pop_LinkStack(stack);

		//判断弹出的结点是否为空
		if (node->root == NULL){
			continue;
		}

		if (node->flag == MY_TRUE){
			printf("%c",node->root->ch);
		}
		else{
			
			//当前结点入栈
			node->flag = MY_TRUE;
			Push_LinkStack(stack, (LinkNode*)node);
			//当前结点右结点入栈
			Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(node->root->rchild, MY_FALSE));			
			//当前结点的左结点入栈
			Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(node->root->lchild, MY_FALSE));

		}

	}
}

void Recursion(BinaryNode* root){
	if (root == NULL){
		return;
	}
	
	//打印左子树
	Recursion(root->lchild);
	//打印右子树
	Recursion(root->rchild);
	printf("%c", root->ch);
}

void CresteBinaryTree(){

	//创建结点
	BinaryNode node1 = { 'A', NULL, NULL };
	BinaryNode node2 = { 'B', NULL, NULL };
	BinaryNode node3 = { 'C', NULL, NULL };
	BinaryNode node4 = { 'D', NULL, NULL };
	BinaryNode node5 = { 'E', NULL, NULL };
	BinaryNode node6 = { 'F', NULL, NULL };
	BinaryNode node7 = { 'G', NULL, NULL };
	BinaryNode node8 = { 'H', NULL, NULL };


	//建立结点关系
	node1.lchild = &node2;
	node1.rchild = &node6;
	node2.rchild = &node3;
	node3.lchild = &node4;
	node3.rchild = &node5;
	node6.rchild = &node7;
	node7.lchild = &node8;

	//二叉树非递归打印
	NonRecursion(&node1); printf("\n");
	Recursion(&node1); printf("\n");

}



int main(void){
	
	CresteBinaryTree();
	system("pause");
	return 0;
} 


-- 09 二叉树编程实战_井号法创建二叉树

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//二叉树结点
typedef struct BINARYNODE{
	char ch;
	struct BINARYNODE* lchild;
	struct BINARYNODE* rchild;
}BinaryNode;

void Recursion(BinaryNode* root){
	if (root == NULL){
		return;
	}

	printf("%c",root->ch);
	Recursion(root->lchild);
	Recursion(root->rchild);
}

BinaryNode* CreateBinaryTree(){
	
	fflush(stdin);
	char ch;
	scanf("%c",&ch);

	BinaryNode* node;

	if (ch == '#'){
		node = NULL;
	}
	else{

		node = (BinaryNode*)malloc(sizeof(BinaryNode));
		node->ch = ch;
		node->lchild = CreateBinaryTree();
		node->rchild = CreateBinaryTree();
	}


	return node;
}

int main(void){

	//创建树
	BinaryNode* root = CreateBinaryTree();
	//打印树
	Recursion(root);
	

	printf("\n");
	system("pause");
	return 0;
}











 