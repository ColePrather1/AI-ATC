#pragma once
#include "common.h"
#include "session.h"
#include "Packet.h"





struct IMUEnvPacket {

    uint8_t id;

    float pressure;
    float temperature;
    float baro_altitude;
    float humidity;

};

