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

int main(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    std::vector<TelemetryMessage*> messages;
    HeartbeatMessage* heartbeat = new HeartbeatMessage();
    GPSMessage* gps = new GPSMessage(12, 2.5);
    messages.push_back(heartbeat);
    messages.push_back(gps);
    for (TelemetryMessage* msg: messages){
        printf("Serialized message: %s\n\r", msg->serialize().c_str());
    }
    for (TelemetryMessage* msg: messages){
        delete msg;
    }
}