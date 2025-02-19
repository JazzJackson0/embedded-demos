#ifndef TASKS_H
#define TASKS_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>
#include "../../../Drivers/ADC.h"
#include "../../../Drivers/CAN.h"
#include "../../../Drivers/GPIO.h"
#include "../../../Drivers/ExternalInterrupt.h"
#include "../../../Drivers/faults.h"
#include "../../../Drivers/DMA.h"

#define CAN_IDENTIFIER 0x49
#define CLOCK_FREQ 16000000
#define ADC_NUM 1
#define CAN_NUM 1
#define DMA_NUM 2
#define DMA_STREAM 0
#define MAILBOX_NUM 0
#define ADC_GPIO_PORT 'C'
#define ADC_GPIO_PIN 4
#define CAN_GPIO_PORT 'B'
#define EXTI_NUM 11
#define EXTI_PORT 'A'
#define EVENT_BIT0 (1 << 0)

void start_tasks();




#endif