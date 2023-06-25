#include <iostream>
#include <fstream>
#include <string>

#include "utilities/readLine.h"

#include "utilities/PointList.h"
#include "QuadTree.h"

void printList(QuadTree *qt) {
	std::vector<PointList> v;
	qt->list(v);

	std::cout << std::endl << "Printing List of size: " << v.size() << std::endl;
	for (unsigned i=0;i<v.size();++i) {
		// std::cout << (nullptr == v[i]) << std::endl;
		v[i].print();
	}
	std::cout << "List printed" << std::endl << std::endl;;
}

int main() {

	std::ifstream file;
    file.open("../dataSet/worldcitiespop_fixed.csv");
	
	if (file.fail()) {
		std::cerr << "Error: The file could not be opened" << std::endl;
		exit(1);
	}
	std::string ignore;
	getline(file, ignore);



	// TESTING

	// // latitude, longitude
	// // latitude [-90, 90]
	// // longitude [-180, 180]

	Point *p = new Point(-90.0f, -180.0f);
	Point *q = new Point(90.0f, 180.0f);

	QuadTree *qt = new QuadTree(new Boundary(p, q));

	int numCities = 6;

	for (int i = 0;i < numCities;++i) {
		PointData *pd = readLine(file);
		Point *p = new Point(pd);
		std::cout << "\n\n\n\n\nINSERTING A NEW POINT...\n\n\n";
		qt->insert(*p);
	}

	printList(qt);

	// std::cout << qt->totalPoints() << std::endl;
	// std::cout << qt->totalNodes() << std::endl;

	// printList(qt);

	file.close();

}