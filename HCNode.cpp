// Sergio Leon <seleon>, Michael Lee <mil039>

#include "HCNode.hpp"

//Check if count size is less than or equal to other's count
bool HCNode::operator<(const HCNode& other) {
    return other.count <= this->count;
}
