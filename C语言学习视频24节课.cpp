
  无法打开包括文件: “stdafx.h”: No such file or directory	https://blog.csdn.net/wangw_5/article/details/83774475

  
  
  
  
  
  
  
  

#include <stdio.h>
#include <tchar.h>

#define PI 3.1415  // 如果改为3又是一个int 类型 ，不能 检测类型错误 

int _tmain(int argc, _TCHAR* argv[])
{
	int pi = 3.434222343343;  // 能 检测类型错误
	printf("PI=%lf,pi=%f\n",PI,pi);

	getchar();
	return 0;

}