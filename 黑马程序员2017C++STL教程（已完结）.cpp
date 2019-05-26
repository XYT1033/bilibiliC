
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


















 














