#include "Boundary.h"

#include <iostream>

Boundary::Boundary() {
	throw "Cannot initialize Boundary without given Points";
}

Boundary::Boundary(Point *p, int d) {
	Point *a = new Point(p->x-d, p->y-d);
	Point *b = new Point(p->x+d, p->y+d);
	this->upperleft = a;
	this->bottomright = b;
}

Boundary::Boundary(Point *ul, Point *br) {
	if (ul->compare(br) != 1)
		throw "Cannot create Boundary, upperLeft Point must be lower than lowerRight Point";
	
	this->upperleft = ul;
	this->bottomright = br;
}

bool Boundary::isInBounds(Point p) { // limits inclusive
	if (p.x < upperleft->x || p.y < upperleft->y)
		return false;

	if (bottomright->x < p.x || bottomright->y < p.y)
		return false;

	return true;
}

bool Boundary::isInBounds(Point *p) {
	return this->isInBounds(*p);
}

bool Boundary::isInBounds(Boundary *b) {
	// Inclusive on upperleft
	// and exclusive on bottomright

	int comparison = this->upperleft->compare(b->upperleft);
	if (!(comparison == 0 || comparison == 5 || comparison == 1 || comparison == 6))
		return false;

	comparison = this->bottomright->compare(b->bottomright);
	if (!(comparison == 3))
		return false;

	return true;
}

bool Boundary::isPartiallyInBounds(Boundary *b) {
	Point *ul = b->upperleft;	
	Point *br = b->bottomright;
	
	if (this->isInBounds(ul) || this->isInBounds(br))
		return true;

	Point *ur = new Point(br->x, ul->y);
	Point *bl = new Point(ul->x, br->y);

	if (this->isInBounds(ur) || this->isInBounds(bl))
		return true;
	
	return false;

}

void Boundary::print() {
	std::cout << "Upper Left bound: ";
	upperleft->print();
	std::cout << std::endl << "Lower Right bound: ";
	bottomright->print();
	std::cout << std::endl;
}