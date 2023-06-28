#include "PointList.h"

PointList::PointList() {
	population_ = 0;
}
  
PointList::PointList(Point p) {
	this->x = p.x;
	this->y = p.y;
	population_ = 0;
	this->append(p);
}

PointList::~PointList() {}

int PointList::population() {
	if (this->container.empty())
		return 0;
	return population_/(this->container.size());
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

long long PointList::append(Point p) {
	if (this->container.empty()) {
		this->x = p.x;
		this->y = p.y;
	}

	this->container.push_back(p);

	if (p.pointdata != nullptr) {
		if (this->container.empty()) {
			population_ += p.pointdata->population;
			// std::cout << "This differs on " << population_ << std::endl;
			return population_;
		}
			
		long long r = population_;
		population_ += p.pointdata->population/this->container.size();
		r *= -1;
		r += population_;
		// std::cout << "This differs on " << r << std::endl;
		return r;
	}

	else {
		std::cerr << "You should not be using append in a node w/o PointData" << std::endl;
		return 0;
	}
}

// long long PointList::append(PointList *pl) {
// 	for (unsigned i=0;i<pl->size();++i) {
// 		this->append(pl->container[i]);
// 	}
// }

Point PointList::top() {
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
		this->container[0].print();
	for (unsigned i=1;i<this->container.size();++i) {
		std::cout << " --> ";
		this->container[i].print();
	}
	std::cout << std::endl;
}