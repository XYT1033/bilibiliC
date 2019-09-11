
-- 3-5

-- DynamicArray.h
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//动态增长内存，策略 将存放数据的内存放到那？堆上
//动态数组 如果5个元素 申请内存 拷贝数据 释放内存6 插入第七个？ 
//容量capacity表示我的这块内存空间一共可以存放多少元素
//size概念 记录当前数组中具体的元素个数

//动态数组的结构体定义完了
typedef struct DYNAMICARRAY{
	int* pAddr; //存放数据的地址
	int size; //当前有多少个元素
	int capacity; //容量，我容器当前最大能容纳多少元素
}Dynamic_Array;

//写一系列的相关对DYNAMICARRAY结构体操作的函数
//初始化
Dynamic_Array* Init_Array();
//插入
void PushBack_Array(Dynamic_Array* arr,int value);
//根据位置删除
void RemoveByPos_Array(Dynamic_Array* arr,int pos);
//根据值删除
void RemoveByValue_Array(Dynamic_Array* arr, int value);
//查找
int Find_Array(Dynamic_Array* arr, int value);
//打印
void Print_Array(Dynamic_Array* arr);
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr);
//清空数组
void Clear_Array(Dynamic_Array* arr);
//获得动态数组容量
int Capacity_Array(Dynamic_Array* arr);
//获得动态数据当前元素个数
int Size_Array(Dynamic_Array* arr);
//根据位置获得某个位置元素
int At_Array(Dynamic_Array* arr,int pos);



#endif


-- DynamicArray.c

#include"DynamicArray.h"


//动态数组的初始化
Dynamic_Array* Init_Array(){

	//申请内存
	Dynamic_Array* myArray = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	//初始化
	myArray->size = 0;
	myArray->capacity = 20;
	myArray->pAddr = (int*)malloc(sizeof(int)*myArray->capacity);

	return myArray;
}
//插入
void PushBack_Array(Dynamic_Array* arr, int value){

	if (arr == NULL){
		return;
	}
	//判断空间是否足够
	if (arr->size == arr->capacity){	
		//第一步 申请一块更大的内存空间 新空间是旧空间的2倍
		int* newSpace = (int*)malloc(sizeof(int) * arr->capacity * 2);
		//第二步 拷贝数据到新的空间
		memcpy(newSpace,arr->pAddr,arr->capacity * sizeof(int));
		//第三步 释放旧空间的内存
		free(arr->pAddr);
		//更新容量
		arr->capacity = arr->capacity * 2;
		arr->pAddr = newSpace;
	}
	//插入新元素
	arr->pAddr[arr->size] = value;
	arr->size++;
}
//根据位置删除
void RemoveByPos_Array(Dynamic_Array* arr, int pos){

	if (arr == NULL){
		return;
	}
	
	//判断位置是否有效
	if(pos < 0 || pos >= arr->size){
		return;
	}

	//删除元素
	for (int i = pos; i < arr->size -1; i ++){
		arr->pAddr[i] = arr->pAddr[i + 1];
	}

	arr->size--;
}
//根据值删除value第一次出现的位置
void RemoveByValue_Array(Dynamic_Array* arr, int value){
	if (arr == NULL){
		return;
	}

	//找到值的位置
	int pos = Find_Array(arr,value);
	//根据位置删除
	RemoveByPos_Array(arr, pos);
}
//查找
int Find_Array(Dynamic_Array* arr, int value){

	if (arr == NULL){
		return -1;
	}
	//找到值的位置
	int pos = -1;
	for (int i = 0; i < arr->size; i++){
		if (arr->pAddr[i] == value){
			pos = i;
			break;
		}
	}

	return pos;
}
//打印
void Print_Array(Dynamic_Array* arr){
	if (arr == NULL){
		return;
	}
	for (int i = 0; i < arr->size;i++){
		printf("%d ",arr->pAddr[i]);
	}
	printf("\n");
}
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr){
	if (arr == NULL){
		return;
	}

	if (arr->pAddr != NULL){
		free(arr->pAddr);
	}
	free(arr);
}
//清空数组
void Clear_Array(Dynamic_Array* arr){
	if (arr == NULL){
		return;
	}
	//pAddr -> 空间
	arr->size = 0;
}
//获得动态数组容量
int Capacity_Array(Dynamic_Array* arr){
	if (arr == NULL){
		return -1;
	}
	return arr->capacity;
}
//获得动态数据当前元素个数
int Size_Array(Dynamic_Array* arr){
	if (arr == NULL){
		return -1;
	}
	return arr->size;
}
//根据位置获得某个位置元素
int At_Array(Dynamic_Array* arr, int pos){
	return arr->pAddr[pos];
}


-- 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"DynamicArray.h"


