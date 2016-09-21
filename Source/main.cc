
#include "../Headers/problem_object.h"
#include "../Headers/my_grid.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
//using Utilities::myNode;

int main(int argc,char* argv[]) {

	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { 
		cout << "Usage: ./grid_router <test_file>" << endl; 
		exit(1);
	}
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN

	//Create your problem map object (in our example, we use a simple grid, you should create your own)
	//Grid g(first_problem);
	myGrid g(first_problem);

	/*
	Note: we do not take into account the connections or blockers that exist in the Project Object
	You should be accouting for these in your problem map objects (you should not be using Grid). You
	should be using both the Node and Edge classes as the background for whatever problem map object
	you create.
	*/


	/*
	Run your algorithm after creating your problem map object. You should be returning from your algorithm 
	either a Path or a Netlist

	Path: a series of straight line segments, with a single source and a single sink
	Netlist: a series of stright line segments, with a single source and more than one sink
	*/
	//go through the connections in the problem and ask the user to choose which paths can intersect 
	for(unsigned i = 0; i < g.connection_size(); i++){
		char input;
		cout << "Do you want path " << i << " to intersect other paths?(y/n): ";
		cin >> input;
		if(input == 'n'){
			g.disable_intersect(i);
		}
	}

	//vector<Path*> paths = g.test_algorithm();
	if(!(g.get_width() == 1 && g.get_height() == 2) && !(g.get_width() == 2 && g.get_height() == 1)){
		g.print_map(0);
	}

	cout << "passed print" << std::endl;
	vector<Path*> paths = g.no_blockers();
	//Print the paths/netlists that you return from your algorithm
	for(unsigned i = 0; i < paths.size(); i++) {
		cout << "Path " << i << ": ";
		paths.at(i)->print();
		Path* temp = paths.at(i);
		delete temp;
	}

	paths.clear();

	delete first_problem;

	return 0;
}
