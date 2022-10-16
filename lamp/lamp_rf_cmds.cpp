#include <stdio.h>

#include "lamp_rf_cmds.h"

#define LAMP_TIME_Q_US 500

bool cmd_head_500us[] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0,
                1, 0, 0,
                1, 1, 0
};

size_t size_cmd_head_500us = sizeof(cmd_head_500us)/sizeof(cmd_head_500us[0]);

bool cmd_tail_500us[] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0
};

size_t size_cmd_tail_500us = sizeof(cmd_tail_500us)/sizeof(cmd_tail_500us[0]);

bool light_type_cmd_500us[] = {
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,

                1, 1, 0,
                1, 1, 0,
                1, 1, 0,

                1, 0, 0
                };

size_t size_light_type_cmd_500us = sizeof(light_type_cmd_500us)/sizeof(light_type_cmd_500us[0]);

bool on_cmd_500us[] = {
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,

                1, 0, 0,
                1, 0, 0,
                1, 1, 0,

                1, 0, 0
                };

size_t size_on_cmd_500us = sizeof(on_cmd_500us)/sizeof(on_cmd_500us[0]);

bool off_cmd_500us[] = {
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,

                1, 0, 0,
                1, 1, 0,
                1, 1, 0,

                1, 0, 0
                };

size_t size_off_cmd_500us = sizeof(off_cmd_500us)/sizeof(off_cmd_500us[0]);

void send_sequence(void (*set_out)  (bool out),
                   void (*sleep_us) (uint64_t us),
                   int time_us,
                   bool *cmd,
                   size_t n) {
    set_out(cmd[0]);
    sleep_us(time_us);

    for (int i=1; i<n; i++) {
        if (cmd[i-1] != cmd[i]) {
            set_out(cmd[i]);
        }
        sleep_us(time_us);
    }
}

void lamp_send(lamp_cmd_t cmd,
               void (*set_out) (bool out),
               void (*sleep_us) (uint64_t us)) {

    send_sequence(set_out, sleep_us, LAMP_TIME_Q_US, cmd_head_500us, size_cmd_head_500us);

    switch(cmd) {
        case LAMP_OFF:
            send_sequence(set_out, sleep_us, LAMP_TIME_Q_US, off_cmd_500us,  size_off_cmd_500us);
            break;

        case LAMP_ON:
            send_sequence(set_out, sleep_us, LAMP_TIME_Q_US, on_cmd_500us,  size_on_cmd_500us);
            break;

        case LAMP_CHANGE_LIGHT:
            send_sequence(set_out, sleep_us, LAMP_TIME_Q_US, light_type_cmd_500us,  size_light_type_cmd_500us);
            break;
    }

    send_sequence(set_out, sleep_us, LAMP_TIME_Q_US, cmd_tail_500us, size_cmd_tail_500us);
    set_out(false);
}
