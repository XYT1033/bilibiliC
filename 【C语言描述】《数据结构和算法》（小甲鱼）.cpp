



-- NotThisVideo 		读取二进制文件到char*	https://blog.csdn.net/jiangyong9753/article/details/82924053 
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(void)
{
	
	//读取文件  
	ifstream in;
	in.open("E:\\XYT\\screenshot\\basketball.png", ios::binary);//1.bin是二进制文件
	in.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	in.seekg(0, ios_base::end);//移动到文件末尾
	ifstream::pos_type len = in.tellg();//取得当前位置的指针长度->即文件长度
	in.seekg(0, ios_base::beg);//重新定位指针到文件开始处
	char *pBuf = NULL;
	pBuf = new char[len];
	in.read(pBuf, sizeof(char)*len);
	in.close();

	//写入刚才读取的文件
	ofstream out;
	out.open("E:\\XYT\\screenshot\\aws_write.png", ios::binary);//2.bin是二进制文件
	//out.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	out.write(pBuf, sizeof(char)*len);
	out.close();

	delete[]pBuf;



	getchar();
	return 0;
}
 


-- NotThisVideo  			https://www.runoob.com/cprogramming/c-file-io.html
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
using namespace std;

int main(void)
{
	
	FILE *fp = NULL;
	char buff[255];

	fp = fopen("E:\\XYT\\screenshot\\basketball.png", "r");
	fscanf(fp, "%s", buff);
	printf("1: %s\n", buff);

	fgets(buff, 255, (FILE*)fp);
	printf("2: %s\n", buff);

	fgets(buff, 255, (FILE*)fp);
	printf("3: %s\n", buff);
	fclose(fp);


	getchar();
	return 0;
}



 -- NotThisVideo    need Improvement		
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>　
#include <stdio.h>　
#include <conio.h>　
int main(void)
{
	FILE *fp;
	char string[] = "This is a test";
	int ch;
	char *buffer;


	fp = fopen("E:\\XYT\\screenshot\\v.txt", "r");
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp); //		获取文件大小C程序： https://www.cnblogs.com/klcf0220/p/5625086.html
	buffer = new char[size];
	fgets(buffer, size, (FILE*)fp);


	FILE *fpW;
	fpW = fopen("E:\\XYT\\screenshot\\vX.txt", "w");
	fseek(fpW, 0L, SEEK_END);
	fputs(buffer, fpW);
	
	return 0;
}


 

 --7  
 
 
 
 
 
 
 
 
 
 
 