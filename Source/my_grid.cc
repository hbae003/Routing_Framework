#include "../Headers/my_grid.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"

//instead of initializing grid variable, this initializes map variable
myGrid::myGrid(ProblemObject* problem_object): Grid(problem_object){
 	vector<Blocker> blockers = problem_object->get_blockers();
 	//saves connections 
 	vector<Connection> con = problem_object->get_connections();
 	for(int i = 0; i < con.size(); i++){
 		myConnection temp_c;
 		temp_c.name = con.at(i).name;
 		temp_c.source = con.at(i).source;
 		temp_c.sink = con.at(i).sink;
 		temp_c.found = false;
 		temp_c.border.push_back(Grid::get_node(con.at(i).source));
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
				new_node = new Node(x,y);
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
        claim("Attemping to access a node outside of the map's range (y-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(x >= this->map.at(y).size()) {
        claim("Attemping to access a node outside of the map's range (x-value out of range)", Utilities::kError);
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


vector<Path*> myGrid::no_blockers(){
	int node_x; 
	int node_y;

	//BFS one connection 
	for(int i = 0; i < this->get_num_connections(); i++){
		int step = 0; 
		while(!this->connections.at(i).found){
			vector<Node*> temp_b; 
			step++;
			for(int j = 0; j < this->connections.at(i).border.size(); j++){
				//set node_x and node_y to source position 
				node_x = this->connections.at(i).border.at(j)->get_x();
				node_y = this->connections.at(i).border.at(j)->get_y();

				//check up down left right 
				//if any are empty nodes, make cost=step and add node to temp_b
				//checks if top node exists and cost=0
				if(node_y != 0 && this->get_node(node_x, node_y - 1) != NULL 
					&& this->get_node(node_x, node_y - 1)->get_cost() == 0){
					this->get_node(node_x, node_y - 1)->set_cost(step);
					temp_b.push_back(this->get_node(node_x, node_y - 1));
				}
				//checks if bottom node exists and cost=0
				if(node_y != map.size() - 1 && this->get_node(node_x, node_y + 1) != NULL 
					&& this->get_node(node_x, node_y + 1)->get_cost() == 0){
					this->get_node(node_x, node_y + 1)->set_cost(step);
					temp_b.push_back(this->get_node(node_x, node_y + 1));
				}
				//checks if left node exists and cost=0
				if(node_x != 0 && this->get_node(node_x - 1, node_y) != NULL 
					&& this->get_node(node_x - 1, node_y)->get_cost() == 0){
					this->get_node(node_x - 1, node_y)->set_cost(step);
					temp_b.push_back(this->get_node(node_x - 1, node_y));
				}
				//checks if right node exists and cost=0
				if(node_x != map.at(0).size() - 1 && this->get_node(node_x + 1, node_y) != NULL 
					&& this->get_node(node_x + 1, node_y)->get_cost() == 0){
					this->get_node(node_x + 1, node_y)->set_cost(step);
					temp_b.push_back(this->get_node(node_x + 1, node_y));
				}

			}//end of second for loop
			//check if any nodes in temp_b are sinks 
			//if any of them are, then found is set to true
			for(int z = 0; z < temp_b.size(); z++){
				if(temp_b.at(z)->get_x() == this->connections.at(i).sink.x 
					&& temp_b.at(z)->get_y() == this->connections.at(i).sink.y){
					this->connections.at(i).found = true;
					z = temp_b.size();
					temp_b.clear();
				}
			}
			//set the new borders 
			this->connections.at(i).border = temp_b;
			temp_b.clear();

		}//end of BFS while loop
		//at the end of BFS, step variable holds lee's number of sink
		//start retrace
		/* The algorithm for retrace first starts by using the step variable to determine 
		*  the direction to go. Every time the retrace changes direcion, a path segment 
		*  is added to a temporary path segment. Because the retrace moves backwards towards the 
		*  source, the sources and sinks of path segments are flipped. When a path is found, 
		*  the path segments are pushed into a correct path variable. The path is then pushed 
		*  into the private my_grid vector paths. 
		*/

		enum direction {NONE, UP, DOWN, LEFT, RIGHT, RESET} dir;
		dir = NONE; 
		
		//set node_x and node_y 
		node_x = this->connections.at(i).sink.x;
		node_y = this->connections.at(i).sink.y;
	
		//path segment vector 
		vector <Point*> segment;
		segment.push_back(&this->connections.at(i).sink);
		Path *correct_path = new Path(); 
		vector <PathSegment*> temp_path; 

		//set path's source and sink 
		Point *path_sink = new Point(node_x, node_y); 
		Point *path_source = new Point(this->connections.at(i).source.x, this->connections.at(i).source.y);

		correct_path->set_source(*path_source);
		correct_path->set_sink(*path_sink);
		step--;

		while(step){
			Point *temp_point; 
			switch(dir){
				case NONE:
					//choose starting direction 
					//checks if top node exists and cost == step
					if(node_y != 0 && this->get_node(node_x, node_y - 1) != NULL 
						&& this->get_node(node_x, node_y - 1)->get_cost() == step){
						node_y--; 
						temp_point = new Point(node_x, node_y); 
						segment.push_back(temp_point);
						dir = UP; 
					}
					//checks if bottom node exists and cost == step
					else if(node_y != map.size() - 1 && this->get_node(node_x, node_y + 1) != NULL 
						&& this->get_node(node_x, node_y + 1)->get_cost() == step){
						node_y++; 
						temp_point = new Point(node_x, node_y); 
						segment.push_back(temp_point);
						dir = DOWN; 
					}
					//checks if left node exists and cost == step
					else if(node_x != 0 && this->get_node(node_x - 1, node_y) != NULL 
						&& this->get_node(node_x - 1, node_y)->get_cost() == step){
						node_x--; 
						temp_point = new Point(node_x, node_y); 
						segment.push_back(temp_point);
						dir = LEFT; 
					}
					//checks if right node exists and cost == step
					else if(node_x != map.at(0).size() - 1 && this->get_node(node_x + 1, node_y) != NULL 
						&& this->get_node(node_x + 1, node_y)->get_cost() == step){
						node_x++; 
						temp_point = new Point(node_x, node_y);
						segment.push_back(temp_point);
						dir = RIGHT; 
					}
					step--;
					break;

				case UP:
					//if the next node is also above, add to segment
					//else set dir to RESET
					if(node_y != 0 && this->get_node(node_x, node_y - 1) != NULL 
						&& this->get_node(node_x, node_y - 1)->get_cost() == step){
						node_y--;
						temp_point = new Point(node_x, node_y);
						segment.push_back(temp_point);
						step--;
					}
					else{ dir = RESET; }
					break;

				case DOWN:
					//if the next node is also below, add to segment
					//else set dir to RESET
					if(node_y != map.size() - 1 && this->get_node(node_x, node_y + 1) != NULL 
						&& this->get_node(node_x, node_y + 1)->get_cost() == step){
						node_y++;
						temp_point = new Point(node_x, node_y);
						segment.push_back(temp_point);
						step--;
					}
					else{ dir = RESET; }
					break;

				case LEFT:
					//if the next node is also left, add to segment
					//else set dir to RESET
					if(node_x != 0 && this->get_node(node_x - 1, node_y) != NULL 
						&& this->get_node(node_x - 1, node_y)->get_cost() == step){
						node_x--; 
						temp_point = new Point(node_x, node_y);
						segment.push_back(temp_point);
						step--;
					}
					else{ dir = RESET; }
					break;

				case RIGHT:
					//if the next node is also right, add to segment
					//else set dir to RESET
					if(node_x != map.at(0).size() - 1 && this->get_node(node_x + 1, node_y) != NULL 
						&& this->get_node(node_x + 1, node_y)->get_cost() == step){
						node_x++; 
						temp_point = new Point(node_x, node_y);
						segment.push_back(temp_point);
						step--;
					}
					else{ dir = RESET; }
					break;

				case RESET:
					//push new pathsegment into temp_path and clear segment
					//set the first point (sink) in segment as source of previous 
					PathSegment *temp_seg = new PathSegment(*segment.at(segment.size() - 1), *segment.at(0));
					temp_path.push_back(temp_seg);
					temp_point = segment.at(segment.size() - 1);
					segment.clear();
					segment.push_back(temp_point);
					dir = NONE;
					break;

			}//end of switch

			if(step == 0 && segment.size() > 1){//retrace reaches source 
				//push source of path onto segment because this method skips the last read 
				segment.push_back(path_source);
				//reverse source and sink 
				PathSegment *temp_seg = new PathSegment(*segment.at(segment.size() - 1), *segment.at(0)); 
				temp_path.push_back(temp_seg);
				segment.clear();
			}
		}//end of retrace
		//reverse temp_path by pushing into correct_path and push path into vector

		//flip temp path and add segments into correct path
		for(int j = temp_path.size() - 1; j >= 0; j--){
			correct_path->add_segment(temp_path.at(j));
		}

		this->add_path(correct_path);
		this->clear_map();
	}//end of first for loop
	return this->get_paths();
}//end of no_blockers 

void myGrid::clear_map() {
	std::cout << "Testing" << endl;

	//go through the map and change all costs back to 0
	for(int i = 0; i < this->map.size(); i++){
		for(int j = 0; j < this->map.at(i).size(); j++){
			if(this->get_node(i,j) != NULL){
				this->get_node(i,j)->set_cost(0);
			}
		}
	}
}


void myGrid::print_map(int num){
	std::cout << endl;
	myConnection temp = connections.at(num);
	for(int i = 0; i < this->map.size(); i++){
		for(int j = 0; j < this->map.at(i).size(); j++){
			if(this->get_node(i,j) != NULL){
				if(i == temp.source.x && j == temp.source.y){
					std::cout << " S ";
				}
				else if(i == temp.sink.x && j == temp.sink.y){
					std::cout << " F ";
				}
				else{
					std::cout << " 0 ";
				}
			}
			else{
				std::cout << " X ";
			}
		}
		std::cout << endl;
	}
}

void myGrid::path_to_blockers(){
	
}
















