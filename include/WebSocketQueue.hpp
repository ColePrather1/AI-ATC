#ifndef WEBSOCKET_QUEUE_H
#define WEBSOCKET_QUEUE_H
#pragma once
#include "ThreadSafeQueue.h"
#include "WebSocketPacket.hpp"

inline ThreadSafeQueue<WebSocketPacket> websocket_queue{10};      // Max 5 seconds worth of data

#endif // WEBSOCKET_QUEUE_H