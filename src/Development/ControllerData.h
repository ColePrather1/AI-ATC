#pragma once
#include "common.h"



class ControllerData {
public:
    ControllerData(const char* table, const char* field, std::string value) : table(table), field(field), value(value) {}
    const char* table;
    const char* field;
    //int value;
    time_t timestamp;
    std::string value;
};

