#include "../Headers/my_pathsegment.h"

Utilities::myPathSegment::myPathSegment(Point source, Point sink):
        PathSegment(source, sink) {
    
}

Utilities::myPathSegment::myPathSegment(int p1_x, int p1_y, int p2_x, int p2_y):
        PathSegment(p1_x, p1_y, p2_x, p2_y) {
    
}

Utilities::myPathSegment::~myPathSegment() {
    /* Empty Destructor */
}

void Utilities::myPathSegment::print() {
    //X = false
    //Y = True
    Point trace = this->get_source(); 
    Point dir_check = this->get_sink();
    bool direction;
    trace.x == dir_check.x ? direction = true : direction = false; 
    int size = this->get_length();
    for(int i = 0; i < size; i++){
    	if(direction){
    		cout << trace.x << " -> " << trace.y + i;
    	}
    	else{
    		cout << trace.x + i << " -> " << trace.y;
    	}
    }
}
