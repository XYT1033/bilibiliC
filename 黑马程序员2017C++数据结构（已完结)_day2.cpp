
-- 01 循环链表
--  CircleLinkList.h

#ifndef CIRCLELINKLIST
#define CIRCLELINKLIST

#include<stdio.h>
#include<stdlib.h>

//链表的小结点
typedef struct CIRCLELINKNODE{
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

//链表结构体
typedef struct CIRCLELINKLIST{
	CircleLinkNode head;
	int size;
}CircleLinkList;

//编写针对链表结构体操作的API函数

#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALSE 0

//比较回调
typedef int(*COMPARENODE)(CircleLinkNode*, CircleLinkNode*);
//打印回调
typedef void(*PRINTNODE)(CircleLinkNode*);

//初始化函数
CircleLinkList* Init_CircleLinkList();
//插入函数
void Insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data);
//获得第一个元素
CircleLinkNode* Front_CircleLinkList(CircleLinkList* clist);
//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList* clist,int pos);
//根据值去删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//获得链表的长度
int Size_CircleLinkList(CircleLinkList* clist);
//判断是否为空
int IsEmpty_CircleLinkList(CircleLinkList* clist);
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//打印节点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print);
//释放内存
void FreeSpace_CircleLinkList(CircleLinkList* clist);

#endif




 -- CircleLinkList.c 

 #include"CircleLinkList.h"

//初始化函数
CircleLinkList* Init_CircleLinkList(){

	CircleLinkList* clist = (CircleLinkList*)malloc(sizeof(CircleLinkList));
	clist->head.next = &(clist->head);
	clist->size = 0;

	return clist;
}

//插入函数
void Insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data){
	
	if (clist == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	if (pos <0 || pos > clist->size){
		pos = clist->size;
	}

	//根据位置查找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos;i++){
		pCurrent = pCurrent->next;
	}

	//新数据入链表
	data->next = pCurrent->next;
	pCurrent->next = data;

	clist->size ++;
}
//获得第一个元素
CircleLinkNode* Front_CircleLinkList(CircleLinkList* clist){
	return clist->head.next;
}
//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList* clist, int pos){

	if (clist == NULL){
		return;
	}

	if (pos < 0 || pos >= clist->size){
		return;
	}

	//根据pos找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos;i++){
		pCurrent = pCurrent->next;
	}
	
	//缓存当前结点的下一个结点
	CircleLinkNode* pNext = pCurrent->next;
	pCurrent->next = pNext->next;
	
	clist->size--;
}
//根据值去删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare){

	if (clist == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	//这个是循环链表
	CircleLinkNode* pPrev = &(clist->head);
	CircleLinkNode* pCurrent = pPrev->next;
	int i = 0;
	for (i = 0; i < clist->size; i++){
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE){
			pPrev->next = pCurrent->next;
			clist->size--;
			break;
		}
		pPrev = pCurrent;
		pCurrent = pPrev->next;
	}
}
//获得链表的长度
int Size_CircleLinkList(CircleLinkList* clist){
	return clist->size;
}
//判断是否为空
int IsEmpty_CircleLinkList(CircleLinkList* clist){
	if (clist->size == 0){
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare){

	if (clist == NULL){
		return -1;
	}

	if (data == NULL){
		return -1;
	}

	CircleLinkNode* pCurrent = clist->head.next;
	int flag = -1;
	for (int i = 0; i < clist->size; i ++){
		if (compare(pCurrent,data) == CIRCLELINKLIST_TRUE){
			flag = i;
			break;
		}
		pCurrent = pCurrent->next;
	}

	return flag;
}
//打印节点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print){
		
	if (clist == NULL){
		return;
	}
	
	//辅助指针变量
	CircleLinkNode* pCurrent = clist->head.next;
	for (int i = 0; i < clist->size;i++){
		if (pCurrent == &(clist->head)){
			pCurrent = pCurrent->next;
			printf("------------------\n");
		}
		print(pCurrent);
		pCurrent = pCurrent->next;
	}

}
//释放内存
void FreeSpace_CircleLinkList(CircleLinkList* clist){

	if (clist == NULL){
		return;
	}
	free(clist);
}


 -- 源.c 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"CircleLinkList.h"

typedef struct PERSON{
	CircleLinkNode node;
	char name[64];
	int age;
	int score;
}Person;

