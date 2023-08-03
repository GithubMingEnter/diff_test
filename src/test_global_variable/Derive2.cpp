#include <iostream>
#include "global_incl.h"
using namespace std;

void print_global_variable2() {
	g_var += 2;
	cout << "print function2: " << g_var << endl;
}
