#include "HardwareConfig.hpp"
#include "Gpio.hpp"
#include "driver/gptimer.h"

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gptimer.html#creating-and-starting-a-timer

gptimer_handle_t periodTimer;
gptimer_handle_t fanRunTimer;

static bool periodTimerCallback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    // start fan
    enableActivator();
    gptimer_set_raw_count(fanRunTimer, 0);
    ESP_ERROR_CHECK(gptimer_start(fanRunTimer));

    return false;
}

static bool fanRunTimerCallback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    // stop fan
    disableActivator();
    gptimer_stop(fanRunTimer);
    
    return false;
}

const gptimer_config_t timerConfig = {
    .clk_src = GPTIMER_CLK_SRC_DEFAULT, // Select the default clock source
    .direction = GPTIMER_COUNT_UP,
    .resolution_hz = 1 * 1000 * 1000,
    .intr_priority = 0,
    .flags = {
        .intr_shared = false,
        .allow_pd = false,
    },
};

gptimer_alarm_config_t periodTimerAlarmConfig = {
    .alarm_count = cyclePeriodMs * 1000ULL,
    .reload_count = 0,
    .flags = {
        .auto_reload_on_alarm = true,
    }
};

gptimer_alarm_config_t fanRunTimerAlarmConfig = {
    .alarm_count =  fanWorkPeriodMs * 1000ULL,
    .reload_count = 0,
    .flags = {
        .auto_reload_on_alarm = false,
    }
};

gptimer_event_callbacks_t periodTimerCallbacks = {
    .on_alarm = periodTimerCallback,
};
gptimer_event_callbacks_t fanRunTimerCallbacks = {
    .on_alarm = fanRunTimerCallback,
};

void fanTimerInit()
{
    ESP_ERROR_CHECK(gptimer_new_timer(&timerConfig, &periodTimer));
    ESP_ERROR_CHECK(gptimer_set_alarm_action(periodTimer, &periodTimerAlarmConfig));
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(periodTimer, &periodTimerCallbacks, NULL));
    ESP_ERROR_CHECK(gptimer_enable(periodTimer));

    ESP_ERROR_CHECK(gptimer_new_timer(&timerConfig, &fanRunTimer));
    ESP_ERROR_CHECK(gptimer_set_alarm_action(fanRunTimer, &fanRunTimerAlarmConfig));
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(fanRunTimer, &fanRunTimerCallbacks, NULL));
    ESP_ERROR_CHECK(gptimer_enable(fanRunTimer));

    ESP_ERROR_CHECK(gptimer_start(periodTimer));
}