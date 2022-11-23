#include <iostream>

#define TRAINING_MODE	false
#define GUI_BRAIN		true	// Change to true to use a computed brain in gui simulation
#define INPUT			"input.txt"
#define OUTPUT			"output.txt"
#define VMF				"map.vmf"
#define LAYERS			84, 42, 21, 42, 16

#include "../../GUI/GUI.cpp"
#include "../../World/src/world.h"
#include "../../Boids/src/boids.h"
#include "../../Neural Network/src/neuralnetwork.h"
#include "../../Genetic Algorithm/Evolution.cpp"

#include "overmindfitnessfunctor.h"

using namespace std;

/**
 * 
 **/
int main(int argc, char **argv) {

	// Discrete World.
	DiscreteWorld2D world;
	world.load(INPUT);
	world.calculateWallProximity(PROXIMITY_RESOLUTION);
	world.save(OUTPUT);
	world.load(OUTPUT);
	world.exportVMF(VMF, NUM_BOIDS);
	//world.exportVMF(VMF);

	// Boid System.
	BoidSystem2f bs;
	bs.initialize(&world);

	// Multilayer Perceptron.
	MLPerceptron5d mlp(LAYERS);

	if(TRAINING_MODE) {
		// Training mode.
		OvermindFitnessFunctor off(&world, &bs, &mlp);
		Evolution evolution(&off, mlp.countConnections());
		evolution.train();
	} else {
		// Graphical User Interface mode.
		GUI* gui = GUI::Instance();
		if (GUI_BRAIN) {
			OvermindFitnessFunctor off(&world, &bs, &mlp);
			Evolution evolution(&off, mlp.countConnections());

			// Load most recent brain genes
			int generationNumber = evolution.readFromFile();
			cout << "Using brain from generation: " << generationNumber << endl;
			
			//Select the best genes from the generation
			vector<individual>* population = evolution.getPopulation();
			for (int i=0; i<5; ++i)
				std::cout << population->at(0).genes.at(i) << ", ";
			std::cout << "+++++" << std::endl;
			/*vector<individual>::iterator git;
			for(git = population->begin(); git != population->end(); ++git) {
				(*git).genes;*/

			// Assign the genes to the brain
			mlp.setWeights(population->at(0).genes);

			// Initialize GUI with brain input from training			
			if(gui->initialize(argc, argv, &world, &bs)) {

				gui->setMLP(&mlp);
				gui->setBrainEnabled(true);
				gui->execute();
			}
		}
		else {
			// Initialize GUI in 'dumb mode'
			if(gui->initialize(argc, argv, &world, &bs))
				gui->execute();
		}
	}

	system("pause");
	return 0;
}