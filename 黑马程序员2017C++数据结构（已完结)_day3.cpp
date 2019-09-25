
--  01 栈的应用_就近匹配

-- LinkStack.h

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


-- LinkStack.c

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
#include"LinkStack.h"

typedef struct MYCHAR{
	LinkNode node;
	char* pAddres;
	int index;
}MyChar;

int IsLeft(char c){
	return c == '(';
}

int IsRight(char c){
	return c == ')';
}

MyChar* CreateMyChar(char* p,int index){
	MyChar* mychar = (MyChar*)malloc(sizeof(MyChar));
	mychar->pAddres = p;
	mychar->index = index;

	return mychar;
}

void ShowError(char* str,int pos){
	printf("%s\n",str);
	for (int i = 0; i < pos;i ++){
		printf(" ");
	}
	printf("A");
}

int main(void){


	char* str = "1+2+6(dsf)df)sflp(sdfs)";

	//创建栈容器
	LinkStack* stack = Init_LinkStack();

	char* p = str;
	int index = 0;
	while (*p != '\0'){
	
		//如果左括号 直接进栈
		if (IsLeft(*p)){
			Push_LinkStack(stack, (LinkNode*)CreateMyChar(p,index));
		}

		//如果是右括号 从栈顶弹出元素 判断是不是左括号
		if (IsRight(*p)){
			if (Size_LinkStack(stack) > 0){
				MyChar* mychar = (MyChar*)Top_LinkStack(stack);
				if (IsLeft(*(mychar->pAddres))){
					Pop_LinkStack(stack);
					free(mychar);
				}
			}
			else{
				printf("右括号没有匹配的左括号:\n");
				ShowError(str,index);
				break;
			}
		}

		p++;
		index++;
	}


	while (Size_LinkStack(stack) > 0){
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);
		printf("左括号没有匹配的右括号:\n");
		ShowError(str, mychar->index);
		Pop_LinkStack(stack);
		free(mychar);
	}

	printf("\n");


	system("pause");
	return 0;
}


--  02 栈的应用_中缀表达式转后缀表达式

-- LinkStack.h 

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

-- LinkStack.c

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

//判断是否是数字
int IsNumber(char c){
	return c >= '0' && c <= '9';
}

//判断是不是左括号
int IsLeft(char c){
	return c == '(';
}

//判断是不是右括号
int IsRight(char c){
	return c == ')';
}

//判断是不是运算符号
int IsOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

//返回运算符号优先级
int GetPriority(char c){
	if (c == '*' || c == '/'){
		return 2;
	}
	if (c == '+' || c == '-'){
		return 1;
	}
	return 0;
}

typedef struct MYCHAR{
	LinkNode node;
	char* p;
}MyChar;

//数字操作
void NumberOperate(char* p){
	printf("%c", *p);
}

//创建MyChar
MyChar* CreateMyChar(char* p){
	MyChar* mychar = (MyChar*)malloc(sizeof(MyChar));
	mychar->p = p;
	return mychar;
}

//左括号的操作
void LeftOperate(LinkStack* stack, char* p){
	Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
}

//右括号操作
void RightOperate(LinkStack* stack){

	//先判断栈中有没有元素
	while (Size_LinkStack(stack) > 0){
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);
		//如果匹配到左括号
		if (IsLeft(*(mychar->p))){
			Pop_LinkStack(stack);
			free(mychar);
			break;
		}
		//输出
		printf("%c", *(mychar->p));
		//弹出
		Pop_LinkStack(stack);
		//释放内存
		free(mychar);
	}
}

//运算符号的操作
void OperatorOperate(LinkStack* stack, char* p){

	//先取出栈顶符号
	MyChar* mychar = (MyChar*)Top_LinkStack(stack);
	if (mychar == NULL){
		Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
		return;
	}
	//如果栈顶优先级低于当前字符的优先级 直接入栈
	if (GetPriority(*(mychar->p)) < GetPriority(*p)){
		Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
		//return;
	}

	//如果栈顶符号优先级不低
	else{

		while (Size_LinkStack(stack) > 0){

			MyChar* mychar2 = (MyChar*)Top_LinkStack(stack);

			//如果优先级低 当前符号入栈
			if (GetPriority(*(mychar2->p)) < GetPriority(*p)){
				Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
				return;
			}

			//输出
			printf("%c", *(mychar2->p));
			//弹出
			Pop_LinkStack(stack);
			//释放
			free(mychar2);
		}
	}

}


