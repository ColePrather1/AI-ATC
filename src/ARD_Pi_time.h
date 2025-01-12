#include <ctime>
#include <string>
#include <regex>

uint32_t getGPSTimestamp(const std::string& gprmc_sentence) {
  std::regex gprmc_regex(R"(\$GPRMC,(\d{2})(\d{2})(\d{2})\.(\d{2}),A,.*,(\d{2})(\d{2})(\d{2}),)");
  std::smatch match;
  
  if (std::regex_search(gprmc_sentence, match, gprmc_regex)) {
    struct tm timeinfo = {};
    timeinfo.tm_hour = std::stoi(match[1]);
    timeinfo.tm_min = std::stoi(match[2]);
    timeinfo.tm_sec = std::stoi(match[3]);
    timeinfo.tm_mday = std::stoi(match[5]);
    timeinfo.tm_mon = std::stoi(match[6]) - 1; // Month is 0-indexed in struct tm
    timeinfo.tm_year = std::stoi(match[7]) + 100; // Years since 1900
    
    return static_cast<uint32_t>(timegm(&timeinfo));
  }
  return 0; // Return 0 if parsing fails
}
