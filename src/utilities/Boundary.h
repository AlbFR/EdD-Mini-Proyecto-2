#ifndef Boundary_h
#define Boundary_h

#include "Point.h"

class Boundary {
	public:
		Point *upperleft;
		Point *bottomright;
		Point *next;
		Boundary();
		Boundary(Boundary *b);
		Boundary(Point *p, int d);
		Boundary(Point *ul, Point *br);
		double halfX() const;
		double halfY() const;
		Point* halfPoint() const;
		bool isInBounds(Point p) const;
        bool isInBounds(Point *p) const;
		bool isInBounds(Boundary *b) const;
		bool isPartiallyInBounds(Boundary *b) const;
		void print() const;
		void operator=(Boundary b);
};

#endif