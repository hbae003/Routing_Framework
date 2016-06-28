#ifndef _MY_NODE_H_
#define _MY_NODE_H_

#include "../Headers/point.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;

namespace Utilities {
    class Edge;

    class myNode: public Node {
        private:
            vector<int> myCost;
        public:
            /* Constructors/Destructors */
            myNode(int x, int y, int cost=0);
            myNode(Point coord, int cost=0);
            ~myNode();

            /* Accessors */
            int get_cost(int connection_num);

            /* Mutators */
            void set_cost(int connection_num, int cost);
    };
}

#endif  //_MY_NODE_H_