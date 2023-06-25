#include "PointList.h"

PointList::PointList() {
	population_ = 0;
}
  
PointList::PointList(Point *p) {
	this->x = p->x;
	this->y = p->y;
	population_ = 0;
	this->append(p);
}

int PointList::population() {
	if (this->container.empty())
		return 0;
	return population_/this->container.size();
}

bool PointList::isEmpty() {
	return !this->container.size();
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
		this->y = p->y;
	}




	// if (!this->isEmpty()) {
		// std::cout << (p == this->top()) << std::endl;
		// p.print();
		// std::cout << std::endl;
		// this->top()->print();
	// }



	this->container.push_back(p);

	// if (!this->isEmpty()) {
	// 	std::cout << (p == this->top()) << std::endl;
	// 	p->print();
	// 	this->top()->print();
	// }


	population_ += p->pointdata->population;
}

void PointList::append(PointList *pl) {
	for (unsigned i=0;i<pl->size();++i) {
		this->append(pl->container[i]);
	}
}

Point* PointList::top() {
	if (this->isEmpty())
		std::cerr << "There's no top element in container" << std::endl;
	return this->container[this->container.size()-1];
}

void PointList::pop() {
	this->container.pop_back();
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