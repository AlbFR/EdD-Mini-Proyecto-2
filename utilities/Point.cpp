#include "Point.h"

#include <iostream>
#include <cmath>

Point::Point() {
	throw "Cannot create a Point Object without x and y arguments";
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

void Point::print() {
	std::cout << "(" << this->x << ", " << this->y << ")";
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

int Point::compare(Point q) {
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

int Point::compare(Point *q) {
	return this->compare(*q);
}