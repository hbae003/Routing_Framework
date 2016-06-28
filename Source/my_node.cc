#include "../Headers/edge.h"
#include "../Headers/my_node.h"
#include "../Headers/claim.h"

#include <iostream>

Utilities::myNode::myNode(int x, int y, int cost):Node(x, y, cost){
      this->myCost.push_back(cost);
}

Utilities::myNode::myNode(Point coord, int cost):Node(coord, cost){
      this->myCost.push_back(cost);
}

Utilities::myNode::~myNode(){
}

int Utilities::myNode::get_cost(int connection_num) {
      return this->myCost.at(connection_num);
}

void Utilities::myNode::set_cost(int connection_num, int cost){
      this->myCost.at(connection_num) = cost;
}