#include "packets/GPS.h"

#include "Session.h"
#include "EventTypes.h"
#include "Logging.h"
#include <iostream>
#include <cmath>
#include <cstdint>
//#include <stdint.h>

constexpr double TO_RAD = M_PI / 180.0;
constexpr uint32_t R = 6371000; // Earth's radius in meters  

// 10 bytes

GPSPacket::GPSPacket() : Packet(PacketType::GPS, 'g') {}
GPSPacket::GPSPacket(char hdr, int32_t lat, int32_t lon, int16_t alt) : lat(lat), lon(lon), alt(alt), Packet(PacketType::GPS, hdr) {}


void GPSPacket::process() {
        std::cout << "Processing GPS Packet" << std::endl;
        
    // 1) Store Pilot's current GPS data
        Session::plane_gps_lat.store(lat);
        Session::plane_gps_lon.store(lon);
        Session::plane_gps_alt.store(alt);

        
    // 2) Calculate Pilot's distance from ATC (in meters)
        double lat1_rad = lat / 1e7 * TO_RAD;
        double lon1_rad = lon / 1e7 * TO_RAD;
        double lat2_rad = Session::calc_atc_gps_lat / 1e7 * TO_RAD;
        double lon2_rad = Session::calc_atc_gps_lon / 1e7 * TO_RAD;

        double x = (lon2_rad - lon1_rad) * std::cos((lat1_rad + lat2_rad) / 2);
        double y = lat2_rad - lat1_rad;

        double distance = R * std::sqrt(x*x + y*y);
        uint16_t distance_meters = static_cast<uint16_t>(std::round(distance));
        Session::atc_pilot_distance_meters.store(distance_meters);

    // 3) Check if Pilot is within range of ATC
        if (distance_meters > ATC_RADIUS_METERS){
            Session::within_range.store(false);
            // TODO: Return to bounds
            std::cout << "WARNING: Pilot is too far from ATC" << std::endl;
        }

    // 4) Send to SQL Logging 
        Logging::insertGPSData(lat, lon, alt, distance_meters);       
        return;
}



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
