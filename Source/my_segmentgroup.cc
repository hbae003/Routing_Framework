#include "../Headers/my_segmentgroup.h"

Utilities::mySegmentGroup::mySegmentGroup(): SegmentGroup(){
    /* Empty Constructor */
}

Utilities::mySegmentGroup::~mySegmentGroup() {
    while(!this->segments.empty()) {
        PathSegment* temp = this->segments.back();
        segments.pop_back();
        delete(temp);
    }
}

void Utilities::mySegmentGroup::add_segment(Point source, Point sink) {
    this->segments.push_back(new PathSegment(source, sink));
}