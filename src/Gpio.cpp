#include "HardwareConfig.hpp"
#include "Gpio.hpp"

void gpioInit()
{
    const gpio_config_t ledsConfig = {
        .pin_bit_mask = (1ULL << stopLedPin) | (1ULL << runLedPin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

    gpio_config(&ledsConfig);

    const gpio_config_t activatorConfig = {
        .pin_bit_mask = 1ULL << activatorPin,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

    gpio_config(&activatorConfig);
}

void enableActivator()
{
    gpio_set_level(activatorPin, activeLevel);
    gpio_set_level(stopLedPin, inactiveLevel);
    gpio_set_level(runLedPin, activeLevel);
}

void disableActivator()
{
    gpio_set_level(activatorPin, inactiveLevel);
    gpio_set_level(stopLedPin, activeLevel);
    gpio_set_level(runLedPin, inactiveLevel);
}