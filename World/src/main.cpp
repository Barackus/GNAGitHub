#include <iostream>

#include "world.h"

using namespace std;

int main(void) {

	cout << "----------------" << endl;
	cout << " Discrete World " << endl;
	cout << "----------------" << endl << endl;

	DiscreteWorld<3> world(256, 256, 256);
	world.load("input.txt");
	world.save("test0.txt");
	world.load("test0.txt");
	world.save("test1.txt");
	world.load("test1.txt");
	world.save("test2.txt");
	world.load("test2.txt");
	world.save("output.txt");

	cout << world(2, 2, 1) << " == " << world.get(2, 2, 1) << endl;

	system("pause");
	return 0;
}