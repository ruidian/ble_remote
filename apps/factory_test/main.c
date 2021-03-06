/**
 * @brief Blinky Sample Application main file  SDk的官方闪灯例程
 *
 * This file contains the source code for a sample server application using the LED Button service.
 */

#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "boards.h"
#include "app_timer.h"
#include "app_button.h"
#include "ble_lbs.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "board_remote001.h"
//#include "timer.h"

#include "battery_handler.h"
#include "pl_utils.h"
#include "pl_timer.h"
#include "cli.h"

#include "storage_handler.h"


extern void cmd_ble_pong(void);

static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}


static void clock_init(void)
{
    ret_code_t ret;

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    nrf_drv_clock_lfclk_request(NULL);
    nrf_drv_clock_hfclk_request(NULL);
    while (!nrf_drv_clock_hfclk_is_running())
    {
        // spin lock
    }
}

static void button_pin_init(void)
{
    nrf_drv_gpiote_init();

    nrf_gpio_cfg_input(GUARD_HOME_BUTTON, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(ALARM_SET_BUTTON, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(GUARD_SET_BUTTON, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(GUARD_CANCEL_BUTTON, NRF_GPIO_PIN_NOPULL);

    nrf_gpio_cfg_output(STATUS_LED);

}


/**@brief Function for application main entry.
 */
int main(void)
{

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    log_init();

    clock_init();
    pl_time_init();
    pl_pool_init();
    button_pin_init();

    fstorage_init();

    cli_init();
    cli_greeting();
    cli_start();
    cmd_cache();


    for (;;)
    {
        cli_process();
        if( 0 == nrf_gpio_pin_read(GUARD_CANCEL_BUTTON) )
        {
            NVIC_SystemReset();
            //nrf_gpio_pin_write(STATUS_LED , 1); 
        }
        else
        {
            //nrf_gpio_pin_write(STATUS_LED ,0); 
        }
    }
}


/**
 * @}
 */
