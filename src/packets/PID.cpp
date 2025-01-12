#include "packets/PID.h"
#include "Logging.h"
#include "PIDFeature.h"
//#include "Session.h"
//#include "Common.h"

PIDPacket::PIDPacket(char hdr, PIDFeature feature_id, double Kp, double Ki, double Kd) : Packet(PacketType::PID, hdr), feature_id(feature_id), Kp(Kp), Ki(Ki), Kd(Kd) {}


void PIDPacket::process() {
  // TODO: Implement ATC-based PID controller
    Logging::insertPIDData(feature_id, Kp, Ki, Kd);
}
