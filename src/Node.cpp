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
}

Node::Node(Point *ul, Point *br, int l) {
	level_ = l;
	boundary_ = new Boundary(ul, br);
	*children_ = {nullptr};
	pl_ = new PointList();
	num_points_ = 0;
	num_nodes_ = 1;
}

Node::~Node() {
	delete pl_;	
	delete boundary_;
	for (int i=0;i<4;++i)
		delete children_[i];
}

int Node::pointsAmount() const {
	return num_points_;
}

int Node::nodesAmount() const {
	return num_nodes_;
	// if (pl_ != nullptr)
	// 	return 1;
	
	// int nodes = 0;
	// for (int i = 0; i < 4; i++) {
	// 	if (children_[i] != nullptr)
	// 		nodes += children_[i]->totalNodes();
	// }
	// return nodes + 1;
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
	 	// std::cout << "The PointList was empty so, we proceed to insert the Node :p at level " << level_ << std::endl;
		UpdateInfo* update = new UpdateInfo();
		update->nodes = 0;
		update->population = pl_->append(p);
		// std::cout << "Appended at Node with bounds:";
		population_ += update->population;
		num_points_++;
		return update;
	}

	if (pl_->sameCoordsAs(p)) { // The points in the node are in the same place as the Point being inserted
	 	// std::cout << "Turns out the Node was already saving cities at the same location :D" << std::endl;
		UpdateInfo *update = new UpdateInfo();
		update->nodes = 0;
		update->population = pl_->append(p);

		population_ += update->population;
		num_nodes_ += update->nodes;
		num_points_++;
		return update;
	}

	// std::cout << "There's no option, we gotta subdivide :c" << std::endl;
	// The points in the node are in a different place as the one we're trying to insert
	// so we divide the Node
	UpdateInfo *update = new UpdateInfo();
	// update->nodes = 4;
	// update->population = 0;
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
	update->nodes += sum->nodes;
	update->population += sum->population;
	num_points_++;
	num_nodes_ += update->nodes;
	population_ += update->population;
	pl_ = nullptr;

	return update;
}

void Node::list(std::vector<PointList> &v) const {
	// if (this == nullptr)
	// 	return;
	if (pl_ != nullptr) {
		if (!pl_->isEmpty()) {
			v.push_back(*pl_);
			// pl_->print();
		}
		return;
	}

	for (int i=0;i<4;++i) {
		if (children_[i] != nullptr)
			children_[i]->list(v);
	}
}

// Counts nodes
int Node::countRegion(Boundary *b) const {
	boundary_->print();
	if (!b->isPartiallyInBounds(boundary_)) {
		std::cout << "Out of bounds :c" << std::endl;
		return 0;
	}

	if (b->isInBounds(boundary_)) {
		std::cout << "Completely in bounds :D" << std::endl;
		return num_nodes_;
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


	std::cout << "Recursion..." << std::endl;
	int sum = 0;
	for (int i = 0;i < 4;++i) {
		if (children_[i])
		sum += children_[i]->countRegion(b);
	}
	return sum;
}

// Counts population
int Node::agreggateRegion(Boundary *b) const {
	boundary_->print();
	if (!boundary_->isPartiallyInBounds(b)) {
		std::cout << "Out of bounds :c" << std::endl;
		return 0;
	}

	if (boundary_->isInBounds(b)) {
		std::cout << "Completely in bounds :D" << std::endl;
		return population_;
	}
	

	std::cout << "Recursion..." << std::endl;
	int sum = 0;
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
