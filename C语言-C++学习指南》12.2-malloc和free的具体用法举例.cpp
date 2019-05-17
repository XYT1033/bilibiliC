

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
using namespace std;

int main()
{
	Citizen c1 = { "xyt",100,NULL };
	buy(&c1);
	discard(&c1);

	system("pause");


	return 0;
}
struct Car
{
	char maker[32];//制造商
	int price;
};
struct Citizen
{
	char name[32];
	int deposit; //存款
	Car *car;

};
void buy(Citizen * owner)
{
	int Iu = sizeof(Car);
	Car* car = (Car*)malloc(sizeof(Car));
	strcpy(car->maker,"microsoft");
	car->price = 10;

	owner->car = car;
	owner->deposit -= car->price;

}

void discard(Citizen* owner)
{
	free(owner->car);
	owner->car = NULL;

}

























 