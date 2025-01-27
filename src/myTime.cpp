#include "myTime.h"
#include "Session.h"


static uint32_t local_timeOfFlight = 0;
static uint32_t local_StarttimeOfFlight = 0;

std::chrono::steady_clock::time_point local_flight_start_time;

//std::chrono::milliseconds myTime::getFlightTime() {
//  return  static_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - local_flight_start_time);
//}

std::chrono::milliseconds myTime::getFlightTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - local_flight_start_time);
}


uint32_t myTime::getTimestamp() {
  auto now = std::chrono::system_clock::now();
  return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
}