void test01(){

	//初始化动态数组
	Dynamic_Array* myArray = Init_Array();
	//打印容量
	printf("数组容量:%d\n", Capacity_Array(myArray));
	printf("数组大小:%d\n", Size_Array(myArray));
	//插入元素
	for (int i = 0; i < 30;i++){
		PushBack_Array(myArray, i);
	}
	printf("数组容量:%d\n", Capacity_Array(myArray));
	printf("数组大小:%d\n", Size_Array(myArray));
	//打印
	Print_Array(myArray);

	//删除
	RemoveByPos_Array(myArray,0);
	RemoveByValue_Array(myArray,27);
	//打印
	Print_Array(myArray);

	//查找5个位置
	int pos = Find_Array(myArray, 5);
	printf("5查找到:pos:%d %d\n", pos, At_Array(myArray, pos));

	//销毁
	FreeSpace_Array(myArray);
}

int main(void){
	
	test01();

	system("pause");
	return 0;
}


-- 6-9  
-- LinkList.h 
#ifndef LINKLIST_H
#define LINKLIST_H

#include<stdlib.h>
#include<stdio.h>

//链表结点
typedef struct LINKNODE {
	void* data;  //指向任何类型的数据
	struct LINKNODE* next;
}LinkNode;

//链表结构体
typedef struct LINKLIST {
	LinkNode* head;
	int size;
	//需要容量吗？没有容量的概念
}LinkList;

//打印函数指针
typedef void(*PRINTLINKNODE)(void*);

//初始化链表
LinkList* Init_LinkList();
//指定位置插入
void Insert_LinkList(LinkList* list, int pos, void* data);
//删除指定位置的值
void RemoveByPos_LinkList(LinkList* list, int pos);
//获得链表的长度
int Size_LinkList(LinkList* list);
//查找
int Find_LinkList(LinkList* list, void* data);
//返回第一个结点
void* Front_LinkList(LinkList* list);
//打印链表结点
void Print_LinkList(LinkList* list, PRINTLINKNODE print);
//释放链表内存
void FreeSpace_LinkList(LinkList* list);


#endif

-- LinkList.c
 
#include"LinkList.h"

//初始化链表
LinkList* Init_LinkList() {

	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	list->size = 0;

	//头结点 是不保存数据信息
	list->head = (LinkNode*)malloc(sizeof(LinkNode));
	list->head->data = NULL;
	list->head->next = NULL;

	return list;
}
//指定位置插入
void Insert_LinkList(LinkList* list, int pos, void* data) {

	if (list == NULL) {
		return;
	}
	if (data == NULL) {
		return;
	}

	//友好的处理，pos越界 
	if (pos < 0 || pos > list->size) {
		pos = list->size;
	}

	//创建新的结点
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
	newnode->data = data;
	newnode->next = NULL;

	//找结点
	//辅助指针变量
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++) {
		pCurrent = pCurrent->next;
	}

	//新结点入链表
	newnode->next = pCurrent->next;
	pCurrent->next = newnode;

	list->size++;

}
//删除指定位置的值
void RemoveByPos_LinkList(LinkList* list, int pos) {
	if (list == NULL) {
		return;
	}

	if (pos < 0 || pos >= list->size) {
		return;
	}

	//查找删除结点的前一个结点
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++) {
		pCurrent = pCurrent->next;
	}

	//缓存删除的结点
	LinkNode* pDel = pCurrent->next;
	pCurrent->next = pDel->next;
	//释放删除结点的内存
	free(pDel);

	list->size--;
}
//获得链表的长度
int Size_LinkList(LinkList* list) {
	return list->size;
}
//查找
int Find_LinkList(LinkList* list, void* data) {
	if (list == NULL) {
		return -1;
	}

	if (data == NULL) {
		return -1;
	}

	//遍历查找
	LinkNode* pCurrent = list->head->next;
	int i = 0;
	while (pCurrent != NULL) {
		if (pCurrent->data == data) {
			break;
		}
		i++;
		pCurrent = pCurrent->next;
	}

	return i;
}
//返回第一个结点
void* Front_LinkList(LinkList* list) {
	return list->head->next->data;
}
//打印链表结点
void Print_LinkList(LinkList* list, PRINTLINKNODE print) {
	if (list == NULL) {
		return;
	}
	//辅助指针变量
	LinkNode* pCurrent = list->head->next;
	while (pCurrent != NULL) {
		print(pCurrent->data);
		pCurrent = pCurrent->next;
	}

}
//释放链表内存
void FreeSpace_LinkList(LinkList* list) {

	if (list == NULL) {
		return;
	}

	//辅助指针变量
	LinkNode* pCurrent = list->head;
	while (pCurrent != NULL) {
		//缓存下一个结点
		LinkNode* pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}

	//释放链表内存
	list->size = 0;
	free(list);

}

-- 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"


//自定义数据类型
typedef struct PERSON {
	char name[64];
	int age;
	int score;
}Person;


//打印函数
void MyPrint(void* data) {
	Person* p = (Person*)data;
	printf("Name:%s Age:%d Score:%d\n", p->name, p->age, p->score);
}