int main01(void){

	char* str = "8+(3-1)*5";
	char* p = str;

	//创建栈
	LinkStack* stack = Init_LinkStack();

	while (*p != '\0'){

		//如果是数字
		if (IsNumber(*p)){
			NumberOperate(p);
		}

		//如果左括号 直接进栈
		if (IsLeft(*p)){
			LeftOperate(stack, p);
		}

		//如果是右括号
		if (IsRight(*p)){
			RightOperate(stack);
		}

		//如果是运算符号
		if (IsOperator(*p)){
			OperatorOperate(stack, p);
		}
		p++;
	}

	while (Size_LinkStack(stack) > 0){
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);
		printf("%c", *(mychar->p));
		Pop_LinkStack(stack);
		free(mychar);
	}


	system("pause");
	return 0;
}

--

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkStack.h"

int IsNumber2(char c){
	return c >= '0' && c <= '9';
}

typedef struct MYNUM{
	LinkNode node;
	int val;
}MyNum;


int Caculate(int left,int right,char c){

	int ret = 0;
	switch (c)
	{
	case '+':
		ret = left + right;
		break;
	case '-':
		ret = left - right;
		break;
	case '*':
		ret = left * right;
		break;
	case '/':
		ret = left / right;
		break;
	default:
		break;
	}

	return ret;
}

int main(void){
	
	//后缀表达式
	char* str = "831-5*+";
	char* p = str;

	//创建栈
	LinkStack* stack = Init_LinkStack();

	while(*p != '\0'){
		//如果是数字 直接入栈
		if (IsNumber2(*p)){
			MyNum* num = (MyNum*)malloc(sizeof(MyNum));
			num->val = *p - '0';
			Push_LinkStack(stack, (LinkNode*)num);
		}
		else{
		
			//先从栈中弹出右操作数
			MyNum* right = (MyNum*)Top_LinkStack(stack);
			int rightNum = right->val;
			Pop_LinkStack(stack);
			free(right);
			//取出左操作数
			MyNum* left = (MyNum*)Top_LinkStack(stack);
			int leftNum = left->val;
			Pop_LinkStack(stack);
			free(left);
			
			int ret = Caculate(leftNum, rightNum,*p);
			//结果入栈
			MyNum* num = (MyNum*)malloc(sizeof(MyNum));
			num->val = ret;
			Push_LinkStack(stack, (LinkNode*)num);
		}
		p++;
	}

	if (Size_LinkStack(stack) == 1){
		MyNum* num =  (MyNum*)Top_LinkStack(stack);
		printf("运算结果是:%d\n",num->val);
		Pop_LinkStack(stack);
		free(num);
	}

	//释放栈
	FreeSpace_LinkStack(stack);

	system("pause");
	return 0;
}



 
-- 03 二叉树编程实战_递归遍历 

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

//递归遍历
void Recursion(BinaryNode* root){

	if (root == NULL){
		return;
	}

	//再遍历左子树
	Recursion(root->lchild);
	//再遍历右子树
	Recursion(root->rchild);
	//先访问根结点
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

	//递归遍历
	Recursion(&node1);
	printf("\n");	
}


int main(void){
	
	CresteBinaryTree();

	system("pause");
	return 0;
}
 


-- 05 二叉树编程实战_求叶子节点数目 

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


void CaculateLeafNum(BinaryNode* root,int* leafNum){
	
	if (root == NULL){
		return;
	}

	if (root->lchild == NULL && root->rchild == NULL){
		(*leafNum)++;
	}
	//左子树叶子结点的数目
	CaculateLeafNum(root->lchild, leafNum);
	//右子树叶子结点的数目
	CaculateLeafNum(root->rchild,leafNum);

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

	int leafNum = 0;
	CaculateLeafNum(&node1, &leafNum);
	printf("叶子结点的数目:%d\n", leafNum);

}

int main(void){
	
	CresteBinaryTree();

	system("pause");
	return 0;
}



-- 06 二叉树编程实战_求树的深度 

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


//求二叉树的高度
int CaculateTreeDepth(BinaryNode* root){

	if (root == NULL){
		return 0;
	}

	int depth = 0;
	//求左子树的高度
	int leftDepth = CaculateTreeDepth(root->lchild);
	int rightDepth = CaculateTreeDepth(root->rchild);
	depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;

	return depth;
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

	int depth = CaculateTreeDepth(&node1);
	printf("树的高度为:%d\n",depth);

}


int main(void){
	
	CresteBinaryTree();
	system("pause");
	return 0;
}


--  07 二叉树编程实战_拷贝二叉树

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

//遍历二叉树
void Recursion(BinaryNode* root){

	if (root == NULL){
		return;
	}

	printf("%c",root->ch);
	//遍历左子树
	Recursion(root->lchild);
	//遍历右子树
	Recursion(root->rchild);


}

