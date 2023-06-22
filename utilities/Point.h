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
		void setX(double x);
		void setY(double y);
		int compare(Point q) const;
		int compare(Point *q) const;
		void operator=(Point q);
		void print() const;
};

class PointNode {
	public:
		Point *point;
		PointNode *next;
		PointNode(Point *p) {
			this->point = p;
			this->next = nullptr;
		}
		// PointNode(Point *p, Point *next) {
		// 	this->point = p;
		// 	PointNode *pn = new PointNode(next);
		// 	this->next = pn;
		// }
		PointNode(Point *p, PointNode *next) {
			this->point = p;
			this->next = next;
		}
		void print() {
			this->point->print();
		}
};

class PointList {
	public:
	 	double x, y;
		PointNode *head;
		PointNode *tail;
		PointList() {
			this->head = nullptr;
			this->tail = nullptr;
			amount_ = 0;
		}
		PointList(Point *p) {
			amount_ = 0;
			this->append(p);
			// p.print();
			// this->head->print();
		}
		PointList(PointNode *p) {
			this->head = p;
			this->tail = p;
			amount_ = 1;
		}
		~PointList() {
			delete tail;
			delete head;
		}
		int population();
		bool sameCoordsAs(Point p) {
			if (this->head->point->x != p.x)
				return false;
			if (this->head->point->y != p.y)
				return false;
			return true;
		}
		void append(PointNode *pn) {
			if (!amount_)
				this->tail = pn;
			else
				pn->next = this->head;

			this->head = pn;
			amount_++;
		}
		void append(Point *p) {
			PointNode *pn = new PointNode(p);
			this->append(pn);
		}
		void append(PointList *pl) {
			if (!amount_) {
				this->head = pl->head;
				this->tail = pl->head;
				amount_ = pl->size();
				return;
			}

			this->tail->next = pl->head;
			this->tail = pl->tail;
		}
		unsigned size() const {
			return amount_;
		}
		void print() const {
			PointNode *current = this->head;
			while (current != nullptr) {
				current->print();
				std::cout << " --> ";
				current = current->next;
			}
			std::cout << std::endl;
		}

	private:
		unsigned amount_;
};

#endif