void MyPrint(CircleLinkNode* data){
	Person* p = (Person*)data;
	printf("Name:%s Age:%d Score:%d\n",p->name,p->age,p->score);
}

int MyCompare(CircleLinkNode* data1, CircleLinkNode* data2){
	Person* p1 = (Person*)data1;
	Person* p2 = (Person*)data2;

	if (strcmp(p1->name,p2->name) ==0 && p1->age == p2->age&& p1->score == p2->score){
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}

int main(void){
	
	//创建循环链表
	CircleLinkList* clist = Init_CircleLinkList();

	//创建数据
	Person p1, p2, p3, p4, p5;
	strcpy(p1.name, "aaa");
	strcpy(p2.name, "bbb");
	strcpy(p3.name, "ccc");
	strcpy(p4.name, "ddd");
	strcpy(p5.name, "eee");

	p1.age = 10;
	p2.age = 20;
	p3.age = 30;
	p4.age = 40;
	p5.age = 50;

	p1.score = 50;
	p2.score = 50;
	p3.score = 60;
	p4.score = 65;
	p5.score = 70;


	//数据入链表
	Insert_CircleLinkList(clist, 100, (CircleLinkNode*)&p1);
	Insert_CircleLinkList(clist, 100, (CircleLinkNode*)&p2);
	Insert_CircleLinkList(clist, 100, (CircleLinkNode*)&p3);
	Insert_CircleLinkList(clist, 100, (CircleLinkNode*)&p4);
	Insert_CircleLinkList(clist, 100, (CircleLinkNode*)&p5);

	//打印
	Print_CircleLinkList(clist, MyPrint);


	Person pDel;
	strcpy(pDel.name,"ddd");
	pDel.age = 40;
	pDel.score = 65;

	//根据值删除
	RemoveByValue_CircleLinkList(clist, (CircleLinkNode*)&pDel, MyCompare);


	//打印
	printf("--------------\n");
	Print_CircleLinkList(clist, MyPrint);

	//释放内存
	FreeSpace_CircleLinkList(clist);




	system("pause");
	return 0;
}



-- 02 约瑟夫问题
--  CircleLinkList.h

#ifndef CIRCLELINKLIST
#define CIRCLELINKLIST

#include<stdio.h>
#include<stdlib.h>

//链表的小结点
typedef struct CIRCLELINKNODE{
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

//链表结构体
typedef struct CIRCLELINKLIST{
	CircleLinkNode head;
	int size;
}CircleLinkList;

//编写针对链表结构体操作的API函数

#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALSE 0

//比较回调
typedef int(*COMPARENODE)(CircleLinkNode*, CircleLinkNode*);
//打印回调
typedef void(*PRINTNODE)(CircleLinkNode*);

//初始化函数
CircleLinkList* Init_CircleLinkList();
//插入函数
void Insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data);
//获得第一个元素
CircleLinkNode* Front_CircleLinkList(CircleLinkList* clist);
//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList* clist,int pos);
//根据值去删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//获得链表的长度
int Size_CircleLinkList(CircleLinkList* clist);
//判断是否为空
int IsEmpty_CircleLinkList(CircleLinkList* clist);
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//打印节点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print);
//释放内存
void FreeSpace_CircleLinkList(CircleLinkList* clist);

#endif

--  CircleLinkList.c

#include"CircleLinkList.h"

//初始化函数
CircleLinkList* Init_CircleLinkList(){

	CircleLinkList* clist = (CircleLinkList*)malloc(sizeof(CircleLinkList));
	clist->head.next = &(clist->head);
	clist->size = 0;

	return clist;
}

//插入函数
void Insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data){
	
	if (clist == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	if (pos <0 || pos > clist->size){
		pos = clist->size;
	}

	//根据位置查找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos;i++){
		pCurrent = pCurrent->next;
	}

	//新数据入链表
	data->next = pCurrent->next;
	pCurrent->next = data;

	clist->size ++;
}
//获得第一个元素
CircleLinkNode* Front_CircleLinkList(CircleLinkList* clist){
	return clist->head.next;
}
//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList* clist, int pos){

	if (clist == NULL){
		return;
	}

	if (pos < 0 || pos >= clist->size){
		return;
	}

	//根据pos找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos;i++){
		pCurrent = pCurrent->next;
	}
	
	//缓存当前结点的下一个结点
	CircleLinkNode* pNext = pCurrent->next;
	pCurrent->next = pNext->next;
	
	clist->size--;
}
//根据值去删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare){

	if (clist == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	//这个是循环链表
	CircleLinkNode* pPrev = &(clist->head);
	CircleLinkNode* pCurrent = pPrev->next;
	int i = 0;
	for (i = 0; i < clist->size; i++){
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE){
			pPrev->next = pCurrent->next;
			clist->size--;
			break;
		}
		pPrev = pCurrent;
		pCurrent = pPrev->next;
	}
}
//获得链表的长度
int Size_CircleLinkList(CircleLinkList* clist){
	return clist->size;
}
//判断是否为空
int IsEmpty_CircleLinkList(CircleLinkList* clist){
	if (clist->size == 0){
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare){

	if (clist == NULL){
		return -1;
	}

	if (data == NULL){
		return -1;
	}

	CircleLinkNode* pCurrent = clist->head.next;
	int flag = -1;
	for (int i = 0; i < clist->size; i ++){
		if (compare(pCurrent,data) == CIRCLELINKLIST_TRUE){
			flag = i;
			break;
		}
		pCurrent = pCurrent->next;
	}

	return flag;
}
//打印节点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print){
		
	if (clist == NULL){
		return;
	}
	
	//辅助指针变量
	CircleLinkNode* pCurrent = clist->head.next;
	for (int i = 0; i < clist->size;i++){
		if (pCurrent == &(clist->head)){
			pCurrent = pCurrent->next;
			printf("------------------\n");
		}
		print(pCurrent);
		pCurrent = pCurrent->next;
	}

}
//释放内存
void FreeSpace_CircleLinkList(CircleLinkList* clist){

	if (clist == NULL){
		return;
	}
	free(clist);
}

