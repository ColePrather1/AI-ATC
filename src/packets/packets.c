#include "packets/packets.h"

/*
#include "Packet.h"
#include "PID.h"
#include "Manual.h"
#include "Auto.h"
#include "Assist.h"
#include "Accel.h"
#include "Gyro.h"
#include "Magnet.h"
#include "GPS.h"
#include "GPS_Env.h"
#include "Barometer.h"
#include "Temp-Humid.h"
#include "Event.h"
#include "EventData8.h"
#include "EventData16.h"
#include "EventData32.h"
#include "EventData64.h"
#include "EventTimed.h"
//#include "EventTimedData.h"
*/



int getPipe(Packet* packet) {
    //PacketType type = packet->type;
    switch (packet->type) {
        //case PacketType::SYSTEM:
        //case PacketType::STATUS:
        //case PacketType::PAIRING:
        //case PacketType::ACK:
        case PacketType::EVENT:
        case PacketType::EVENT_DATA8:
        case PacketType::EVENT_DATA16:
        case PacketType::EVENT_DATA32:
        case PacketType::EVENT_DATA64:
        case PacketType::EVENT_TIMED:
        //case PacketType::EVENT_TIMED_DATA:
            return 0;

        case PacketType::AUTO:
            return 1;
        
        case PacketType::ASSIST:
        case PacketType::MANUAL:
            return 2;

        case PacketType::ACCEL:
        case PacketType::GYRO:
        case PacketType::MAGNET:
            return 3;

        case PacketType::GPS:
        case PacketType::GPS_ENV:
            return 4;
        
        case PacketType::BAROMETER:
        case PacketType::TEMP_HUMID:
        //case PacketType::SENSOR_PACKET:
            return 5;

        case PacketType::BASE:                      // No Pipe / Error Handling
        default:
            return -1;
    }
}

