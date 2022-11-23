#include "GUI.h"
#include <iostream>

using namespace std;

int main (int argc, char **argv) {

	// Discrete World.
	DiscreteWorld2D world;
	//world.load("input.txt");
	//world.calculateWallProximity(5);
	//world.save("output.txt");
	world.load("output.txt");
	world.exportVMF("test.vmf");

	// Boid System.
	BoidSystem2f bs;
	bs.initialize(&world);

	GUI* gui = GUI::Instance();

	if (GUI::Instance()->initialize(argc, argv, &world, &bs)) {
		GUI::Instance()->execute();
	} else {
		std::cout << "\nPress Enter to exit.";
		std::cin.get();
	}
	return 0;
}