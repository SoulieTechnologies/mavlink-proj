#include <stdio.h>
#include <cmath>

class Waypoint {
private:
    double latitude;
    double longitude;
    double altitude;
public:
    Waypoint(double latitude, double longitude, double altitude){
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

int main(){
    Waypoint wp1(40.7128, -74.0060, 0), wp2(34.0522, -118.2437, 20.0);
    wp1.printLocation();
    printf("The distance between wp1 and wp2 is: %.2f meters\n\r", wp2.calculateDistance(wp1));
}