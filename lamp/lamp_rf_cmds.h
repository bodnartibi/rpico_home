#ifndef LAMP_RF_CMDS_H
#define LAMP_RF_CMDS_H

typedef enum {
    LAMP_OFF = 0,
    LAMP_ON,
    LAMP_CHANGE_LIGHT
} lamp_cmd_t;

void lamp_send(lamp_cmd_t cmd,
               void (*set_out) (bool out),
               void (*sleep_us) (uint64_t us));

#endif
