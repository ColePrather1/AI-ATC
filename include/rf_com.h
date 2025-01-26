#ifndef RF_COM_H
#define RF_COM_H
#pragma once

#include "RF24/RF24.h"
#include "packets/packets.h"

#define MAX_PACKET_SIZE 32
#define EMERGENCY_TIMEOUT_millis 3000

const uint64_t pipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };


// CHANNEL/ PIPE NAMES
#define main_pipe 0  // Pr/At
#define ai_pipe 1   // Pr/At
#define servo_pipe 2   // Pr/At
#define imu_pipe 3   // Pr/At
#define misc_pipe 4   // Pt/Ar
#define log_pipe 5   // Pt/Ar

#define RX_PKT_QUEUE_SIZE 50
#define TX_PKT_QUEUE_SIZE 20

#endif // RF_COM_H