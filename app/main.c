#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motor_driver.h"
#include "xtimer.h"
#include "periph/uart.h"
#include "event.h"
#include "isrpipe.h"

#define MOTOR_0_ID 0
#define MOTOR_1_ID 1

static isrpipe_t isrpipe;

int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// uart interrupt callback
static void uart_rx_cb(void *arg, uint8_t data)
{
    (void)arg; // avoid unused var warning
    if (data == '\r')
        return; // ignore CR

    isrpipe_write_one(&isrpipe, data);
}

int main(void)
{
    char buf[256]; // isr pipe buffer size

    printf("isrpipe_init\n");
    isrpipe_init(&isrpipe, (uint8_t *)buf, sizeof(buf));

    printf("uart_init\n");
    uart_init(UART_DEV(2), 9600, uart_rx_cb, NULL);

    printf("motor_driver_init\n");
    int ret = motor_driver_init(MOTOR_DRIVER_DEV(0));
    if (ret)
    {
        printf("motor_driver_init failed with error code %d\n", ret);
        return ret;
    }

    while (1)
    {
        int res = 0;
        char bff[64];
        char c;
        int i = 0;
        while ((res = isrpipe_read(&isrpipe, (uint8_t *)&c, 1)) == 1 && c != '\n')
        {
            bff[i++] = c;
        }
        bff[i] = '\0';
        printf("bff %s\n", bff);

        //char received[] = "x1:50,y1:-10,x2:100,y2:-100";
        char *tok;

        tok = strtok(bff, ",");
        char *x1str = tok;

        tok = strtok(NULL, ",");
        char *y1str = tok;

        tok = strtok(NULL, ",");
        char *x2str = tok;

        tok = strtok(NULL, ",");
        char *y2str = tok;

        int x1, y1, x2, y2;
        tok = strtok(x1str, ":");
        tok = strtok(NULL, ":");
        x1 = atoi(tok);
        //printf("x1 %d\n", x1);

        tok = strtok(y1str, ":");
        tok = strtok(NULL, ":");
        y1 = atoi(tok);
        //printf("y1 %d\n", y1);

        tok = strtok(x2str, ":");
        tok = strtok(NULL, ":");
        x2 = atoi(tok);
        //printf("x2 %d\n", x2);

        tok = strtok(y2str, ":");
        tok = strtok(NULL, ":");
        y2 = atoi(tok);
        //printf("y2 %d\n", y2);

        // if timeout -> stop!

        int x, y;
        x = map(x1, -100, 100, -255, 255);
        y = map(y1, -100, 100, -255, 255);

        printf("x1: %d %d, y1: %d %d, x2: %d, y2: %d\n", x1, x, y1, y, x2, y2);
        motor_set(MOTOR_DRIVER_DEV(0), MOTOR_0_ID, y - x);
        motor_set(MOTOR_DRIVER_DEV(0), MOTOR_1_ID, y + x);
    }

    return 0;
}
