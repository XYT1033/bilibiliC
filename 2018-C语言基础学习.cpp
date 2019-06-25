


 
 -- 7 
 #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(int argc, char *argv[])
{	
	int arr[] = { 1,2,3,4,5 ,'a','b'};
	int*  p ;  //数组名是数组首元素地址
	p = arr;
	printf("%p\n",p);
	printf("%p\n", arr);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n",arr[i]);
		printf("%d\n", p[i]);
	}


	getchar();
	return 0;
}












