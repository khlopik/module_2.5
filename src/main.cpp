#include "Gpio.hpp"
#include "FanTimer.hpp"

extern "C" void app_main()
{
    gpioInit();
    disableActivator();
    fanTimerInit();
}