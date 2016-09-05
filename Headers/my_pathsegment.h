#ifndef _MY_PATH_SEGMENT_H_
#define _MY_PATH_SEGMENT_H_

#include "point.h"
#include "pathsegment.h"

namespace Utilities {
    class myPathSegment: public PathSegment{
        public:
            /* Constructors/Destructors */
            myPathSegment(Point source, Point sink);
            myPathSegment(int p1_x, int p1_y, int p2_x, int p2_y);
            ~myPathSegment();

            /* Overloaded Operators */
            // bool operator==(const PathSegment& rhs);

            /* Accessors */
            // Point get_source();
            // Point get_sink();
            // int get_length();
            // bool contains_points(Point source, Point sink);
            // void print_source();
            // void print_sink();
            void print();

            /* Mutators */
            // void set_source(Point source);          
            // void set_sink(Point sink);
    };
}

#endif //_MY_PATH_SEGMENT_H_
