#ifndef PointData_h
#define PointData_h

#include <string>

class PointData {
	public:
		double latitude;
		double longitude;
		unsigned population;
		PointData();
		PointData(std::string country, std::string city, std::string accentcity, std::string region, int population, double latitude, double longitude, std::string geopoint);
		void print();

	private:
		std::string country_;
		std::string city_;
		std::string accentcity_;
		std::string region_;
		std::string geopoint_;
};

#endif