
 Search for the same   ： C语言】《带你学C带你飞》（小甲鱼）   





 
 
 -- 
 #include <stdio.h>

#define PRICE 30		


void main()
{
	int num, total;
	num = 10;
	total = num * PRICE;
	printf("total=%d\n",total);
	getchar();


}


-- 56 

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>　
#include <stdio.h>
int main()
{
	FILE* fp = fopen("E:\\XYT\\screenshot\\v.txt", "r");
	int ch;
	if (fp==NULL)
	{
		
	}
	while ((ch=getc(fp))!=EOF)
	{
		putchar(ch);
	}
	fclose(fp);

	getchar();
	return 0;
} 

--57 

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>　
#include <stdio.h>
int main()
{
	FILE* fp = fopen("E:\\XYT\\screenshot\\v.txt", "r");
	FILE* fpW = fopen("E:\\XYT\\screenshot\\v1.txt", "w");
	int ch;
	if (fp==NULL || fpW == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while ((ch=getc(fp))!=EOF)
	{
		fputc(ch,fpW);
	}


	fclose(fp);
	fclose(fpW);
	getchar();
	return 0;
}














