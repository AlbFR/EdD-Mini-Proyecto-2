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
	num_points_ = 0;
	num_nodes_ = 1;
	population_ = 0;
}

Node::Node(Point *ul, Point *br, int l) {
	level_ = l;
	boundary_ = new Boundary(ul, br);
	*children_ = {nullptr};
	pl_ = new PointList();
	num_points_ = 0;
	num_nodes_ = 1;
	population_ = 0;
}

Node::~Node() {
	for (int i=0;i<4;++i) {
		if (children_[i] != nullptr)
			delete children_[i];
	}
	// delete []children_;
	delete pl_;	
	delete boundary_;
	delete this;
}

int Node::pointsAmount() const {
	return num_points_;
}

int Node::nodesAmount() const {
	return num_nodes_;
}

UpdateInfo* Node::insert(Point p) {

	if (!(boundary_->isInBounds(p)))
		return nullptr;

	if (pl_ == nullptr) { // The node has children
		// std::cout << "The node has children" << std::endl;
		UpdateInfo *update = new UpdateInfo();
		for (int i=0;i<4;++i) {
			if (children_[i] != nullptr) {
				update = children_[i]->insert(p);
				if (update != nullptr)
					break;
			}
		}
		population_ += update->population;
		num_nodes_ += update->nodes;
		num_points_++;
		return update;
	}

	if (pl_->isEmpty()) { // The node w/o children has no points	
		UpdateInfo* update = new UpdateInfo();
		update->nodes = 0;
		update->population = pl_->append(p);
		population_ += update->population;
		num_points_++;
		return update;
	}

	if (pl_->sameCoordsAs(p)) { // The points in the node are in the same place as the Point being inserted
		UpdateInfo *update = new UpdateInfo();
		update->nodes = 0;
		update->population = pl_->append(p);

		population_ += update->population;
		num_nodes_ += update->nodes;
		num_points_++;
		return update;
	}

	UpdateInfo *update = new UpdateInfo();
	subdivide();

	for (unsigned j=0;j<pl_->size();++j) {
		for (int i=0;i<4;++i) {
			if (children_[i] != nullptr) {
				update = children_[i]->insert(pl_->top());
				if (update != nullptr)
					break;
			}
		}
		pl_->pop();
		if (update != nullptr)
			break;
	}
	update->nodes += 4;
	UpdateInfo *sum = new UpdateInfo();
	for (int i=0;i<4;++i) {
		if (children_[i] != nullptr) {
			sum = children_[i]->insert(p);
			if (sum != nullptr) break;
		}
	}
	update->nodes = sum->nodes;
	update->population = sum->population;
	num_points_++;
	num_nodes_ += update->nodes;
	population_ += update->population;
	// pl_ = nullptr;
	delete pl_;
	pl_ = nullptr;


	return update;
}

void Node::list(std::vector<PointList> &v) const {
	if (pl_ != nullptr) {
		if (!pl_->isEmpty()) {
			v.push_back(*pl_);
		}
		return;
	}

	for (int i=0;i<4;++i) {
		if (children_[i] != nullptr)
			children_[i]->list(v);
	}
}

// Counts Points
int Node::countRegion(Boundary *b) const {
	if (!b->isPartiallyInBounds(boundary_)) {
		// std::cout << "Out of bounds :c" << std::endl;
		return 0;
	}

	if (b->isInBounds(boundary_)) {
		// std::cout << "Completely in bounds :D" << std::endl;
		return num_points_;
	}


	if (children_[0] == nullptr) { // Has no children
		if (!pl_->isEmpty()) {
			if (b->isInBounds(new Point(pl_->x, pl_->y)))
				return pl_->size();
			else
				return 0;
		}
		else
			return 0;
	}


	// std::cout << "Recursion..." << std::endl;
	int sum = 0;
	for (int i = 0;i < 4;++i) {
		if (children_[i])
		sum += children_[i]->countRegion(b);
	}
	return sum;
}

// Counts population
long long Node::agreggateRegion(Boundary *b) const {
	// b->print();
	// boundary_->print();
	if (!b->isPartiallyInBounds(boundary_)) {
		// std::cout << "Out of bounds :c" << std::endl;
		return 0;
	}

	if (b->isInBounds(boundary_)) {
		// std::cout << "Completely in bounds :D" << std::endl;
		// std::cout << "return " << population_ << std::endl;
		return population_;
	}
	
	if (children_[0] == nullptr) { // Has no children
		if (!pl_->isEmpty()) {
			if (b->isInBounds(new Point(pl_->x, pl_->y)))
				return population_;
			else
				return 0;
		}
		else
			return 0;
	}

	// std::cout << "Recursion..." << std::endl;
	long long sum = 0;
	for (int i = 0;i < 4;++i) {
		sum += children_[i]->agreggateRegion(b);
	}
	return sum;
}

void Node::showPoints() const {
	pl_->print();
}

void Node::subdivide() {
	Point ul = *boundary_->upperleft;
	Point br = *boundary_->bottomright;

	double halfX = boundary_->halfX();
	double halfY = boundary_->halfY();

	Point p = ul;
	Point q = *(boundary_->halfPoint());
	Boundary *b1 = new Boundary(p, q);
	children_[0] = new Node(b1, level_+1);

	p.setX(halfX);
	q.set(br.x, halfY);
	Boundary *b2 = new Boundary(p, q);
	children_[1] = new Node(b2, level_+1);

	p.set(ul.x, halfY);
	q.setX(halfX);
	q.setY(br.y);
	Boundary *b3 = new Boundary(p, q);
	children_[2] = new Node(b3, level_+1);

	p = *(boundary_->halfPoint());
	q = br;
	Boundary *b4 = new Boundary(p, q);
	children_[3] = new Node(b4, level_+1);
}
