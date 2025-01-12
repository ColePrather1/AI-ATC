#include <cstdint>
#include <atomic>

#include "SyncedObjects.h"
#include "Bitmask.h"


Bitmask ATC_synced;
Bitmask Airplane_synced;

//Bitmask bm;

enum class ControlMode {
    // Define your control modes here
    MANUAL
};

struct FlightParameters {
    std::atomic<ControlMode> control_mode;
    std::atomic<bool> throttle_lock, within_range, returning_home;
    bool paired, gps_active, flying, fixed_altitude, fixed_heading;
};



std::atomic<ControlMode> control_mode = ControlMode::MANUAL;
std::atomic<bool> throttle_lock = false, within_range = false, returning_home = false;
bool paired = false, gps_active = false, flying = false, fixed_altitude = false, fixed_heading = false;



// Encoding function
/*
uint16_t encode_flight_parameters(const FlightParameters& params) {
    Bitmask bm;
    bm[0] = params.throttle_lock.load();
    bm[1] = params.within_range.load();
    bm[2] = params.returning_home.load();
    bm[3] = params.paired;
    bm[4] = params.gps_active;
    bm[5] = params.flying;
    bm[6] = params.fixed_altitude;
    bm[7] = params.fixed_heading;
    return bm.mask;
    //return bm;
}
*/

// Encoding function

// SEND LOCAL
void encode_flight_parameters() {
    ATC_synced[0] = throttle_lock.load();
    ATC_synced[1] = within_range.load();
    ATC_synced[2] = returning_home.load();
    ATC_synced[3] = paired;
    ATC_synced[4] = gps_active;
    ATC_synced[5] = flying;
    ATC_synced[6] = fixed_altitude;
    ATC_synced[7] = fixed_heading;
}



void decode_flight_parameters(uint16_t encoded_mask) {
    Bitmask bm(encoded_mask);
    params.throttle_lock.store(bm[0]);
    params.within_range.store(bm[1]);
    params.returning_home.store(bm[2]);
    params.paired = bm[3];
    params.gps_active = bm[4];
    params.flying = bm[5];
    params.fixed_altitude = bm[6];
    params.fixed_heading = bm[7];
}



void DEV_decode_flight_parameters(uint16_t encoded_mask, FlightParameters& params) {
    Bitmask bm(encoded_mask);
    params.throttle_lock.store(bm[0]);
    params.within_range.store(bm[1]);
    params.returning_home.store(bm[2]);
    params.paired = bm[3];
    params.gps_active = bm[4];
    params.flying = bm[5];
    params.fixed_altitude = bm[6];
    params.fixed_heading = bm[7];
}



// Decoding function
/*
void decode_flight_parameters(uint16_t encoded_mask, FlightParameters& params) {
    Bitmask bm(encoded_mask);
    params.throttle_lock.store(bm[0]);
    params.within_range.store(bm[1]);
    params.returning_home.store(bm[2]);
    params.paired = bm[3];
    params.gps_active = bm[4];
    params.flying = bm[5];
    params.fixed_altitude = bm[6];
    params.fixed_heading = bm[7];
}
*/

