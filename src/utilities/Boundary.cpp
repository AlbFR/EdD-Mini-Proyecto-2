#include "Boundary.h"

#include <iostream>

Boundary::Boundary() {
	std::cerr << "Cannot initialize Boundary without given Points" << std::endl;
}

Boundary::Boundary(Boundary *b) {
	this->upperleft = b->upperleft;
	this->bottomright = b->bottomright;
}

Boundary::Boundary(Point *p, int d) {
	Point *a = new Point(p->x-d, p->y-d);
	Point *b = new Point(p->x+d, p->y+d);
	this->upperleft = a;
	this->bottomright = b;
}

Boundary::Boundary(Point ul, Point br) {
	if (ul.compare(br) != 1)
		std::cerr << "Cannot create Boundary, upperLeft Point must be lower than lowerRight Point" << std::endl;;
	
	Point *p = new Point(ul.x, ul.y);
	Point *q = new Point(br.x, br.y);

	this->upperleft = p;
	this->bottomright = q;
}

Boundary::Boundary(Point *ul, Point *br) {
	if (ul->compare(br) != 1)
		std::cerr << "Cannot create Boundary, upperLeft Point must be lower than lowerRight Point" << std::endl;;
	
	this->upperleft = ul;
	this->bottomright = br;
}

Point* Boundary::halfPoint() const {
	double x = (this->upperleft->x + this->bottomright->x) / 2;
	double y = (this->upperleft->y + this->bottomright->y) / 2;
	return new Point(x, y);
}

double Boundary::halfX() const {
	return (this->upperleft->x + this->bottomright->x) / 2;
}

double Boundary::halfY() const {
	return (this->upperleft->y + this->bottomright->y) / 2;
}

bool Boundary::isInBounds(Point p) const {
	// Inclusive in upper and left bounds
	// Exclusive in bottom and right bounds

	int val = this->upperleft->compare(p);
	if (!(val == 0 || val == 5 || val == 1 || val == 6))
		return false;

	val = this->bottomright->compare(p);
	if (val != 3)
		return false;

	return true;
}

bool Boundary::isInBounds(Point *p) const {
	return this->isInBounds(*p);
}

// Returns wether  or not b is completely inside this
bool Boundary::isInBounds(Boundary *b) const {
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

bool Boundary::isPartiallyInBounds(Boundary *b) const {
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

void Boundary::print() const {
	std::cout << "Upper Left bound: ";
	upperleft->print();
	std::cout << std::endl << "Lower Right bound: ";
	bottomright->print();
	std::cout << std::endl;
}

void Boundary::operator=(Boundary b) {
	this->upperleft = b.upperleft;
	this->bottomright = b.bottomright;
}