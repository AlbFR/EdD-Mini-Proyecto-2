#include "PointData.h";

PointData::PointData() {
    throw "Cannot create a PointData Object without arguments";
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