#include "Node.h"
#include <iostream>

Node::Node() {
	std::cerr << "Cannot create a Node w/o Boundary and level" << std::endl;
}

Node::Node(Boundary *b, int l) {
	level_ = l;
	boundary_ = b;
	*children_ = {nullptr};
	pl_ = new PointList();
}

Node::Node(Point *ul, Point *br, int l) {
	level_ = l;
	boundary_ = new Boundary(ul, br);
	*children_ = {nullptr};
	pl_ = new PointList();
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
	 	if (children_[i] != nullptr)
			points += children_[i]->totalPoints();
	return points;
}

int Node::totalNodes() const {
	if (pl_ != nullptr)
		return 1;
	
	int nodes = 0;
	for (int i = 0; i < 4; i++) {
		if (children_[i] != nullptr)
			nodes += children_[i]->totalNodes();
	}
	return nodes + 1;
}

void Node::insert(Point *p) {
	if (!(boundary_->isInBounds(p))) {
		return;
	}

	if (*children_ != nullptr) { // The node has children
		for (int i=0;i<4;++i) {
			if (children_[i] != nullptr)
				children_[i]->insert(p);
		}
		return;
	}

	if (pl_ == nullptr) { // The node w/o children has no points	
		pl_ = new PointList(p);
		return;
	}

	if (pl_->sameCoordsAs(*p)) { // The points in the node are in the same place as the Point being inserted
		pl_->append(p);
		return;
	}

	// The points in the node are in a different place as the one we're trying to insert
	// so we divide the Node
	subdivide();
	for (int i=0;i<4;++i)
	 	if (children_[i] != nullptr)
			children_[i]->insert(pl_);
	this->insert(p);	
	pl_ = nullptr;

}

void Node::insert(PointList *pl) {
	Point *q = new Point(pl->x, pl->y);
	if (!(boundary_->isInBounds(q))) {
		return;
	}

	if (pl_ == nullptr) {
		pl_ = new PointList();
		pl_->append(pl);
		return;
	}
	else {
		if (pl_->sameCoordsAs(*q)) {
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
		return pl_->population();
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
	Point ul = *boundary_->upperleft;
	Point br = *boundary_->bottomright;
	Point *p = new Point(0.0f, 0.0f);
	Point *q = new Point(0.0f, 0.0f);
	double halfX = boundary_->halfX();
	double halfY = boundary_->halfY();

	*p = ul;
	*q = *(boundary_->halfPoint());
	Boundary *b1 = new Boundary(p, q);
	children_[0] = new Node(b1, level_+1);

	p->setX(halfX);
	q->set(br.x, halfY);
	Boundary *b2 = new Boundary(p, q);
	children_[1] = new Node(b2, level_+1);

	p->set(ul.x, halfY);
	q->setX(halfX);
	q->setY(br.y);
	Boundary *b3 = new Boundary(p, q);
	children_[2] = new Node(b3, level_+1);

	*p = *(boundary_->halfPoint());
	*q = br;
	Boundary *b4 = new Boundary(p, q);
	children_[4] = new Node(b4, level_+1);
	std::cout << "Subdivision made :D (print in Node::subdivide())" << std::endl;
	std::cout << "Reached out level: " << level_+1 << std::endl;
}
