#include "PointList.h"

PointList::PointList() {}
  
PointList::PointList(Point *p) {
	this->x = p->x;
	this->y = p->y;
	this->append(p);
}

int PointList::population() {
	if (this->container.empty())
		return 0;
	return population_/this->container.size();
}

bool PointList::sameCoordsAs(Point p) {
	if (this->x != p.x)
		return false;
	if (this->y != p.y)
		return false;
	return true;
}

void PointList::append(Point *p) {
	if (this->container.empty()) {
		this->x = p->x;
		this->y = p-> y;
	}
	this->container.push_back(p);
	population_ += p->pointdata->population;
}

void PointList::append(PointList *pl) {
	for (unsigned i=0;i<pl->size();++i) {
		this->append(pl->container[i]);
	}
}

unsigned PointList::size() const {
	return this->container.size();
}

void PointList::print() const {
	if (!this->container.empty())
		this->container[0]->print();
	for (unsigned i=1;i<this->container.size();++i) {
		std::cout << " --> ";
		this->container[i]->print();
	}
	std::cout << std::endl;
}