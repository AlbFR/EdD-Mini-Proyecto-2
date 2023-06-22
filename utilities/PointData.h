#ifndef PointData_h
#define PointData_h

#include <string>

class PointData {
	public:
		std::string country;
		std::string city;
		std::string accentcity;
		std::string region;
		int population;
		double latitude;
		double longitude;
		std::string geopoint;
		PointData();
		PointData(std::string country, std::string city, std::string accentcity, std::string region, int population, double latitude, double longitude, std::string geopoint);
};

#endif