int main(void) {


	//创建链表
	LinkList* list = Init_LinkList();

	//创建数据
	Person p1 = { "p1", 18, 100 };
	Person p2 = { "p2", 19, 99 };
	Person p3 = { "p3", 20, 101 };
	Person p4 = { "p4", 17, 97 };
	Person p5 = { "p5", 16, 59 };

	//数据插入链表
	Insert_LinkList(list, 0, &p1);
	Insert_LinkList(list, 0, &p2);
	Insert_LinkList(list, 0, &p3);
	Insert_LinkList(list, 0, &p4);
	Insert_LinkList(list, 0, &p5);

	//打印
	Print_LinkList(list, MyPrint);

	//删除3
	RemoveByPos_LinkList(list, 3);

	//打印
	printf("---------------\n");
	Print_LinkList(list, MyPrint);

	//返回第一个结点
	printf("-----查找结果------------\n");
	Person* ret = (Person*)Front_LinkList(list);
	printf("Name:%s Age:%d Score:%d\n", ret->name, ret->age, ret->score);

	//销毁链表
	FreeSpace_LinkList(list);

	system("pause");
	return 0;
}



 -- 15 

--  CircleLinkList.h
#ifndef CIRCLELINKLIST
#define CIRCLELINKLIST

#include<stdio.h>
#include<stdlib.h>

//链表的小结点
typedef struct CIRCLELINKNODE {
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

//链表结构体
typedef struct CIRCLELINKLIST {
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
void RemoveByPos_CircleLinkList(CircleLinkList* clist, int pos);
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


-- CircleLinkList.cpp
#include"CircleLinkList.h"

//初始化函数
CircleLinkList* Init_CircleLinkList() {

	CircleLinkList* clist = (CircleLinkList*)malloc(sizeof(CircleLinkList));
	clist->head.next = &(clist->head);
	clist->size = 0;

	return clist;
}

//插入函数
void Insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data) {

	if (clist == NULL) {
		return;
	}

	if (data == NULL) {
		return;
	}

	if (pos <0 || pos > clist->size) {
		pos = clist->size;
	}

	//根据位置查找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos; i++) {
		pCurrent = pCurrent->next;
	}

	//新数据入链表
	data->next = pCurrent->next;
	pCurrent->next = data;

	clist->size++;
}
//获得第一个元素
CircleLinkNode* Front_CircleLinkList(CircleLinkList* clist) {
	return clist->head.next;
}
//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList* clist, int pos) {

	if (clist == NULL) {
		return;
	}

	if (pos < 0 || pos >= clist->size) {
		return;
	}

	//根据pos找结点
	//辅助指针变量
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos; i++) {
		pCurrent = pCurrent->next;
	}

	//缓存当前结点的下一个结点
	CircleLinkNode* pNext = pCurrent->next;
	pCurrent->next = pNext->next;

	clist->size--;
}
//根据值去删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare) {

	if (clist == NULL) {
		return;
	}

	if (data == NULL) {
		return;
	}

	//这个是循环链表
	CircleLinkNode* pPrev = &(clist->head);
	CircleLinkNode* pCurrent = pPrev->next;
	int i = 0;
	for (i = 0; i < clist->size; i++) {
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE) {
			pPrev->next = pCurrent->next;
			clist->size--;
			break;
		}
		pPrev = pCurrent;
		pCurrent = pPrev->next;
	}
}
//获得链表的长度
int Size_CircleLinkList(CircleLinkList* clist) {
	return clist->size;
}
//判断是否为空
int IsEmpty_CircleLinkList(CircleLinkList* clist) {
	if (clist->size == 0) {
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare) {

	if (clist == NULL) {
		return -1;
	}

	if (data == NULL) {
		return -1;
	}

	CircleLinkNode* pCurrent = clist->head.next;
	int flag = -1;
	for (int i = 0; i < clist->size; i++) {
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE) {
			flag = i;
			break;
		}
		pCurrent = pCurrent->next;
	}

	return flag;
}
//打印节点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print) {

	if (clist == NULL) {
		return;
	}

	//辅助指针变量
	CircleLinkNode* pCurrent = clist->head.next;
	for (int i = 0; i < clist->size; i++) {
		if (pCurrent == &(clist->head)) {
			pCurrent = pCurrent->next;
			printf("------------------\n");
		}
		print(pCurrent);
		pCurrent = pCurrent->next;
	}

}
//释放内存
void FreeSpace_CircleLinkList(CircleLinkList* clist) {

	if (clist == NULL) {
		return;
	}
	free(clist);
}

-- 源.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"CircleLinkList.h"

typedef struct PERSON {
	CircleLinkNode node;
	char name[64];
	int age;
	int score;
}Person;

void MyPrint(CircleLinkNode* data) {
	Person* p = (Person*)data;
	printf("Name:%s Age:%d Score:%d\n", p->name, p->age, p->score);
}

int MyCompare(CircleLinkNode* data1, CircleLinkNode* data2) {
	Person* p1 = (Person*)data1;
	Person* p2 = (Person*)data2;

	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age&& p1->score == p2->score) {
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALSE;
}

int main(void) {

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
	strcpy(pDel.name, "ddd");
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

















 