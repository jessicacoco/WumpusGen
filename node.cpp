#include <iostream>
#include <vector>
#include "node.h"
using namespace std;

Node::Node(int xcoord, int ycoord, string & label_, int wall_size_) {
    // constructor function
    x_coord = xcoord;
    y_coord = ycoord;
    label = label_;
    wall_size = wall_size_;
}

Node::~Node() { // destuctor will call the function that deletes everything
    deletenode();
}

Node::Node(const Node& n) { //calls copy constructor function
    copy(n);
}

Node* Node::copy(const Node &n) {// function that copies node object
    // copy over variables
    Node * newnode = new Node();
    newnode->x_coord = n.x_coord;
    newnode->y_coord = n.y_coord
    newnode->label = n.label;
    newnode.wall_size = n.wall_size;
    return newnode; 
}

void Node::deletenode() {
    // destructor function goes here
}

Node& Node::operator=(const Node & n) { // assigment operator function
    // check if the two node objects are equal
    if (this != &n) { 
        // if two node objects are not equal, call destructor and copy
        deletenode();
        this->copy(n);
    }
    // return pointer to object
    return *this;
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

bool Node::is_start_spot() {
    /* 
    A node is at the starting location if it is at the bottom left corner of the generated board. This
    means that the x coordinate should be in the last row of the generated board (its  wall size) and the y
    coordinate should be in the first spot in the last row (that spot is index 0).
    */

    return x_coord == wall_size - 1 && y_coord == 0;
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
        (next_to_left_wall && next_to_lower_wall()) ||
        (next_to_right_wall() && next_to_upper_wall()) ||
        (next_to_right_wall() && next_to_lower_wall())) {
            return true;
        }
    // if it does not fit in the above statement then the node is not in a corner
    return false;
 }


bool Node::is_pit() {
    /* 
    This function assumes that any spot on the board with a pit is labeled "pit". This
    may need to be changed if the pits are labeled differently.
    */

    return label == "pit";
}

bool Node::is_wumpus() {
    /* 
    This function assumes that any spot on the board with a wumpus is labeled "wumpus". This
    may need to be changed if the wumpus spot is labeled differently.
    */

    return label == "wumpus";
}

bool Node::is_gold() {
    /* 
    This function assumes that any spot on the board with the gold is labeled "gold". This
    may need to be changed if the gold spot is labeled differently.
    */

    return label == "gold";
}

bool Node::is_notpit_marked() {
    /* 
    This function assumes that any spot that is marked as not having a pit is labeled "np". This
    may need to be changed if the spot is labeled differently. 
    */

    return label == "np";
}

bool Node::is_notwumpus_marked() {
    /* 
    This function assumes that any spot that is marked as not having a wumpus is labeled "nw". This
    may need to be changed if the spot is labeled differently. 
    */

    return label == "nw";
}