//拷贝二叉树
BinaryNode* CopyBinaryTree(BinaryNode* root){

	if (root == NULL){
		return NULL;
	}

	//拷贝左子树
	BinaryNode* lchild = CopyBinaryTree(root->lchild);
	//拷贝右子树
	BinaryNode* rchild = CopyBinaryTree(root->rchild);

	//创建结点
	BinaryNode* newnode = (BinaryNode*)malloc(sizeof(BinaryNode));
	newnode->ch = root->ch;
	newnode->lchild = lchild;
	newnode->rchild = rchild;

	return newnode;
}

//释放二叉树内存
void FreeSpaceBinaryTree(BinaryNode* root){

	if (root == NULL){
		return;
	}
	//释放左子树
	FreeSpaceBinaryTree(root->lchild);
	//释放右子树
	FreeSpaceBinaryTree(root->rchild);

	//释放当前结点
	free(root);
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

	BinaryNode* root = CopyBinaryTree(&node1);
	Recursion(root);
	FreeSpaceBinaryTree(root);
}

int main(void){
	
	CresteBinaryTree();
	system("pause");
	return 0;
}

 -- Test
 
--  Books.h 

#pragma once
#include <string>
#include <vector>
#include "Readers.h"
using namespace std;

class Books{

	friend ostream& operator<<(ostream&out, Books&anther);
	friend istream& operator>>(istream&in, Books&anther);

public:
	Books();			  //book类构造函数
	void set_id();		//设置书号
	string get_name();           //获取书名
	string get_writer();		  //获取作者
	vector<Reader>& get_vborrower();			  //获取借书人
	int get_id();				 //获取书号
	int get_borr_num();			 //获取借书人学号
	int get_store();			 //获取现存量
	int get_total();			 // 获取总存量
	string get_pub_time();		 //获取出版时间
	float get_price();			//获取价格
	string get_publish();		 //获取出版社
private:
	string name;        //书名
	string writer;      //作者
	vector<Reader> vborrower;//借书人
	int id;            //书号
	int store;         //现存量
	int total;         // 总存量
	string pub_time;   //出版时间
	float price;       //价格
	string publish;    //出版社

};

--  Readers.h

#pragma once
#include <string>
using namespace std;

class Reader{

	friend ostream& operator<<(ostream&out, Reader&anther);
	friend istream& operator>>(istream&in, Reader&anther);

public:
	Reader();
	int getnum();				 //获取读者学号函数
	string getgrade();		//获取读者年级函数
	string getclas();	    	//获取读者班级函数
	string getsex();			//获取读者性别函数
	string getbook_name();	//获取所借书书名函数
	string getdate();	        //获取借书日期函数
	string getname();         //获取读者姓名函数
	int  getavaiday();		//获取可借天数函数
	int setname(string); 		//设置读者姓名函数
	int setnum(int);         //设置读者学号函数
	int setgrade(string);     //设置读者年级函数
	int setclas(string);      //设置读者班级函数
	int setsex(string);	     //设置读者性别函数
	int setbook_name(string);	 //设置所借书籍书名函数
	int setdate(string);	     //设置借书日期函数
	int setavaiday(int);	     //设置可借天数函数
	void book_out();			//借书函数
	void book_in();			//还书函数

private:
	string name;                  //名字
	int	   num;                  //学号
	string grade;                 //年级
	string clas;                  //班级
	string sex;                   //性别
	string book_name;              //所借书的书名
	string date;                   //借书日期
	int avai_days;                  //可借天数
};



-- Books.cpp 

#include "Books.h"
#include <iostream>
#include <vector>
using namespace std;

Books::Books()    //book类构造函数
{
	this->name = "book";
	this->writer = "writer";
	//this->vborrower;
	this->id = 0;
	this->store = 0;
	this->total = 0;
	this->pub_time = "pub_time";
	this->price = 0.0;
	this->publish = "publish";
}

void  Books::set_id()		//设置书号
{
	cout << "请输入书籍编号（书籍编号从10001起，且不能和已有书籍重号）：" << endl;
}
string Books::get_name()           //获取书名
{
	return name;
}
string Books::get_writer()		  //获取作者
{
	return writer;
}

vector<Reader>& Books::get_vborrower()			  //获取借书人
{
	return vborrower;
}

int Books::get_id()				 //获取书号
{
	return id;
}

int Books::get_store()			 //获取现存量
{
	return store;
}
int Books::get_total()			 // 获取总存量
{
	return total;
}
string Books::get_pub_time()		 //获取出版时间
{
	return pub_time;
}
float  Books::get_price()	//获取价格
{
	return price;
}
string Books::get_publish()		 //获取出版社
{
	return publish;
}

