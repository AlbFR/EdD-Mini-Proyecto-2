#ifndef Point_h
#define Point_h

#include <iostream>
#include "PointData.h"

class Point {
	public:
		double x;
		double y;
		// This will store the data related to the cities
		PointData* pointdata;
		Point();
		Point(double x, double y);
		Point(PointData data);
		void print();
		void set(double x, double y);
		void setX(double x);
		void setY(double y);
		int compare(Point q) const;
		int compare(Point *q) const;
		void operator=(Point q);
		void print() const;
};

class PointList {
	public:
	 	double x, y;
		std::vector<Point*> container;
		PointList() {}
		PointList(Point *p) {
			this->append(p);
		}
		~PointList() {}
		int population() {
			if (this->container.empty())
				return 0;
			return population_/this->container.size();
		}
		bool sameCoordsAs(Point p) {
			if (this->x != p.x)
				return false;
			if (this->y != p.y)
				return false;
			return true;
		}
		void append(Point *p) {
			this->container.push_back(p);
			population_ += p->pointdata->population;
		}
		void append(PointList *pl) {
			for (unsigned i=0;i<pl->size();++i) {
				this->append(pl->container[i]);
			}
		}
		unsigned size() const {
			return this->container.size();
		}
		void print() const {
			this->container[0]->print();
			for (unsigned i=1;i<this->container.size();++i) {
				std::cout << " --> ";
				this->container[i]->print();
			}
			std::cout << std::endl;
		}

	private:
		unsigned population_;
};

#endif