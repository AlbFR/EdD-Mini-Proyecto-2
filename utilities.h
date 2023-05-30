#ifndef utilities_h
#define utilities_h

#include <iostream>

// This file contains different "small" classes that simplify the code

class Point {
	public:
		int x;
		int y;
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


#endif