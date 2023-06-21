#include <iostream>
#include "utilities/Boundary.h"

int main() {
	Point *a = new Point(0, 1);
	Point *b = new Point(1, 2);
	Point *c = new Point(2, 3);
	Point *d = new Point(3, 4);
	std::cout << b->compare(a) << std::endl;
	Boundary *b1 = new Boundary(a, d);
	Boundary *b2 = new Boundary(b, c);
	std::cout << b1->isInBounds(b2) << std::endl;
}