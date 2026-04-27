#ifndef DEC_AND_INIT_H
#define DEC_AND_INIT_H

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


//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22

#define LED1 28
#define LED2 29
#define LED3 30
#define LED4 31
#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9
#define LED_OFF 1
#define LED_ON 0

void uarte_init(void);
void systick_init(void);
void button_LED_init(void);
void RTC_init(void);

void send_string(char string[]);
void read_string(char string[]);
int read_int(void);
void send_int(int num);
void new_line();
void clear();

#endif