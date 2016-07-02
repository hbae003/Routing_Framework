#include "../Headers/my_grid.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"

//instead of initializing grid variable, this initializes map variable
myGrid::myGrid(ProblemObject* problem_object):Grid(problem_object){
 	vector<Blocker> blockers = problem_object->get_blockers();
 	//saves connections 
 	vector<Connection> con = problem_object->get_connections();
 	for (int i = 0; i < con.size(); i++){
 		myConnection temp_c;
 		temp_c.name = con.at(i).name;
 		temp_c.source = con.at(i).source;
 		temp_c.sink = con.at(i).sink;
 		temp_c.found = false;
 		temp_c.border.push_back(get_node(con.at(i).source));
 		this->connections.push_back(temp_c);
 	}
	int height = problem_object->get_height();
	int width = problem_object->get_width();
	for(int y = 0; y < height; y++) {
	    vector<Node*> temp_row;
	    for(int x = 0; x < width; x++) {
			Node* new_node;
	      	//Check to see if what we want to add falls within a blocker, and if it does than don't add it
	      	bool add_flag = true;
	      	for(unsigned i = 0; i < blockers.size(); i++) {
			if(x > blockers.at(i).location.x && x <= blockers.at(i).location.x + blockers.at(i).width &&
				y > blockers.at(i).location.y && y <= blockers.at(i).location.y + blockers.at(i).height) {
				add_flag = false;
				}
			}

			//If the add flag is true, the node doesn't lie within a blocker and we can add it to the system
			if(add_flag) {
				/* 
				Note that we add connections west and north because we start building in the upper left
				corner of the system, so as the system fills it links to all the nodes it can connect to
				that have already been created. This stops the system from accidentally creating multiple
				connections between two nodes, which could cause issues when routing
				*/
				new_node = new myNode(x,y);
				if (x > 0) {
				  	if(temp_row.at(temp_row.size()-1) != NULL) {
						Edge* west = new Edge(new_node,temp_row.at(temp_row.size()-1));
						new_node->add_connection(west);
					}
				}
				if (y > 0) {
				    if(map.at(y-1).at(x) != NULL) {
				  		Edge* north = new Edge(new_node,map.at(y-1).at(x));
						new_node->add_connection(north);
					}
				}
			}
			//If the add flag is false, the node shouldn't exist, so we fill its space with a NULL for completeness
			else {
				new_node = NULL;
			}
			temp_row.push_back(new_node);
	    }
	    this->map.push_back(temp_row);
	}
}


myGrid::~myGrid(){
	int width = this->get_width();
    int height = this->get_height();
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < width; y++) {
	    	if(map.at(y).at(x) != NULL) {
                delete map.at(y).at(x);
		  	}
        }
    }
}

int myGrid::get_width() {
	//Assumes a perfect rectangle
	return map.empty()?0:map.at(0).size();
}

int myGrid::get_height() {
	//Assumes a perfect rectangle
	return this->map.size();
}


Node* myGrid::get_node(int x, int y) {
      if(y >= this->map.size()) {
        claim("Attemping to access a node outside of the grid's range (y-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(x >= this->map.at(y).size()) {
        claim("Attemping to access a node outside of the grid's range (x-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(this->map.at(y).at(x) != NULL) {
      	    return this->map.at(y).at(x);      //at(...) will throw an out of range exception
      }
      else {
	    return NULL;
      }
}

void myGrid::replace_node(Node* replacement_node) {
      delete this->map.at(replacement_node->get_y()).at(replacement_node->get_x());
      this->map.at(replacement_node->get_y()).at(replacement_node->get_x()) = replacement_node;
}

Node* myGrid::get_node(Point coord) {
      return this->get_node(coord.x, coord.y);
}

vector<Path*> no_blockers(){
	//breadth first search for multiple connections 
	int step = 1; 
	bool all_found = false; 
	while(!all_found)
	{
		all_found = true;
		for(int i = 0; i < get_num_connections(); i++){
			if(!this->connections.at(i).found){
				//first set the cost of all nodes adjacent to border nodes 
				//at the same time, push the nodes into a temp border vector 
				vector<Node*> temp_b;
				for(int j = 0; j < this->connections.at(i).border.size(); j++){
					
				}
			}
		}
	}
}












