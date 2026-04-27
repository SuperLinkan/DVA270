#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_rtc.h>
#include <stdlib.h>
#include <stdio.h>

#define LED1 28
#define LED2 29
#define LED3 30
#define LED4 31

#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9

#define LED_OFF 1
#define LED_ON  0

#define PIN_TXD 20
#define PIN_RXD 22



const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
int initiera(void)
{
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_err_t errr = nrfx_rtc_init(&rtc_instance, &config, NULL);
    nrfx_rtc_enable(&rtc_instance);
    
}

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//Skapar en funktion för att skicka data:
void uarte_write(uint8_t* data, uint8_t length)
{
    nrfx_uarte_tx(&instance, data, length, 0);
}



int toggle_light(void)
{
    nrfx_systick_init();

    // Konfigurera LED som output
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);

    // Konfigurera knappar som input med pull-up
    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    // Släck alla LED från början
    nrf_gpio_pin_write(LED1, LED_OFF);
    nrf_gpio_pin_write(LED2, LED_OFF);
    nrf_gpio_pin_write(LED3, LED_OFF);
    nrf_gpio_pin_write(LED4, LED_OFF);

    // Variabler för att spara knappstatus (för edge-detection)
    bool last_btn1 = 1;
    bool last_btn2 = 1;
    bool last_btn3 = 1;
    bool last_btn4 = 1;


    while (1)
    {
        bool btn1 = nrf_gpio_pin_read(BUTTON1);
        bool btn2 = nrf_gpio_pin_read(BUTTON2);
        bool btn3 = nrf_gpio_pin_read(BUTTON3);
        bool btn4 = nrf_gpio_pin_read(BUTTON4);

        // BUTTON1 → LED1
        if (last_btn1 == 1 && btn1 == 0) {
            nrf_gpio_pin_toggle(LED1);
            nrfx_systick_delay_ms(50); // debounce
        }

        // BUTTON2 → LED2
        if (last_btn2 == 1 && btn2 == 0) {
            nrf_gpio_pin_toggle(LED2);
            nrfx_systick_delay_ms(50);
        }

        // BUTTON3 → LED3
        if (last_btn3 == 1 && btn3 == 0) {
            nrf_gpio_pin_toggle(LED3);
            nrfx_systick_delay_ms(50);
        }

        // BUTTON4 → LED4
        if (last_btn4 == 1 && btn4 == 0) {
            nrf_gpio_pin_toggle(LED4);
            nrfx_systick_delay_ms(50);
        }

        // Uppdatera senaste knappstatus
        last_btn1 = btn1;
        last_btn2 = btn2;
        last_btn3 = btn3;
        last_btn4 = btn4;
    }
}


int Random_generator(void)
{
    

    initiera();
    nrfx_systick_init();
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0){

        //Hantera det, om ni känner att ni behöver det.
    }

    

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);

    char ran[20];   
    int ran_num;
    int loop = 1;
    while(loop)
    {
        nrfx_systick_delay_ms(50);

        if (nrf_gpio_pin_read(23) == 0)
        {
            loop = 0;
        }
        while(!nrf_gpio_pin_read(23))
        {
            nrfx_systick_delay_ms(50);
        }
    } 
    srand(nrfx_rtc_counter_get(&rtc_instance));
    ran_num = rand() % 1000 + 1;
    sprintf(ran, "\r\n%d", ran_num);
    uarte_write(ran, strlen(ran));
    nrfx_systick_delay_ms(1000);
}

