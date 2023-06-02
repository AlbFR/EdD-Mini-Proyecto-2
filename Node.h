#include "utilities.h"
#include <vector>
#define Node_H
#ifndef Node_H

class Node {
public:
    Node();
    ~Node();
    int totalPoints();
    int totalNodes();
    void insert(Point p, int population);
    vector<Node> list();
    int countRegion();
private:
    string city;
    int population;
    string country;
    Boundary boundary; //Pair of points that delimit the area represented by the node
    bool color; //Type of node, true (or black) if there is points (information) inside the node, false (or white) otherwise
    Node* children; //Array of, at most, 4 child nodes who represent the upperleft, upperright, lowerleft and lowerright subareas respectively.
};

#endif