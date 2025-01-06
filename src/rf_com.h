#pragma once

//#include <RF24/RF24.h>
#include "include/RF24/RF24.h"
//#include "include/RF24/utility/includes.h"
#include <vector>
#include "Common.h"
#include "Session.h"
#include "include/packets/packets.h"


#define free_update_interval 1000
#define EMERGENCY_TIMEOUT_millis 3000


//#define GPS_DATA_SIZE 32
//#define ALL_PACKET_SIZE 24

//#define SIZE 8

//inline constexpr uint16_t EMERGENCY_TIMEOUT_millis = 3000;

const uint64_t pipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };




// CHANNEL/ PIPE NAMES
#define main_pipe 0  // Pr/At
#define ai_pipe 1   // Pr/At
#define servo_pipe 2   // Pr/At
#define imu_pipe 3   // Pr/At
#define misc_pipe 4   // Pt/Ar
#define log_pipe 5   // Pt/Ar

//#define n_pkt_start 33
//#define n_pkt_end 126

//#define bufferSize 5

//#define t_packet_size 32

//uint8_t active_pipe = 0;

#define RX_PKT_QUEUE_SIZE 10
#define TX_PKT_QUEUE_SIZE 10




/*
void encode_gps_packet(float latitude, float longitude, float altitude) {
    GPSPacket data;
    data.lat = fix.latitude() * 1e7;
    data.lon = fix.longitude() * 1e7;
    data.alt = fix.altitude_cm() / 100;
    data.sats = fix.satellites;
}
*/
/*
char decode_gps_packet(GPSPacket packet) {
    //char data[GPS_DATA_SIZE];
    //char header = packet.id;
}
*/


/////////inline void decode_gps_packet(std::vector<float> &vec, const GPSPacket &pkt) {
/////////    vec[0] = pkt.lat / 1e7;   // Convert latitude to float
/////////    vec[1] = pkt.lon / 1e7;   // Convert longitude to float
/////////    vec[2] = pkt.alt ;//* 100;         // Altitude in meters
/////////}
/////////
/////////inline void decode_gps_env_packet(std::vector<float> &vec, const GPSEnvPacket &pkt) {
/////////    vec[0] = pkt.speed / 1e7;;
/////////    vec[1] = pkt.sats;
/////////    vec[2] = pkt.timestamp;
/////////    vec[3] = pkt.course / 1e7;
/////////}



 // IMPLEMENT ASAP
/*
void encode_manual_packet(const char header, const char[SIZE] input, char* output) {
    output[0] = SOH;
    //output[1] = NULL_CHAR;
    //output[1] = header;
    output[1] = n_packets++; 
    output[2] = STX;

    output[3] = input[0];
    output[4] = input[1];
    output[5] = input[2];

    
    //output[3] = '0' + (input / 100) % 10;  // Hundreds place
    //output[4] = '0' + (input / 10) % 10;   // Tens place
    //output[5] = '0' + input % 10;          // Units place
    

    output[6] = ETX;
    output[7] = EOT;
}
*/


// returns packet header, first parameter is the array input chars, second parameter is the int output
//char decode_manual_packet(const char input[24], int &output[NUM_FEATS]) {
//    if (input[0] != SOH || input[2] != STX 
//                    || input[PAYLOAD_SIZE-5] != RECSEP
//                    || input[PAYLOAD_SIZE-9] != RECSEP
//                    || input[PAYLOAD_SIZE-13] != RECSEP
//                    || input[PAYLOAD_SIZE-17] != RECSEP
//                    || input[PAYLOAD_SIZE-1] != ETX 
//                    || input[PAYLOAD_SIZE] != EOT) {
//        return -1;  // Invalid format
//    }
//    for (int i = 0; i < NUM_FEATS; i+=1) {
//        output[i] = (atoi(&input[i*4 + 3]));
//    }
//    return input[1];
//}


/*
int send_packet(const char header,const char[SIZE] input) {
  char data[SIZE];

  radio.flush_tx();
  radio.stopListening();

  encode('p', input, data);
  
  if (!radio.write(data, SIZE)) {
    Serial.println("failed");
    return -1;
  }

  //radio.startListening();
  return 0;
}

void encode_manual_packet(const char header, const char[SIZE] input, char* output) {
    output[0] = SOH;
    //output[1] = NULL_CHAR;
    //output[1] = header;
    output[1] = n_packets++; 
    output[2] = STX;

    output[3] = input[0];
    output[4] = input[1];
    output[5] = input[2];

    
    //output[3] = '0' + (input / 100) % 10;  // Hundreds place
    //output[4] = '0' + (input / 10) % 10;   // Tens place
    //output[5] = '0' + input % 10;          // Units place
    

    output[6] = ETX;
    output[7] = EOT;
}
*/


/*
bool processServoPacket(const ServoPacket& packet, uint16_t servoValues[SERVO_COUNT]) {
    if (packet.header != 'S') {
        return false;  // Invalid packet
    }
    
    uint8_t calculatedChecksum = calculateChecksum((uint8_t*)&packet, sizeof(ServoPacket) - 1);
    if (calculatedChecksum != packet.checksum) {
        return false;  // Checksum mismatch
    }
    
    int parsed = sscanf(packet.payload, ":%4hu,%4hu,%4hu,%4hu,%4hu",
                        &servoValues[0], &servoValues[1], &servoValues[2], &servoValues[3], &servoValues[4]);
    
    return (parsed == SERVO_COUNT);
}
*/

// returns packet header, first parameter is the array input chars, second parameter is the int output
/*
char decode(const char input[8], int* output) {
    if (input[0] != SOH || input[2] != STX || input[6] != ETX || input[7] != EOT) {
        
        //Serial.print("\n Bad Data: ");
        //Serial.print(input[0]);
        //Serial.print(input[1]);
        //Serial.print(input[2]);
        //Serial.print(input[3]);
        //Serial.print(input[4]);
        //Serial.print(input[5]);
        //Serial.print(input[6]);
        //Serial.print(input[7]);
        
        return -1;  // Invalid format
    }

    *output = (atoi(&input[3]));
    //n_packets++;
    //Serial.print("\n Good Data: ");
    //Serial.println(*output);
    //Serial.print(input[1]);
    //return input[1] - '0';
    //return input[1] - 97;
    return input[1];
}
*/
