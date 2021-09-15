#include "include/libbloom.h"

using namespace std;

int main() {
	Bloom *bl = new Bloom(10000, 0.01);
	bl->add("helloworld", strlen("helloworld"));

	if (!(bl->check("helloworld", strlen("helloworld")))) {
		cout << "have" << endl;
	}
	else {
		cout << "haven't" << endl;
	}
	bl->clear();
}