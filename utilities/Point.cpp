#include "Point.h"

// #include <iostream>
#include <cmath>

Point::Point() {
	std::cerr << "Cannot create a Point Object without x and y arguments" << std::endl;
	exit(1);
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
	this->pd = nullptr;
}

Point::Point(double x, double y, PointData *pd) {
	this->x = x;
	this->y = y;
	this->pd = pd;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

int Point::compare(Point q) const {

	/*		
	This graphic explains the possible return values,
	where right is the positive x-axis and bottom 
	is the positive y-axis.
	If the points have the same coord 0 is returned
			    8
			    ^
			    |
		     3  |  4
		7 <-----0-----> 5
		     2  |  1
			    |
				v
				6
	*/

	double e = 1e-6; // epsilon for float comparison error
	double x = q.x - this->x;
	double y = q.y - this->y;

	if (x < 0) {
		if (y < 0)
			return 3;
		if (fabs(y) < e)
			return 7;
		return 2; // 0 < y
	}
	else if (fabs(x) < e) {
		if (y < 0)
			return 8;
		if (fabs(y) < e)
			return 0;
		return 6; // 0 < y
	}
	else { // 0 < x
		if (y < 0)
			return 4;
		else if (fabs(y) < e)
			return 5;
		return 1; // 0 < y
	}
}

int Point::compare(Point *q) const {
	return this->compare(*q);
}

void Point::operator=(Point q) {
	this->x = q.x;
	this->y = q.y;
}

// bool Point::operator==(Point q) const {
// 	if (this->x != q.x)
// 		return false;
// 	if (this->y != q.y)
// 		return false;
// 	return true;
// }

void Point::print() const {
	std::cout << "(" << this->x;
	std::cout << ", " << this->y;
	std::cout << ")";
}