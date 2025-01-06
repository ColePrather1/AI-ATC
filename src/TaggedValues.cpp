
#include <iostream>



/*
    Basic Usage:
*/
union NumericType {
    int intValue;
    float floatValue;
    double doubleValue;
};

NumericType num;
num.intValue = 42;
// Now num.floatValue and num.doubleValue are undefined




/*
    With Tag Fields: Often, unions are used with an accompanying enum to keep track of the active member
*/

enum ValueType { INT, FLOAT, DOUBLE };

struct TaggedValue {
    ValueType type;
    union {
        int intValue;
        float floatValue;
        double doubleValue;
    } value;
};




/*
    Anonymous Unions: C++ allows anonymous unions within structures
*/
struct Color {
    union {
        struct { uint8_t r, g, b, a; };
        uint32_t value;
    };
};
