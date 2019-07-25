
-- 3 

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




-- 12





 





 