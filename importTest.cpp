#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "utilities/Point.h"
#include "utilities/readLine.h"
#include "utilities/PointData.h"

int main() {
    std::ifstream file1;
    file1.open("dataSet/worldcitiespop_fixed.csv");
    if(file1.fail()) {
        std::cout << "Error: The file could not be open." << std::endl;
        return 1;
    }

    int numCities = 10;
    for(int i = 1; i <= numCities; i++) {
        PointData data = readLine(file1);
        Point* p = new Point(data);
        (*p).print();
        std::cout << std::endl;
        delete p;
    }
    
    file1.close();
    return 0;
}