#include <stdio.h>
#include <cmath>
#include <stdexcept>

class Waypoint {
private:
    double latitude;
    double longitude;
    double altitude;
public:
    Waypoint(double latitude, double longitude, double altitude){
        if (altitude < 0) {
            throw std::invalid_argument("Altitude cannot be negative");
        }
        this->latitude = latitude;
        this->longitude = longitude;
        this->altitude = altitude; 
    }
    void printLocation(){
        printf("The drone is located at:\n\rlatitude: %.2f,\n\rlongitude: %.2f,\n\raltitude: %.2f\n\r", latitude, longitude, altitude);
    }
    double calculateDistance(const Waypoint& other){
        double dlat = latitude - other.latitude;
        double dlon = longitude - other.longitude;
        double dalt = altitude - other.altitude;
        double distance = std::hypot(dlat,dlon,dalt);
        return distance;
    }
};
