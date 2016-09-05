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
            //Point coord;
            //vector<Edge*> connections;
            //int cost;
        public:
            /* Constructors/Destructors */
            myNode(int x, int y, int cost=0);
            myNode(Point coord, int cost=0);
            ~myNode();

            /* Accessors */
            int get_cost();

            /* Mutators */
            void set_cost();
    };
}

#endif  //_MY_NODE_H_