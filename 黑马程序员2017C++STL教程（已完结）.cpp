
--1 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#if 1 
//int类型数据交换
void MySwap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//double类型
void MySwap(double& a, double& b) {
	double temp = a;
	a = b;
	b = temp;
}
#endif

//模板技术 类型参数化 编写代码可以忽略类型
//为了让编译器区分是普通函数  模板函数
template<class T> //template<typename T>  //告诉编译器 我下面写模板函数，看到奇怪东西不要随便报错
void MySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

void test01() {

	int a = 10;
	int b = 20;
	//1 自动类型推导
	cout << "a:" << a << " b:" << b << endl;
	MySwap(a, b); //编译器根据你传的值 进行类型自动推导
	cout << "a:" << a << " b:" << b << endl;

	double da = 1.13;
	double db = 1.14;
	cout << "da:" << da << " db:" << db << endl;
	MySwap(da, db);
	cout << "da:" << da << " db:" << db << endl;

	//2. 显式的指定类型
	MySwap<int>(a, b);
}

int main(void) {

	test01();




	getchar();
	return 0;
}


-- 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

template<class T>
int MyAdd(T a, T b) {
	return a + b;
}

//普通函数可以进行自动类型转换
//函数模板必须严格类型匹配
int MyAdd(int a, int c) {
	return a + c;
}

void test01() {

	int a = 10;
	int b = 20;
	char c1 = 'a';
	char c2 = 'b';

	MyAdd<>(a, b);

#if 0 
	MyAdd(a, c1);
	MyAdd(a, b);
	MyAdd(c1, b);
#endif
}


template<class T>
void Print(T a) {

}

template<class T>
void Print(T a, T b) {

}

int main(void)
{
	test01();
	getchar();
	return 0;
}

-- 

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

void MySwap(int & a, int& b)
{
	int temp = a;
	a = b;
	b = temp;

}
void MySwap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;

}

template<class T>
void MySwap1(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;

}
int main()
{
	int a = 10;
	int b = 20;
	MySwap1(a, b);


	getchar();
	return 0;
}



-- 17

 

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template<class T>
class MyArray {
public:
	MyArray(int capacity)
	{
		this->mCapacity = capacity;
		this->mSize = 0;
		this->pAddr = new T[this->mCapacity];
	}
	MyArray(const MyArray<T>& arr)
	{

		this->mSize = arr.mSize;
		this->mCapacity = arr.mCapacity;
		this->pAddr = new T[this->mCapacity];//申请内存空间
		for (int i = 0; i < this->m; i++)
		{
			this->pAddr[i] = arr.pAddr[i];
		}
	}
	T& operator[](int index)
	{
		return this->pAddr[index];
	}
	MyArray<T> operator=(const MyArray<T>& arr)
	{
		if (this->pAddr!=NULL )
		{
			delete[] this->pAddr;
		}
		return *this;
	}

	void PushBack(T& data)
	{
		if (this->mSize>=this->mCapacity)
		{
			return;
		}

		this->pAddr[this->mSize] = data;
		this->mSize++;
	}


	int mCapacity;
	int mSize;
	T* pAddr;

};


int main()
{
	

	MyArray<int> x(20);
	x.PushBack(2);

	getchar();
	return 0;
}


--
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


template<class T>
class MyArray {
public:
	MyArray<T>(int capacity) {
		this->mCapacity = capacity;
		this->mSize = 0;
		//申请内存
		this->pAddr = new T[this->mCapacity];
	}
	MyArray<T>(const MyArray<T>& arr) {
		this->mSize = arr.mSize;
		this->mCapacity = arr.mCapacity;

		//申请内存空间
		this->pAddr = new T[this->mCapacity];
		//数据拷贝
		for (int i = 0; i < this->mSize; i++) {
			this->pAddr[i] = arr.pAddr[i];
		}

	}
	T& operator[](int index) {
		return this->pAddr[index];
	}

	MyArray<T>& operator=(const MyArray<T>& arr) {

		if (this->pAddr != NULL) {
			delete[] this->pAddr;
		}

		this->mSize = arr.mSize;
		this->mCapacity = arr.mCapacity;

		//申请内存空间
		this->pAddr = new T[this->mCapacity];
		//数据拷贝
		for (int i = 0; i < this->mSize; i++) {
			this->pAddr[i] = arr.pAddr[i];
		}

		return *this;
	}

	void PushBack(const T& data) {
		//判断容器中是否有位置
		if (this->mSize >= this->mCapacity) {
			return;
		}

		//调用拷贝构造 =号操作符
		//1. 对象元素必须能够被拷贝
		//2. 容器都是值寓意，而非引用寓意 向容器中放入元素，都是放入的元素的拷贝份
		//3  如果元素的成员有指针，注意深拷贝和浅拷贝问题
		this->pAddr[this->mSize] = data;
		//msize++
		this->mSize++;
	}


	~MyArray() {
		if (this->pAddr != NULL) {
			delete[] this->pAddr;
		}
	}
public:
	//一共可以容下多少个元素
	int mCapacity;
	//当前数组有多少元素
	int mSize;
	//保存数据的首地址
	T* pAddr;
};

void test01() {

	MyArray<int> marray(20);
	int a = 10, b = 20, c = 30, d = 40;
	marray.PushBack(a);
	marray.PushBack(b);
	marray.PushBack(c);
	marray.PushBack(d);

	//不能对右值取引用
	//左值 可以在多行使用
	//临时变量 只能当前行使用
	marray.PushBack(100);
	marray.PushBack(200);
	marray.PushBack(300);

	for (int i = 0; i < marray.mSize; i++) {
		cout << marray[i] << " ";
	}
	cout << endl;
}

class Person {};

void test02() {

	Person p1, p2;

	MyArray<Person> arr(10);
	arr.PushBack(p1);
	arr.PushBack(p2);

}


int main() {

	test01();

	getchar();
	return 0;
}










https://github.com/huaweicloud/huaweicloud-sdk-c-obs.git




 
	option.bucket_options.host_name = HOST_NAME;
    option.bucket_options.bucket_name = bucket_name;
    option.bucket_options.access_key = ACCESS_KEY_ID;
    option.bucket_options.secret_access_key = SECRET_ACCESS_KEY;
    option.bucket_options.uri_style = OBS_URI_STYLE_PATH;
	option.bucket_options.protocol = OBS_PROTOCOL_HTTPS; 













