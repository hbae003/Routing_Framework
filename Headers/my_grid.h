#ifndef _MY_GRID_H_
#define _MY_GRID_H_

#include "my_node.h"
#include "path.h"
#include "my_grid.h"
#include "problem_object.h"
#include <vector>

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Edge;
using Utilities::Path;
using Utilities::ProblemObject;

class myGrid: public Grid{
	private:
	public:
		/* Constructors/Destructors */
		myGrid(ProblemObject* problem_object);
	    ~myGrid();
};

#endif
//_MY_GRID_H