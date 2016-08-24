#ifndef _MY_SEGMENT_GROUP_H_
#define _MY_SEGMENT_GROUP_H_

#include "pathsegment.h"
#include "my_pathsegment.h"
#include "segmentgroup.h"

#include <vector>

using std::vector;
using Utilities::Point;
using Utilities::myPathSegment;

namespace Utilities {
    class mySegmentGroup: public SegmentGroup{
        public:
            mySegmentGroup();
            ~mySegmentGroup();

            /* Accessors */
            // unsigned size() const;
            // PathSegment* at(unsigned index) const;
            // bool empty() const;
            // bool contains(const Point& point);
            // int get_length();
            // void print();

            /* Mutators */
            // void add_segment(PathSegment* pathsegment);
            void add_segment(Point source, Point sink);
            // void remove_segment(PathSegment* pathsegment);
            // void remove_segment(Point soruce, Point sink);
            // void remove_segment(int index);
    };
}

#endif //_PATH_SEGMENT_GROUP_BASE_H_