-- 源.c 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircleLinkList.h"

#define M 8
#define N 3

typedef struct MYNUM{
	CircleLinkNode node;
	int val;
}MyNum;

void MyPrint(CircleLinkNode* data){
	MyNum* num = (MyNum*)data;
	printf("%d ",num->val);
}

int MyCompare(CircleLinkNode* data1, CircleLinkNode* data2){
	MyNum* num1 = (MyNum*)data1;
	MyNum* num2 = (MyNum*)data2;
	if (num1->val == num2->val){
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}

int main(void){

	//创建循环链表
	CircleLinkList* clist = Init_CircleLinkList();
	//链表插入数据
	MyNum num[M];
	for (int i = 0; i < 8;i ++){
		num[i].val = i + 1;
		Insert_CircleLinkList(clist, i, (CircleLinkNode*)&num[i]);
	}

	//打印
	Print_CircleLinkList(clist, MyPrint);
	printf("\n");


	int index = 1;
	//辅助指针
	CircleLinkNode* pCurrent = clist->head.next;
	while (Size_CircleLinkList(clist) > 1){
		
		if (index == N){
			
			MyNum* temNum = (MyNum*)pCurrent;
			printf("%d ", temNum->val);

			//缓存待删除结点的下一个结点
			CircleLinkNode* pNext = pCurrent->next;
			//根据值删除
			RemoveByValue_CircleLinkList(clist, pCurrent, MyCompare);
			pCurrent = pNext;
			if (pCurrent == &(clist->head)){
				pCurrent = pCurrent->next;
			}
			index = 1;
		}

		pCurrent = pCurrent->next;
		if (pCurrent == &(clist->head)){
			pCurrent = pCurrent->next;
		}
		index++;
	}

	if (Size_CircleLinkList(clist) == 1){
		MyNum* tempNum = (MyNum*)Front_CircleLinkList(clist);
		printf("%d ",tempNum->val);
	}
	else{
		printf("出错!");
	}

	printf("\n");

	//释放链表内存
	FreeSpace_CircleLinkList(clist);
	



	system("pause");
	return 0;
}



-- 03 栈的顺序存储

-- SeqStack.h

#ifndef SEQSTACK_H
#define SEQSTACK_H

#include<stdlib.h>
#include<stdio.h>

//数组去模拟栈的顺序存储
#define MAX_SIZE 1024
#define SEQSTACK_TRUE 1
#define SEQSTACK_FALSE 0

typedef struct SEQSTACK{
	void* data[MAX_SIZE];
	int size;
}SeqStack;

//初始化栈
SeqStack* Init_SeqStack();
//入栈
void Push_SeqStack(SeqStack* stack,void* data);
//返回栈顶元素
void* Top_SeqStack(SeqStack* stack);
//出栈
void Pop_SeqStack(SeqStack* stack);
//判断是否为空
int IsEmpty(SeqStack* stack);
//返回栈中元素的个数
int Size_SeqStack(SeqStack* stack);
//清空栈
void Clear_SeqStack(SeqStack* stack);
//销毁
void FreeSpace_SeqStack(SeqStack* stack);



#endif

--  SeqStack.c

#include"SeqStack.h"

//初始化栈
SeqStack* Init_SeqStack(){

	SeqStack* stack = (SeqStack*)malloc(sizeof(SeqStack));
	for (int i = 0; i < MAX_SIZE;i++){
		stack->data[i] = NULL;
	}
	stack->size = 0;

	return stack;
}
//入栈
void Push_SeqStack(SeqStack* stack, void* data){

	if (stack == NULL){
		return;
	}
	if (stack->size == MAX_SIZE){
		return;
	}
	if (data == NULL){
		return;
	}

	stack->data[stack->size] = data;
	stack->size++;
}
//返回栈顶元素
void* Top_SeqStack(SeqStack* stack){
	if (stack == NULL){
		return NULL;
	}

	if (stack->size == 0){
		return NULL;
	}

	return stack->data[stack->size-1];
}
//出栈
void Pop_SeqStack(SeqStack* stack){
	if (stack == NULL){
		return;
	}
	if (stack->size == 0){
		return;
	}
	stack->data[stack->size - 1] = NULL;
	stack->size--;
}
//判断是否为空
int IsEmpty(SeqStack* stack){
	if (stack == NULL){
		return -1;
	}

	if (stack->size == 0){
		return SEQSTACK_TRUE;
	}

	return SEQSTACK_FALSE;
}
//返回栈中元素的个数
int Size_SeqStack(SeqStack* stack){
	return stack->size;
}
//清空栈
void Clear_SeqStack(SeqStack* stack){
	if (stack == NULL){
		return;
	}
	for (int i = 0; i < stack->size;i++){
		stack->data[i] = NULL;
	}
	stack->size = 0;
}
//销毁
void FreeSpace_SeqStack(SeqStack* stack){

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
#include "SeqStack.h"

typedef struct PERSON{
	char name[64];
	int age;
}Person;

int main(void){
	
	//创建栈
	SeqStack* stack = Init_SeqStack();

	//创建数据
	Person p1 = { "aaa", 10 };
	Person p2 = { "bbb", 20 };
	Person p3 = { "ccc", 30 };
	Person p4 = { "ddd", 40 };
	Person p5 = { "eee", 50 };

	//入栈
	Push_SeqStack(stack, &p1);
	Push_SeqStack(stack, &p2);
	Push_SeqStack(stack, &p3);
	Push_SeqStack(stack, &p4);
	Push_SeqStack(stack, &p5);

	//输出
	while (Size_SeqStack(stack) > 0){
		//访问栈顶元素
		Person* person = (Person*)Top_SeqStack(stack);
		printf("Name:%s Age:%d\n",person->name,person->age);
		//弹出栈顶元素
		Pop_SeqStack(stack);
	}

	//释放内存
	FreeSpace_SeqStack(stack);

	system("pause");
	return 0;
}


-- 04 栈的链式存储

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

typedef struct PERSON{
	LinkNode node;
	char name[64];
	int age;
}Person;

int main(void){
	
	//创建栈
	LinkStack* stack = Init_LinkStack();

	//创建数据
	Person p1, p2, p3, p4, p5;
	strcpy(p1.name, "aaa");
	strcpy(p2.name, "bbb");
	strcpy(p3.name, "ccc");
	strcpy(p4.name, "ddd");
	strcpy(p5.name, "eee");

	p1.age = 10;
	p2.age = 20;
	p3.age = 30;
	p4.age = 40;
	p5.age = 50;

	//入栈
	Push_LinkStack(stack, (LinkNode*)&p1);
	Push_LinkStack(stack, (LinkNode*)&p2);
	Push_LinkStack(stack, (LinkNode*)&p3);
	Push_LinkStack(stack, (LinkNode*)&p4);
	Push_LinkStack(stack, (LinkNode*)&p5);

	//输出
	while (Size_LinkStack(stack) > 0){
		
		//取出栈顶元素
		Person* p = (Person*)Top_LinkStack(stack);
		printf("Name:%s Age:%d\n",p->name,p->age);
		//弹出栈顶元素
		Pop_LinkStack(stack);
	}

	//销毁栈
	FreeSpace_LinkStack(stack);

	system("pause");
	return 0;
}

--  05 队列的顺序存储

--  SeqQueue.h 

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include<stdlib.h>
#include<stdio.h>
#define MAX_SIZE 1024


//顺序队列结构体
typedef struct SEQQUEUE{
	void* data[MAX_SIZE];
	int size;
}SeqQueue;

//初始化
SeqQueue* Init_SeqQueue();
//入队
void Push_SeqQueue(SeqQueue* queue,void* data);
//返回队头元素
void* Front_SeqQueue(SeqQueue* queue);
//出队
void Pop_SeqQueue(SeqQueue* queue);
//返回队尾元素
void* Back_SeqQueue(SeqQueue* queue);
//返回大小
int Size_SeqQueue(SeqQueue* queue);
//清空队列
void Clear_SeqQueue(SeqQueue* queue);
//销毁
void FreeSpace_SeqQueue(SeqQueue* queue);



#endif

--  SeqQueue.c 

#include "SeqQueue.h"

//初始化
SeqQueue* Init_SeqQueue() {

	SeqQueue* queue = (SeqQueue*)malloc(sizeof(SeqQueue));
	for (int i = 0; i < MAX_SIZE;i ++){
		queue->data[i] = NULL;
	}
	queue->size = 0;

	return queue;
}
//入队
void Push_SeqQueue(SeqQueue* queue, void* data){

	//数组左边当做队头
	if (queue == NULL){
		return;
	}

	if (data == NULL){
		return;
	}

	if (queue->size == MAX_SIZE){
		return;
	}

	queue->data[queue->size] = data;
	queue->size++;
}
//返回队头元素
void* Front_SeqQueue(SeqQueue* queue){

	if (queue == NULL){
		return NULL;
	}
	if (queue->size ==0){
		return NULL;
	}
	return queue->data[0];
}
//出队
void Pop_SeqQueue(SeqQueue* queue){

	//需要移动元素
	if (queue == NULL){
		return;
	}

	if (queue->size == 0){
		return;
	}

	for (int i = 0; i < queue->size - 1;i ++){
		queue->data[i] = queue->data[i + 1];
	}

	queue->size--;
}
//返回队尾元素
void* Back_SeqQueue(SeqQueue* queue){
	if (queue == NULL){
		return NULL;
	}
	if (queue->size == 0){
		return NULL;
	}

	return queue->data[queue->size-1];
}
//返回大小
int Size_SeqQueue(SeqQueue* queue){
	if (queue == NULL){
		return -1;
	}
	return queue->size;
}
//清空队列
void Clear_SeqQueue(SeqQueue* queue){

	if (queue == NULL){
		return;
	}
	queue->size = 0;
}
//销毁
void FreeSpace_SeqQueue(SeqQueue* queue){
	if (queue == NULL){
		return;
	}

	free(queue);
}


--   

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SeqQueue.h"

typedef struct PERSON{
	char name[64];
	int age;
}Person;

int main(void){
	
	//创建队列
	SeqQueue* queue = Init_SeqQueue();

	//创建数据
	Person p1 = { "aaa", 10 };
	Person p2 = { "bbb", 20 };
	Person p3 = { "ccc", 30 };
	Person p4 = { "ddd", 40 };
	Person p5 = { "eee", 50 };

	//数据入队列
	Push_SeqQueue(queue, &p1);
	Push_SeqQueue(queue, &p2);
	Push_SeqQueue(queue, &p3);
	Push_SeqQueue(queue, &p4);
	Push_SeqQueue(queue, &p5);

	//输出队尾元素
	Person* backPerson = (Person*)Back_SeqQueue(queue);
	printf("Name:%s Age:%d\n",backPerson->name,backPerson->age);

	//输出
	while (Size_SeqQueue(queue) > 0){
		//取出队头元素
		Person* p = (Person*)Front_SeqQueue(queue);
		printf("Name:%s Age:%d\n",p->name,p->age);
		//从队头弹出元素
		Pop_SeqQueue(queue);
	}

	


	//销毁队列
	FreeSpace_SeqQueue(queue);

	system("pause");
	return 0;
}














 


