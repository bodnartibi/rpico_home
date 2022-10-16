/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "pico/stdlib.h"
#include "stdio.h"

#include "lamp/lamp_rf_cmds.h"

#define BUFSIZE 100
#define RX_PIN  17
#define LED_PIN 16
#define TX_PIN 18

void filter(const char *buf, char *out) {
  for (int i = 4; i < BUFSIZE; i++) {
    out[i-4] = (buf[i] + buf[i-1] + buf[i-2] + buf[i-3] + buf[i-4] + 2) / 5;
  }
  out[BUFSIZE-4] = '0';
}

void receive_loop() {
    int on = 0;
    gpio_init(RX_PIN);
    gpio_init(LED_PIN);
    gpio_set_dir(RX_PIN,  GPIO_IN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    char buf[BUFSIZE + 1];
    char buf_filtered[BUFSIZE + 1];
    buf[BUFSIZE] = '0';
    buf_filtered[BUFSIZE] = '0';
    while (true) {
        for (int i=0; i< BUFSIZE; i++) {
            buf[i] = (int)gpio_get(RX_PIN) + 48;
            sleep_us(50);
        }
        filter(buf, buf_filtered);
        puts_raw(buf);
        puts_raw(buf_filtered);
        puts_raw("\n\n");
        gpio_put(LED_PIN, on);
        on = !on;
        stdio_flush();
    }
}

void set_out_lamp(bool out) {
    gpio_put(TX_PIN, out);
}

void send_loop() {
    gpio_init(TX_PIN);
    gpio_init(LED_PIN);
    gpio_set_dir(TX_PIN, GPIO_OUT);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(TX_PIN, 0);

    int on = 0;

    while(true) {
        lamp_send(LAMP_CHANGE_LIGHT, set_out_lamp, sleep_us);
        gpio_put(TX_PIN, 0);
        gpio_put(LED_PIN, on);
        on = !on;

        sleep_ms(100);
    }
}

int main() {
    stdio_init_all();

    //receive_loop();
    send_loop();
}
