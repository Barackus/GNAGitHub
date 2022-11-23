#include <iostream>

#include "boids.h"

using namespace std;

/**
 * 
 **/
int main(void) {

	BoidSystem2f bs;
	bs.initialize();

	for(int i = 0; i < 50; ++i)
		cout << "-";
	cout << "\r";
	for(int i = 0; i < 1000; ++i) {
		if(i % 20 == 0)
			cout << "+";
		bs.update();
	}
	cout << endl;

	system("pause");

}