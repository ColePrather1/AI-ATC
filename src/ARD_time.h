#include <TinyGPS++.h>

TinyGPSPlus gps;

uint32_t getGPSTimestamp() {
  if (gps.time.isValid() && gps.date.isValid()) {
    tmElements_t tm;
    tm.Hour = gps.time.hour();
    tm.Minute = gps.time.minute();
    tm.Second = gps.time.second();
    tm.Day = gps.date.day();
    tm.Month = gps.date.month();
    tm.Year = gps.date.year() - 1970; // TinyGPS++ returns year as YYYY, we need years since 1970
    return makeTime(tm);
  }
  return 0; // Return 0 if time is not valid
}
