#ifndef TASKS_H
#define TASKS_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include "../../../Drivers/ADC.h"
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


void start_tasks();




#endif