#include <iostream>
#include "global_incl.h"
using namespace std;

int g_var = 233;

int main(int argc, char *argv[])
{
	cout << "original print: " << g_var << endl;
	print_global_variable1();
	g_var += 1;
	cout << "after function1: " << g_var << endl;

	print_global_variable2();
	g_var += 1;
	cout << "after function2 " << g_var << endl;

	// print_global_variable3();
	g_var += 1;
	cout << "after funtion3: " << g_var << endl;
	return 0;
}
