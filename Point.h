#ifndef Point_h
#define Point_h

#include <iostream>
#include "utilities.h"

class Point {
	public:
		double x;
		double y;
		PointData pd;

		Point() {
			throw "Cannot create a Point Object without x and y arguments";
		}

		Point(double x, double y) {
			this->x = x;
			this->y = y;
		}

		void print() {
			std::cout << "(" << this->x << ", " << this->y << ")";
		}

		void setX(double x) {
			this->x = x;
		}

		void setY(double y) {
			this->y = y;
		}

		bool operator<(Point q) {
			if (this->x < q.x && this->y < q.y)
				return true;
			return false;
		}

		bool operator<=(Point q) {
			if (this->x <= q.x && this->y <= q.y)
				return true;
			return false;
		}
};

#endif