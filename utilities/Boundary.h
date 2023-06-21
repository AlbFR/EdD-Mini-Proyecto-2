#ifndef Boundary_h
#define Boundary_h

#include "Point.h"

class Boundary {
	public:
		Point *upperleft;
		Point *bottomright;
		Boundary();
		Boundary(Point *p, int d);
		Boundary(Point *ul, Point *br);
		bool isInBounds(Point p);
        bool isInBounds(Point *p);
		bool isInBounds(Boundary *b);
		bool isPartiallyInBounds(Boundary *b);
		void print();
};

#endif