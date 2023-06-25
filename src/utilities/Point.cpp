#include "Point.h"

#include <cmath>

Point::Point() {
	std::cerr << "Cannot create a Point Object without x and y arguments" << std::endl;
	exit(1);
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
	this->pointdata = nullptr;
}

Point::Point(PointData *pointData) {
	this->x = pointData->latitude;
	this->y = pointData->longitude;
	this->pointdata = pointData;
}


void Point::print() const {
	if (this->pointdata != nullptr) {
		this->pointdata->print();
	}
	else {
		std::cout << "(" << this->x << ", " << this->y << ")";
	}
}

void Point::set(double x, double y) {
	this->setX(x);
	this->setY(y);
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

	double e = 1e-7; // epsilon for float comparison error
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
