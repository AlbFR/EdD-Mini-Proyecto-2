#ifndef utilities_h
#define utilities_h

#include <iostream>

// This file contains different "small" classes that simplify the code

class Point {
	public:
		int x;
		int y;

		Point() {
			throw "Cannot create a Point Object without x and y arguments";
		}

		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}

		void print() {
			std::cout << "(" << this->x << ", " << this->y << ")";
		}

		void setX(int x) {
			this->x = x;
		}

		void setY(int y) {
			this->y = y;
		}
};

class Boundary {
	public:
		Point upperleft;
		Point lowerright;

		Boundary(Point ul, Point lr) {
			if (ul.x > lr.x || ul.y > lr.y)
				throw "Cannot create Boundary, upperLeft Point must be lower than lowerRight Point";
			
			this->upperleft = ul;
			this->lowerright = lr;
		}

		void print() {
			std::cout << "Upper Left bound: ";
			upperleft.print();
			std::cout << std::endl << "Lower Right bound: ";
			lowerright.print();
			std::cout << std::endl;
		}
};

#endif