#ifndef _MY_GRID_H_
#define _MY_GRID_H_

#include "node.h"
#include "path.h"
#include "grid.h"
#include "problem_object.h"
#include <vector>

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Edge;
using Utilities::Path;
using Utilities::ProblemObject;

struct myConnection{
	vector<Node*> border; 
	string name;
	bool found; //found is used to find source and sink in algorithms 
	Point source;
	Point sink;
};

class myGrid: public Grid{
	private:
		vector<vector<Node*> > map;
		vector<myConnection> connections;
		//vector<vector<Node*> > grid;
	 	//int num_connections;
	 	//vector<Path*> paths;
	public:
		//functions that are commented out are the same 
		/* Constructors/Destructors */
		myGrid(ProblemObject* problem_object);
	    ~myGrid();

	    /* Accessors */
	    int get_width();
	    int get_height();
	    //int get_num_connections();
	    Node* get_node(int x, int y);
	    Node* get_node(Point coord);
	    //vector<Path*> get_paths();
	    //Path* get_path(int i);

	    /* Mutators */
	    void replace_node(Node* replacement_node);
	    //void set_paths(vector<Path*> paths);
	    //void add_path(Path* path);s
	    //void replace_path(int i, Path* path);
	    //void remove_path(int i);

	    /* Algorithms */
	    vector<Path*> no_blockers();
};

#endif
//_MY_GRID_H