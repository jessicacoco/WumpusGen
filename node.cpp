#ifndef WUMPUSNODECPP
#define WUMPUSNODECPP
#include <iostream>
#include <string>
#include "node.h"

using namespace std;

Node::Node(int xcoord, int ycoord, string label_, int wall_size_) {
    // constructor function
    label = label_;
    // the max functions make sure the x and y coordinates are never negative
    x_coord = max(0, xcoord);
    y_coord = max(0, ycoord);
    // the minimum wall size is 4 so check that the given wall size is at least 4
    wall_size = max(4, wall_size_);
    // make sure x and y are feasible given the wall size, and if not, change it to the largest possible coorindate
    x_coord = min(x_coord, wall_size - 1);
    y_coord = min(y_coord, wall_size - 1);
}

int Node::get_x_coord() const {
    return x_coord;
}

int Node::get_y_coord() const {
    return y_coord;
}

const string& Node::get_label() const {
    return label;
}

int Node::get_wall_size() const {
    return wall_size;
}

void Node::set_label(string new_label) {
    label = new_label;
}

bool Node::is_start_spot() {
    // the start spot is the spot in the lower left corner labeled with "s"
    if (label == "s" && x_coord == wall_size - 1 && y_coord == 0) {
        return true;
    }
    // if the Node is in the lower left corner (the starting spot) but not labeled "s", change the label
    if (x_coord == wall_size - 1 && y_coord == 0) {
        set_label("s");
        return true;
    }
    // if the node fits neither of the above things then the node cannot be the starting spot
    if (label == "s") { // if this spot is incorrectly labeled, fix the label
        set_label("e");
    }
    return false;
}

bool Node::next_to_right_wall() {
    // if the node is next to the right wall, its y coordinate must be the farthest spot to the right
    return y_coord == wall_size - 1;
}

bool Node::next_to_left_wall() {
    // if node is next to left wall then its y coordinate would be 0
    return y_coord == 0;
}

bool Node::next_to_upper_wall() {
    // if node is next to the upper wall then its x coordinate would be 0
    return x_coord == 0;
}

bool Node::next_to_lower_wall() {
    // if node is next to the lower wall then its x coord must be the highest index
    return x_coord == wall_size - 1;
}

 bool Node::is_corner_spot() {
     //A node is in a corner if it is next to a vertical wall AND a horizontal wall
    if ((next_to_left_wall() && next_to_upper_wall()) ||
        (next_to_left_wall() && next_to_lower_wall()) ||
        (next_to_right_wall() && next_to_upper_wall()) ||
        (next_to_right_wall() && next_to_lower_wall())) {
            return true;
        }
    // if it does not fit in the above statement then the node is not in a corner
    return false;
 }

bool Node::is_empty() {
    // this function assumes that any empty spot is labeled "e"
    return label == "e";
}

bool Node::is_pit() {
    //This function assumes that any spot on the board with a pit is labeled "p"
    return label == "p";
}

bool Node::is_wumpus() {
    //This function assumes that any spot on the board with a wumpus is labeled "w"
    return label == "w";
}

bool Node::is_gold() {
    //This function assumes that any spot on the board with the gold is labeled "g"
    return label == "g";
}

bool Node::is_notpit_marked() {
    /* 
    This function assumes that any spot that is marked as not having a pit is labeled "np" or
    the np bool is set to true
    */
    if (this->np) {
        return true;
    }
    if (label == "np") {
        this->np = true;
        return true;
    }
    // if not labeled as not having a pit and np bool is false, then return false
    return false;
}

bool Node::is_notwumpus_marked() {
    /* 
    This function assumes that any spot that is marked as not having a wumpus is labeled "nw" or the
    nw bool is set to true 
    */
    if (this->nw) {
        return true;
    }
    if (label == "nw") {
        this->nw = true;
        return true;
    }
    // if not labeled as not having a wumpus and nw bool is false, then return false
    return false;
}

bool Node::is_notgold_marked() {
    /* This function assumes that any spot that is marked as not having gold is labeled "ng" or the
    ng bool is set to true
    */
    if (this->ng) {
        return true;
    }
    if (label == "ng") {
        this->nw = true;
        return true;
    }
    // if not labeled as not having gold and ng bool is false, then return false
    return false;
}

bool Node::marked_as_visited() {
    /* 
    This function assumes that any spot that is marked as visited is labeled with a "v" or the
    visited bool is set to true
    */
    if (this->visited) {
        return true;
    }
    if (label == "v") {
        this->visited = true;
        return true;
    }
    // if not labeled as visited and visited bool is false, then return false
    return false;
}


void Node::killw() {
    /*
     if the wumpus is shot and killed, that means the node's label must change from "w"/having a wumpus
     to "e" for it is now empty
     */
    if (this->label=="w"){this->label = "e";this->nw=true; this->np=true;}
    return;
}

#endif
