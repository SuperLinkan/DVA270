#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <stdio.h>
#include <nrfx_systick.h>
#include <nrfx_rtc.h>
#include <nrf_gpio.h>
#include "Declarationer_&_initieringar.h"



//skapar en buffer att ta emot tecken vi läser över UARTE
char uarte_buffer;

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);


void uarte_init(void)
{
    //Vi kör med default settings och anger våra TX- och RX-pinnar:
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
   
    //Initierar UARTE:
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
}

void systick_init(void)
{
    nrfx_systick_init();
}

void button_LED_init(void)
{
    nrf_gpio_pin_write(LED1,LED_OFF);
    nrf_gpio_pin_write(LED2,LED_OFF);
    nrf_gpio_pin_write(LED3,LED_OFF);
    nrf_gpio_pin_write(LED4,LED_OFF);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);
}

void RTC_init(void)
{
    nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_err_t rtc_err = nrfx_rtc_init(&rtc_instance, &rtc_config, NULL);
    if (rtc_err != NRFX_SUCCESS) {
        // handle error
    }
    nrfx_rtc_enable(&rtc_instance);
}

void send_string(char string[])
{
    nrfx_uarte_tx(&instance, string, strlen(string), 0);
}


void read_string(char string[])
{

    int counter = 0;

    while(counter < 10)
    {
       
        //Vi väntar på att läsa ett tecken över UARTE
        nrfx_uarte_rx (&instance, &uarte_buffer, sizeof(uarte_buffer));

        if (uarte_buffer == '\r')
        {

            string[counter] = '\0';

            counter = 10;

        }
        else
        {
        
            string[counter] = uarte_buffer;

            counter += 1;

            if (counter == 10)
            {
                string[counter] = '\0';
            }

        }
    }

    nrfx_uarte_tx(&instance, string, strlen(string), 0);
}

int read_int(void)
{
    char string[10];

    read_string(string);

    int num = atoi(string);

    return num;

}

void send_int(int num)
{
    char string[10];

    sprintf(string, "%d", num);

    nrfx_uarte_tx(&instance, string, strlen(string), 0);

}


void clear()
{
    uint8_t clear_screen[] = "\033c";
    
    send_string(clear_screen);
}

void new_line()
{
    uint8_t new_line[] = "\n\r";

    send_string(new_line);
}