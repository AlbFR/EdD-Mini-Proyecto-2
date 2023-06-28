#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

#include "utilities/readLine.h"

#include "utilities/PointList.h"
#include "QuadTree.h"

// void printList(QuadTree *qt) {
// 	std::vector<PointList> v;
// 	qt->list(v);

// 	std::cout << std::endl << "Printing List of size: " << v.size() << std::endl;

// 	// for (unsigned i=0;i<v.size();++i)
// 	// 	v[i].print();

// 	std::cout << "List printed" << std::endl << std::endl;;
// }

long double testInsert(long long n, std::vector<Point> &v) {



	Point *p = new Point(-90.0f, -180.0f);
	Point *q = new Point(90.0f, 180.0f);
	Boundary *b = new Boundary(p, q);
	long double total_time = 0;
	const long long tests = 10;

	auto start_time = std::chrono::high_resolution_clock::now();
	auto end_time = std::chrono::high_resolution_clock::now();
	for (long long k = 0;k < tests;++k) {

		QuadTree *qt = new QuadTree(b);

		for (long long i = 0; i < n;++i) {
			qt->insert(v[i]);
		}

		// total_time += duration_time;

		// std::cout << "Test " << k+1 << " completed" << std::endl;
		// std::cout << "Total Time: " << total_time << std::endl << std::endl;
		// delete qt;
	}
	auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();
	return duration_time/tests;
}
 
 void readFile(std::vector<Point> &v, long long n) {
	std::cout << "Reading Dataset..." << std::endl;
	std::ifstream file;
	file.open("../dataSet/worldcitiespop_fixed.csv");
	if (file.fail()) {
		std::cerr << "Error: The file could not be opened" << std::endl;
		exit(1);
	}
	std::string ignore;
	getline(file, ignore);
	
	// const long long n = 3173647;
	// const long long n = 200000;

	Point *q = new Point(0.0f, 0.0f);
	v.resize(n, *q);

	for (long long i = 0; i < n;++i) {
		// Point *p = new Point(readLine(file));
		// p->print();

		v[i] = *(new Point(readLine(file)));
	}
	file.close();
	std::cout << "Dataset read without issues" << std::endl;
 }

int main(int argc, char *argv[]) {

 
	std::vector<Point> v;
	long long n = 100000;
	std::cin >> n;
	readFile(v, n);

	std::cout << "Time for n = " << n << std::endl;
	std::cout << std::fixed << std::setprecision(15) << testInsert(n, v) << std::endl << std::endl;

	// n = 200000;
	// std::cout << "Time for n = " << n << std::endl;
	// std::cout << std::setprecision(18) << testInsert(n, v) << std::endl << std::endl;

	// n = 400000;
	// std::cout << "Time for n = " << n << std::endl;
	// std::cout << testInsert(n) << std::endl << std::endl;

	// n = 800000;
	// std::cout << "Time for n = " << n << std::endl;
	// std::cout << testInsert(n) << std::endl << std::endl;

	// n = 1600000;
	// std::cout << "Time for n = " << n << std::endl;
	// std::cout << testInsert(n) << std::endl << std::endl;

	// n = 3173647;
	// std::cout << "Time for n = " << n << std::endl;
	// std::cout << testInsert(n) << std::endl << std::endl;

}
