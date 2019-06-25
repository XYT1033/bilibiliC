

-- 1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main01(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //元素个数

	printf("排序前\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");


	//选择法排序
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //升序
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

	printf("排序后\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	//如何看懂带算法的程序
	/*
	1、流程
	2、每个语句功能
	3、试数
	4、调试
	5、模仿改
	6、不看代码写
	*/








	printf("\n");
	system("pause");
	return 0;
}

//如果数组作为函数参数，数组形参退化为指针
//void print_array(int a[1], int n)
//void print_array(int a[], int n)
void print_array(int *a, int n)
{
	// a, 当做指针用，指针类型，32位，长度4个字节

	n = sizeof(a) / sizeof(a[0]); //元素个数
	printf("print_array: n = %d\n", n);

	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void sort_array(int a[10], int n)
{
	int i, j, tmp;

	//选择法排序
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) //升序
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int main(void)
{
	int a[] = { 10, 7, 1, 9, 4, 6, 7, 3, 2, 0 };
	int n;
	int i = 0;
	int j = 0;
	int tmp = 0;

	n = sizeof(a) / sizeof(a[0]); //元素个数
	printf("n = %d\n", n);

	printf("排序前：\n");
	print_array(a, n);

	sort_array(a, n);

	printf("排序后：\n");
	print_array(a, n);

	printf("\n");
	system("pause");
	return 0;
}

-- 2 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int a;		//告诉编译器，分配 4个字节
	int b[10];	//告诉编译器，分配 4 * 10 个字节

	/*类型的本质：固定内存块大小别名
	  可以通过 sizeof()测试
	*/

	printf("sizeof(a) = %d, sizeof(b) = %d\n", sizeof(a), sizeof(b));


	//打印地址
	//数组名字，数组首元素地址，数组首地址
	printf("b:%d， &b:%d\n", b, &b);


	//b, &b的数组类型不一样
	//b， 数组首元素地址， 一个元素4字节，+1， +4
	//&b, 整个数组的首地址，一个数组4*10  = 40字节，+1， +40
	printf("b+1:%d， &b+1:%d\n", b + 1, &b + 1);

	//指针类型长度，32位程序， 长度4
	//              64位程序， 长度8
	char ***********************p = NULL;
	int *q = NULL;
	printf("%d, %d\n", sizeof(p), sizeof(q));


	printf("\n");
	system("pause");
	return 0;
}
 
 
 --3  
 #define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;

//typedef和结构体结合使用
struct MyStruct
{
	int a;
	int b;
};

typedef struct MyStruct2
{
	int a;
	int b;
}TMP;

/* void, 无类型
1、函数参数为空，定义函数时，可以用void修饰:  int fun(void)
2、函数没有返回值：void fun(void);
3、不能定义void类型的普通变量： void a; //err,无法确定类型,不同类型分配空间不一样
4、可以定义void *变量： void *p; //ok， 32永远4字节，64永远8字节
5、数据类型本质：固定内存块大小别名
6、void *p万能指针，函数返回值，函数参数

*/

int main(void)
{
	u32 t; // unsigned int

	//定义结构体变量，一定要加上struct关键字
	struct MyStruct m1;
	//MyStruct m2; //err

	TMP m3;
	struct MyStruct2 m4;

	char buf[1024];
	strcpy(buf, "1111111111");


	printf("\n");
	system("pause");
	return 0;
}

--4 
 
 
 #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int *p = 0x11111;
	char ***************q = 0x11;

	printf("sizeof(p) = %d, sizeof(q) =%d\n", sizeof(p), sizeof(q));


	int a = 100;
	int *p1 = NULL;

	//指针指向谁，就把谁的地址赋值给指针
	p1 = &a;
	//*钥匙，通过*可以找到指针指向的内存区域，操作还是内存
	*p1 = 22;

	//*放在=左边，给内存赋值，写内存
	//*放在=右边，取内存的值，读内容
	int b = *p1;
	printf("b = %d\n", b);

	printf("\n");
	system("pause");
	return 0;
}




--5 


























 







