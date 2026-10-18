#ifndef HARDWARECONFIG_HPP
#define HARDWARECONFIG_HPP

#include "driver/gpio.h"

constexpr gpio_num_t activatorPin = GPIO_NUM_7;
constexpr gpio_num_t stopLedPin = GPIO_NUM_8;
constexpr gpio_num_t runLedPin = GPIO_NUM_9;

constexpr int activeLevel = 1;
constexpr int inactiveLevel = 0;

// constexpr uint32_t cyclePeriodMs = 1000 * 60 * 60 * 1; // 1 hour
constexpr uint32_t cyclePeriodMs = 1000 * 10 * 1 * 1; // 10 sec for debug
// constexpr uint32_t fanWorkPeriodMs = 1000 * 60 * 15 * 1; // 15 minutes
constexpr uint32_t fanWorkPeriodMs = 1000 * 3 * 1 * 1; // 3 sec for debug

#endif