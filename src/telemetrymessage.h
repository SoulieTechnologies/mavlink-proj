#include <stdio.h>
#include <string>
#include <vector>

class TelemetryMessage{
public:
    virtual std::string serialize(){
        return ("base message");
    }
};

class HeartbeatMessage : public TelemetryMessage{
private:
    int state;
public:
    std::string serialize(){
        return("bip bip bip");
    }
};

class GPSMessage : public TelemetryMessage{
private:
    double latitude;
    double longitude;
public:
    GPSMessage(double lat, double lon){
        latitude = lat;
        longitude = lon;
    }
    std::string serialize(){
        return("latitude: " + std::to_string(latitude) + "\n\rlongitude: " + std::to_string(longitude));
    }
};