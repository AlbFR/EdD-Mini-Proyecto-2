#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PointData.h"

PointData readLine(std::ifstream &file) {
    if(file.fail()) {
        throw "There was an error reading the file.";
    }
    std::string line;
    std::string data;
    std::vector<std::string> citydata;
    getline(file, line);
    std::stringstream lineStream(line);
    while(getline(lineStream, data, ';')) {
        citydata.push_back(data);
    }
    std::replace(citydata[5].begin(), citydata[5].end(), ',', '.');
    std::replace(citydata[6].begin(), citydata[6].end(), ',', '.');
    PointData city(citydata[0], citydata[1], citydata[2], citydata[3], std::stoi(citydata[4]), std::stod(citydata[5]), std::stod(citydata[6]), citydata[7]);
    return city;
}