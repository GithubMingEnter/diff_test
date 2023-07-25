#include <iostream>
#include "global_incl.h"
using namespace std;

void print_global_variable1() {
	g_var += 1;
	cout << "print function1: " << g_var << endl;
}
