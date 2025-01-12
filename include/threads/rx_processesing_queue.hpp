#ifndef RX_PROCESSING_QUEUE_H
#define RX_PROCESSING_QUEUE_H
#pragma once

//#include <cstdint>
//#include <iostream>

#include "ThreadSafeQueue.h"
//#include <span>
//#include <cstddef>
//#include <array>
//#include <memory>
//#include <stdspan>

#include <vector>

inline ThreadSafeQueue<std::vector<std::byte>> rx_buffer_queue(50);


//ThreadSafeQueue<span<std::byte>> rx_buffer_queue;

//ThreadSafeQueue<span<std::byte>> rx_buffer_queue;

#endif // RX_PROCESSING_QUEUE_H