#ifndef GPS_H
#define GPS_H
#pragma once
#include "Packet.h"
#include <cstdint>

//constexpr double TO_RAD = M_PI / 180.0;
//constexpr uint32_t R = 6371000; // Earth's radius in meters  

// 10 bytes

class GPSPacket : public Packet {
public:
    //float lat;  // Latitude
    //float lon;  // Longitude

    int32_t lat;  // Latitude * 1e7 (degrees)  
    int32_t lon;  // Longitude * 1e7 (degrees)
    int16_t alt;  // Altitude in meters

    GPSPacket(); // : Packet(PacketType::GPS, 'g') {}
    GPSPacket(char hdr, int32_t lat, int32_t lon, int16_t alt);

    void process() override;

};

/*

inline bool inBounds(GPS_Coordinate coordinate){
    const double R = 6371000; // Earth's radius in meters
    double dx = (lon2 - lon1) * cos((lat1 + lat2) / 2);
    double dy = (lat2 - lat1);
    return R * sqrt(dx*dx + dy*dy) * M_PI / 180.0;
    return ATC_RADIUS_METERS_SQUARED
}

double approx_distance_meters(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000; // Earth's radius in meters
    double dx = (lon2 - lon1) * cos((lat1 + lat2) / 2);
    double dy = (lat2 - lat1);
    return R * sqrt(dx*dx + dy*dy) * M_PI / 180.0;
}

inline double approx_distance_meters_squared(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000; // Earth's radius in meters
    double dx = (lon2 - lon1) * cos((lat1 + lat2) / 2);
    double dy = (lat2 - lat1);
    return R * sqrt(dx*dx + dy*dy) * M_PI / 180.0;
}
*/

/*
inline void decode_gps_packet(std::vector<float> &vec, const GPSPacket &pkt) {
    vec[0] = pkt.lat / 1e7;   // Convert latitude to float
    vec[1] = pkt.lon / 1e7;   // Convert longitude to float
    vec[2] = pkt.alt ;//* 100;         // Altitude in meters
}

inline void decode_gps_env_packet(std::vector<float> &vec, const GPSEnvPacket &pkt) {
    vec[0] = pkt.speed / 1e7;;
    vec[1] = pkt.sats;
    vec[2] = pkt.timestamp;
    vec[3] = pkt.course / 1e7;
}
*/


/*
struct GPSData {
  float lat;
  float lon;
  float alt;
  float speed;
  int satellites;
  unsigned long timestamp;
  char header;
};

*/

#endif // GPS_H