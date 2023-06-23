#include "Node.h"
#include <iostream>

Node::Node(Boundary *b) {
	boundary_ = b;
	*children_ = {nullptr};
	pl_ = nullptr;
}

Node::Node(Point *ul, Point *br) {
	boundary_ = new Boundary(ul, br);
	*children_ = {nullptr};
	pl_ = nullptr;
}

Node::~Node() {
	delete pl_;	
	delete boundary_;
	for (int i=0;i<4;++i)
		delete children_[i];
}

int Node::totalPoints() const {
	if (pl_ != nullptr)
		return pl_->size();

	int points = 0;
	for (int i=0;i<4;++i)
		points += children_[i]->totalPoints();
	return points;
}

int Node::totalNodes() const {
	if (*children_ == nullptr)
		return 1;
	
	int nodes = 1;
	for (int i = 0; i < 4; i++) {
		nodes += children_[i]->totalNodes();
	}
	return nodes;
}

void Node::insert(Point &p) {
	if (!(boundary_->isInBounds(p))) {
		return;
	}

	if (pl_ == nullptr) {
		pl_ = new PointList(&p);
		return;
	}
	else {
		if (pl_->sameCoordsAs(p)) {
			pl_->append(&p);
			return;
		}
		else {
			subdivide();
			this->insert(pl_);
			pl_ = nullptr;
		}
	}
	
	for (int i=0;i<4;++i) {
		children_[i]->insert(p);
	}
}

void Node::insert(PointList *pl) {
	Point *head = pl->head->point;
	if (!(boundary_->isInBounds(*head))) {
		return;
	}

	if (pl_ == nullptr) {
		pl_->append(pl);
		return;
	}
	else {
		if (pl_->sameCoordsAs(*head)) {
			pl_->append(pl);
			return;
		}
		else {
			subdivide();
			this->insert(pl_);
			pl_ = nullptr;
		}
	}
	
	for (int i=0;i<4;++i) {
		children_[i]->insert(pl);
	}
}

void Node::list(std::vector<PointList*> &v) const {
	// std::cerr << (this==nullptr) << std::endl;
	// if (this == nullptr)
	// 	return;
	if (pl_ != nullptr) {
		// std::cerr << "The next PL was appended to the list vector: ";
		// pl_->print();
		v.push_back(pl_);
		return;
	}
	for (int i=0;i<4;++i) {
		if (children_[i] != nullptr)
			children_[i]->list(v);
	}
}

// Counts nodes
int Node::countRegion(Boundary *b) const {
	if (!boundary_->isPartiallyInBounds(b))
		return 0;

	if (pl_ != nullptr)
		return pl_->size();

	int sum = 0;
	for (int i = 0;i < 4;++i) {
		sum += children_[i]->countRegion(b);
	}
	return sum;
}

// Counts population
int Node::agreggateRegion(Boundary *b) const {
	if (!boundary_->isPartiallyInBounds(b))
		return 0;

	if (pl_ != nullptr) {
		// return pl_->population();
	}	
	
	int sum = 0;
	for (int i = 0;i < 4;++i) {
		sum += children_[i]->countRegion(b);
	}
	return sum;
}

void Node::showPoints() const {
	pl_->print();
}

void Node::subdivide() {
	Point *ul = boundary_->upperleft;
	Point *br = boundary_->bottomright;
	Point *p = new Point(0.0f, 0.0f);
	Point *q = new Point(0.0f, 0.0f);
	double halfX = boundary_->halfX();
	double halfY = boundary_->halfY();

	*p = *ul;
	*q = *(boundary_->halfPoint());
	children_[0] = new Node(p, q);

	p->setX(halfX);
	q->setX(br->x);
	q->setY(halfY);
	children_[1] = new Node(p, q);

	p->setX(ul->x);
	p->setY(halfY);
	q->setX(halfX);
	q->setY(ul->y);
	children_[2] = new Node(p, q);

	*p = *(boundary_->halfPoint());
	*q = *br;
	children_[4] = new Node(p, q);
	std::cout << "Subdivision made :D (print in Node::subdivide())" << std::endl;
}
