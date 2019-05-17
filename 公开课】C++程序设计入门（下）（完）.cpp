


-- 7.6

#include<iostream>								//预处理命令
#include<fstream>

using namespace std;

int main()
{
	fstream binaryio;
	binaryio.open("E:\\XYT\\screenshot\\aws.png", ios::out | ios::binary);
	int value;
	binaryio.read(reinterpret_cast<char*>(&value), sizeof(value));
	cout << value;
	binaryio.close();
	system("pause");
	return 0;

}


--   

#include <iostream> // c++ 通过数据流方式实现文件拷贝  https://www.cnblogs.com/northeastTycoon/p/9294323.html 
#include<fstream>
using namespace std;
void copy(char* src, char* dst);

int main()
{

	// 源文件地址及文件名
	char src[50] = "E:\\XYT\\screenshot\\office.png";

	// 拷贝的目的及文件名称 
	char dst[50] = "E:\\XYT\\screenshot\\office01.png";

	copy(src, dst);

	return 0;
}

// 文件拷贝实现方法
void copy(char* src, char* dst)
{
	using namespace std;
	ifstream in(src, ios::binary);
	ofstream out(dst, ios::binary);
	if (!in.is_open()) {
		cout << "error open file " << src << endl;
		exit(EXIT_FAILURE);
	}
	if (!out.is_open()) {
		cout << "error open file " << dst << endl;
		exit(EXIT_FAILURE);
	}
	if (src == dst) {
		cout << "the src file can't be same with dst file" << endl;
		exit(EXIT_FAILURE);
	}
	char buf[2048];
	long long totalBytes = 0;
	while (in)
	{
		//read从in流中读取2048字节，放入buf数组中，同时文件指针向后移动2048字节
		//若不足2048字节遇到文件结尾，则以实际提取字节读取。
		in.read(buf, 2048);
		//gcount()用来提取读取的字节数，write将buf中的内容写入out流。
		out.write(buf, in.gcount());
		totalBytes += in.gcount();
	}
	in.close();
	out.close();
}


-- 7.7 
#include <iostream>
#include<fstream>
using namespace std;

int main()
{
	const int SIZE = 5;
	fstream binaryio;

	//
	binaryio.open("array.dat",ios::out |ios::binary);
	double array[SIZE] = { 3.4,6.7,4.5,7.45};
	binaryio.write(reinterpret_cast<char*>(array),sizeof(array));
	binaryio.close();

	//
	binaryio.open("array.dat",ios::in|ios::binary);
	double result[SIZE];
	binaryio.read(reinterpret_cast<char*>(result),sizeof(result));
	cout << sizeof(result) << "" <<endl;
	binaryio.close();

	for (int i = 0; i < SIZE; i++)
	{
		cout << result[i] << "" << endl;
	}
	
	system("pause");
	return 0;
}






#include <iostream> //   c语言如何获取一个文件字节大小 	https://zhidao.baidu.com/question/2119897656052052307.html

int main()
{
	struct stat st;
	stat("E:\\XYT\\screenshot\\office.png", &st);
	printf(" file size = %d\n", st.st_size);
	
	system("pause");
	return 0;
}







#define _CRT_SECURE_NO_WARNINGS
#include <iostream> // C 语言File   https://www.cnblogs.com/saolv/p/7793379.html
#include<fstream>
using namespace std;

int main()
{
	FILE* pReadFile = fopen("E:\\XYT\\screenshot\\office.png", "r");   // 打开文件　　
	if (pReadFile == NULL)

		return 0;

	fclose(pReadFile);     // 关闭文件


	return 0;
}

 
 
 
 #define _CRT_SECURE_NO_WARNINGS		// C 语言File   https://www.cnblogs.com/saolv/p/7793379.html    https://www.cnblogs.com/saolv/p/7793379.html  
#include <stdio.h>
void main(int argc, char *argv[]) //命令行参数
{
	argc = 3;//i knock 
	int ch;
	FILE *in, *out; //定义in和out两个文件类型指针
	if (argc != 3) //判断命令行是否正确
	{
		printf("Error in format,Usage: copyfile filename1 filename2\n");
		return; //命令行错，结束程序的执行
	}
	//按读方式打开由argv[1]指出的文件
	if ((in = fopen("D:\\project_c++\\bilibili_c++\\office.png", "r")) == NULL) //  argv[1] alter :  "D:\project_c++\bilibili_c++\\office.png"
	{
		printf("The file <%s> can not be opened.\n", argv[1]);
		return; //打开失败，结束程序的执行
	}
	//成功打开了argv[1]所指文件，再
	//按写方式打开由argv[2]指出的文件
	if ((out = fopen("D:\\project_c++\\bilibili_c++\\office3.png", "w")) == NULL) //   argv[2] alter :  "D:\project_c++\bilibili_c++\\office2.png"
	{
		printf("The file %s can not be opened.\n", argv[2]);
		return; //打开失败，结束程序的执行
	}
	//成功打开了argv[2]所指文件
	ch = fgetc(in); //从in所指文件的当前指针位置读取一个字符
	while (ch != EOF) //判断刚读取的字符是否是文件结束符
	{
		fputc(ch, out); //若不是结束符，将它写入out所指文件
		ch = fgetc(in); //继续从in所指文件中读取下一个字符
	} //完成将in所指文件的内容写入（复制）到out所指文件中
	fclose(in); //关闭in所指文件
	fclose(out); //关闭out所指文件
}
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 







