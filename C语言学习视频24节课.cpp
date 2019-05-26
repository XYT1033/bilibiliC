
  无法打开包括文件: “stdafx.h”: No such file or directory	https://blog.csdn.net/wangw_5/article/details/83774475

  
  
  
  
  
  
  
  



#include <stdio.h>
#include <tchar.h>

#define PI 3.1415  // 如果改为3又是一个int 类型 ，不能 检测类型错误 
#define FUN(X,Y) ((X)*(Y))

int _tmain(int argc, _TCHAR* argv[])
{
	int pi = 3.434222343343;  // 能 检测类型错误
	printf("PI=%lf,pi=%f\n",PI,pi);
	int q = FUN(10+10,20+10);

	printf("PI=%lf,pi=%f q=%d\n",PI,pi,q);
	printf("__line__ = %d  ,  __file__=%s\n", __LINE__, __FILE__);

	getchar();
	return 0;

}






















