#include <iostream>
#include <fstream>
#include <string>
#include "QuadTree.h"
#include "utilities/readLine.h"

int main() {
	
	std::ifstream file;
    file.open("../dataSet/worldcitiespop_fixed.csv");
	
	if (file.fail()) {
		std::cerr << "Error: The file could not be opened" << std::endl;
		exit(1);
	}

	// latitude, longitude
	// latitude [-90, 90]
	// longitude [-180, 180]

	Point *p = new Point(-90.0f, -180.0f);
	Point *q = new Point(90.0f, 180.0f);


	QuadTree *qt = new QuadTree(new Boundary(p, q));

	int numCities = 10;

	std::string ignore;
	getline(file, ignore);
	for (int i = 0;i < numCities;++i) {
		PointData pd = readLine(file);
		Point *p = new Point(pd);
		p->print();
		qt->insert(*(new Point(pd)));
	}

	std::cout << qt->totalPoints() << std::endl;

	std::vector<PointList*> v;
	qt->list(v);

	for (unsigned i=0;i<v.size();++i) {
		std::cout << (v[i]==nullptr) << std::endl;
		v[i]->print();
	}

	file.close();


	// Point *a = new Point(0.0f, 0.0f);
	// Point *b = new Point(100.0f, 100.0f);
	// Point *xd = new Point(20.0f, 30.5f);
	// // Point *d = new Point(3, 4);

	// Boundary *b1 = new Boundary(a, b);

	// Point *p = new Point(0.0f, 1.0f);
	// PointNode *pn = new PointNode(p);
	// PointList *pl = new PointList(pn);
	// p->print();
	// pn->print();
	// pl->print();


	// Node *n = new Node(b1);
	// n->insert(*xd);

	// n->showPoints();
}