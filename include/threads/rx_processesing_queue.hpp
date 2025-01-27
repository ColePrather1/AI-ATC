#ifndef RX_PROCESSING_QUEUE_H
#define RX_PROCESSING_QUEUE_H
#pragma once
#include "ThreadSafeQueue.h"
#include <vector>

inline ThreadSafeQueue<std::vector<std::byte>> rx_buffer_queue(50);

#endif // RX_PROCESSING_QUEUE_H