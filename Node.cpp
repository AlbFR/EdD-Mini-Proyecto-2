#include "Node.h"

Node::Node(Boundary *boundary) {
	boundary_ = boundary;	
	*children_ = {nullptr};
}

Node::~Node() {}

int Node::totalPoints() {
	if (p_ != nullptr)
		return 1;

	if (*children_ == nullptr)
		return 0;

	int points = 0;
	for (int i=0;i<4;++i)
		points += children_[i]->totalPoints();
}

int Node::totalNodes() {
	if (*children_ == nullptr)
		return 0;
	
	return 4;
}

void Node::insert(Point p) {
	if (!boundary_->isInBounds(p))
		return;

	
	for (int i=0;i<4;++i)
		children_[i]->insert(p);
}

std::vector<Node> Node::list() {

}

int Node::countRegion(Boundary *b) {
	if (!boundary_->isPartiallyInBounds(b))
		return 0;

	int sum = 0;
	for (int i = 0;i < 4;++i) {
		sum += children_[i]->countRegion(b);
	}
	return sum;
}

int Node::agreggateRegion(Boundary *b) {
	if (!boundary_->isPartiallyInBounds(b));
		return 0;
	
	int sum = 0;
	for (int i = 0;i < 4;++i) {
		sum += children_[i]->countRegion(b);
	}
	return sum;
}