ostream& operator<<(ostream&out, Books&anther)
{

	cout << "书名：" << anther.name;
	cout << "作者：" << anther.writer;
	cout << "书号：" << anther.id;
	cout << "现存量：" << anther.store;
	cout << "总数量：" << anther.total;
	cout << "出版时间：" << anther.pub_time;
	cout << "价格：" << anther.price;
	cout << "出版社：" << anther.publish;
	if (anther.total - anther.store > 0)
	{
		for (int i = 0; i < anther.total - anther.store; i++)
			cout << "借书读者" << i << "：" << anther.vborrower[i];
	}
	return out;
}

istream& operator>>(istream&in, Books&anther)
{

	cout << "请输入书名：" << endl; cin >> anther.name;
	cout << "请输入作者：" << endl; 	cin >> anther.writer;
	//cout << "请输入书籍编号：" << endl;	cin >> anther.id;
	cout << "请输入出版社：" << endl;	cin >> anther.store;
	cout << "请输入本书总数量：" << endl;	cin >> anther.total;
	cout << "请输入出版时间：" << endl;	cin >> anther.pub_time;
	cout << "请输入本书价格：" << endl; cin >> anther.price;
	cout << "请输入出版社：" << endl; cin >> anther.publish;
	if (anther.total - anther.store > 0)
	{
		for (int i = 0; i < anther.total - anther.store; i++)
		{
			cout << "请输入第" << i << "个借书读者：" << endl;
			cin >> anther.vborrower[i];
		}
	}
	return in;
}


--  index.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


using namespace std;

int main(void)
{
	
	return 0;
}

--  Readers.cpp

#include<iostream>
#include<string>
using namespace std;
#include "Readers.h"

Reader::Reader()
{

}

int Reader::getnum()			 //获取读者学号函数
{
	return num;
}
string Reader::getgrade()	//获取读者年级函数
{
	return grade;
}
string Reader::getclas()	    	//获取读者班级函数
{
	return clas;
}
string Reader::getsex()			//获取读者性别函数
{
	return sex;
}
string Reader::getbook_name()	//获取所借书书名函数
{
	return book_name;
}
string Reader::getdate()	        //获取借书日期函数
{
	return date;
}
string Reader::getname()         //获取读者姓名函数
{
	return name;
}
int Reader::getavaiday()		//获取可借天数函数
{
	return avai_days;
}
int Reader::setname(string)		//设置读者姓名函数
{
	cout << "请输入读者姓名：" << endl;
	cin >> this->name;
	return 0;
}
int Reader::setnum(int)         //设置读者学号函数
{
	cout << "请输入读者的学号（学号从10001起，且不能和已有读者学号相同）：" << endl;
	cin >> this->num;
	return 0;
}
int Reader::setgrade(string)     //设置读者年级函数
{
	cout << "请输入读者年级：" << endl;
	cin >> this->grade;
	return 0;
}
int Reader::setclas(string)      //设置读者班级函数
{
	cout << "请输入读者班级：" << endl;
	cin >> this->clas;
	return 0;
}
int Reader::setsex(string)	     //设置读者性别函数
{
	cout << "请输入读者性别：" << endl;
	cin >> this->sex;
	return 0;
}
int Reader::setbook_name(string)	 //设置所借书籍书名函数
{
	cout << "请输入读者所借书名：" << endl;
	cin >> this->book_name;
	return 0;
}
int Reader::setdate(string)	     //设置借书日期函数
{
	cout << "请输入读者结束日期：" << endl;
	cin >> this->date;
	return 0;
}
int Reader::setavaiday(int)	     //设置可借天数函数
{
	cout << "请输入读者可借天数：" << endl;
	cin >> this->clas;
	return 0;
}
void Reader::book_out()			//借书函数
{

}
void Reader::book_in()			//还书函数
{

}
ostream& operator<<(ostream&out, Reader&anther)
{

	cout << "读者姓名：" << anther.name << endl;
	cout << "读者学号" << anther.num << endl;
	cout << "读者年级" << anther.grade << endl;
	cout << "读者班级" << anther.clas << endl;
	cout << "读者性别" << anther.sex << endl;
	if (anther.book_name != "未借书")
	{
		cout << "读者所借书名" << anther.book_name << endl;
		cout << "读者借书日期" << anther.date << endl;
		cout << "读者可借天数" << anther.avai_days << endl;
	}

	return out;
}
istream& operator>>(istream&in, Reader& anther)
{
	cout << "请输入读者姓名：" << endl;
	cin >> anther.name;
	cout << "请输入读者年级：" << endl;
	cin >> anther.grade;
	cout << "请输入读者班级：" << endl;
	cin >> anther.clas;
	cout << "请输入读者性别：" << endl;
	cin >> anther.sex;
	return in;
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


