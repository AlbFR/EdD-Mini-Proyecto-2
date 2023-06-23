#include <iostream>
#include "PointData.h"

PointData::PointData() {
    std::cerr << "Cannot create a PointData Object without arguments" << std::endl;
}

PointData::PointData(std::string country, std::string city, std::string accentcity, std::string region, int population, double latitude, double longitude, std::string geopoint) {
    this->country = country;
    this->city = city;
    this->accentcity = accentcity;
    this->region = region;
    this->population = population;
    this->latitude = latitude;
    this->longitude = longitude;
    this->geopoint = geopoint;
}

void PointData::print() {
    std::cout << "City: " << this->city;
	std::cout << "; Population: " << this->population;
	std::cout << std::endl;
}