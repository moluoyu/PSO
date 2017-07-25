#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	time_t t;
	cout << t << endl;
	srand((unsigned)time(&t));
	cout <<rand()<<endl;
}