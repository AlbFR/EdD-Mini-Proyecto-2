#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include "QuadTree.h"
#include "utilities/readLine.h"

int main() {
	
	std::ifstream file;
    file.open("worldcitiespop_fixed.csv");
	
	if (file.fail()) {
		std::cerr << "Error: The file could not be opened" << std::endl;
		exit(1);
	}

	// latitude, longitude
	// latitude [-90, 90]
	// longitude [-180, 180]

	Point *p = new Point(-180.0f, -180.0f);
	Point *q = new Point(180.0f, 180.0f);
	QuadTree *qt = new QuadTree(new Boundary(p, q));

	int numCities = 10;

	std::string ignore;
	getline(file, ignore);
	for (int i = 0;i < numCities;++i) {
		PointData pd = readLine(file);
		qt->insert(*(new Point(pd)));
	}

    file.close();

	std::cout << "Total points: " << qt->totalPoints() << std::endl;
    std::cout << "Total nodes: " << qt->totalNodes() << std::endl;

	/*std::vector<PointList> v;
	qt->list(v);

	for (int i=0;i<v.size();++i) {
		v[i].print();
	}*/

    Point *center = new Point(0.0f, 0.0f);
    int radius = 180;
    int pointsNum = qt->countRegion(*center, radius);
    std::cout << "The number of points in the region with center ";
    center->print();
    std::cout << " and radius " << radius << " is " << pointsNum << std::endl;

    int pop = qt->aggregateRegion(*center, radius);
    std::cout << "The population in the region with center ";
    center->print();
    std::cout << " and radius " << radius << " is " << pop << std::endl;


    /*srand (time(NULL));

    int reps = 10;
    double duration = 0;
    int elementos = 100000;
    for(int i = 0; i < reps; i++){
        VectorList* vectorlist = new VectorList;
        auto start = chrono::high_resolution_clock::now();
        //####################INICIO DEL CLOCK####################
        for(int j = 0; j < elementos; j++) {
            vectorlist->insertAt(j, 1);
        }
        //#####################FIN DEL CLOCK######################
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff = end - start;
        duration += diff.count();
        delete vectorlist;
    }
    duration /= reps;
    cout << "Medicion de insertAt() VectorList: " << endl;
    cout << "cantidad de elementos a insertar al final: " << elementos << endl;
    cout << "timpo promedio: " << duration << endl;*/
    return 0;
}