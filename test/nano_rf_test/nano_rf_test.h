
//#include <cstdint>

#define SOH 0x01  // Start of Header
#define NULL_CHAR 0x00  // Null character
#define STX 0x02  // Start of Text
#define ETX 0x03  // End of Text
#define EOT 0x04  // End of Transmission
#define RECSEP 0x1E  // Record Seporator


enum class PacketType : uint8_t {
    BASE,
    // System Data
    //SYSTEM,
    //STATUS,
    PID,
    // Pairing
    //PAIRING,
    // Control Modes
    AUTO,
    ASSIST,
    MANUAL,
    // IMU Data     // (d, x,y,z) in each packet
    ACCEL,
    GYRO,
    MAGNET,
    // GPS Data
    GPS,
    GPS_ENV,
    // Sensor Data
    BAROMETER,       // LPS22HB
    TEMP_HUMID,      // HS3003
    //MIC_PACKET,           // MP34DT06JTR
    //GESTURE_PACKET,       // APDS9960
    //LIDAR_PACKET,         // TF-Luna
    // Acknowledgement
    //ACK,
    EVENT,
    //EVENT_DATA,
    EVENT_DATA8,
    EVENT_DATA16,
    EVENT_DATA32,
    EVENT_DATA64,
    EVENT_TIMED,
    EVENT_TIMED_DATA
};


class Packet {
public:
    PacketType type;
    char header;



    Packet() : type(PacketType::BASE), header(0) {}
    Packet(PacketType t, char hdr) : type(t), header(hdr) {}
    virtual ~Packet() = default;

    virtual void process() = 0;


    //virtual void serialize(char* buffer) const = 0;     // Encode
    //virtual void deserialize(const char* buffer) = 0;   // Decode
};



// 12 Bytes
class ManualPacket : public Packet {
public:
    uint8_t throttle;
    uint8_t elevator;
    uint8_t rudder;
    uint8_t left_aileron;
    uint8_t right_aileron;

    ManualPacket() : Packet(PacketType::MANUAL, 'm') {}

    ManualPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron) 
    : throttle(throttle), elevator(elevator), rudder(rudder), left_aileron(left_aileron), right_aileron(right_aileron), 
    Packet(PacketType::MANUAL, hdr) {}
    

    // Process function for Aircraft
    void process() {
    // Implement processing
    //std::cout << "Processing Manual Packet" << std::endl;
    return;
}

};













