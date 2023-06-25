#include <iostream>
#include <iomanip>
#include "PointData.h"

PointData::PointData() {
    std::cerr << "Cannot create a PointData Object without arguments" << std::endl;
}

PointData::PointData(std::string country, std::string city, std::string accentcity, std::string region, int population, double latitude, double longitude, std::string geopoint) {
    country_ = country;
    city_ = city;
    accentcity_ = accentcity;
    region_ = region;
    this->population = population;
    this->latitude = latitude;
    this->longitude = longitude;
    geopoint_ = geopoint;
}

void PointData::print() {
	std::cout << "Geopoint:   (" << std::setprecision(15) << this->latitude << ", ";
	std::cout << std::setprecision(15) << this->longitude << ")" << std::endl;
    std::cout << "Country:    " << country_ << std::endl;
    std::cout << "City:       " << city_ << std::endl;
	std::cout << "Population: " << this->population << std::endl;
}