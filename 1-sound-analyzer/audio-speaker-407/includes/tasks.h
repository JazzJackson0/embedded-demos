#ifndef TASKS_H
#define TASKS_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include "../../../Drivers/DAC.h"
#include "../../../Drivers/CAN.h"
#include "../../../Drivers/GPIO.h"
#include "../../../Drivers/ExternalInterrupt.h"
#include "../../../Drivers/isr_handlers.h"
#include "FourierTransform.h"

#define CAN_IDENTIFIER 0x47
#define IDENTIFIER 0x49
#define CLOCK_FREQ 16000000
#define DAC_NUM 1
#define CAN_NUM 1
#define MAILBOX_NUM 0
#define CAN_GPIO_PORT 'B'
#define VOLT_LOW 0.0
#define VOLT_HIGH 3.3
#define BYTE_LOW 0
#define BYT_HIGH 4095
#define SAMPLE_SIZE 512
void start_tasks();




#endif