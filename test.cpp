#include <iostream>
#include "Node.h"
#include "utilities/Boundary.h"

int main() {
	Point *a = new Point(0.0f, 0.0f);
	Point *b = new Point(100.0f, 100.0f);
	Point *xd = new Point(20.0f, 30.5f);
	// Point *d = new Point(3, 4);

	Boundary *b1 = new Boundary(a, b);

	Point *p = new Point(0.0f, 1.0f);
	PointNode *pn = new PointNode(p);
	PointList *pl = new PointList(pn);
	p->print();
	pn->print();
	pl->print();


	Node *n = new Node(b1);
	n->insert(*xd);

	n->showPoints();
}