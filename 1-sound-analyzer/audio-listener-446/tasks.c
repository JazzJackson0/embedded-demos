#include "includes/tasks.h"

uint8_t can_pinNums[] = {8, 9};
TaskHandle_t adc_read_handle;
TaskHandle_t adc_off_handle; 
TaskHandle_t can_transmit_handle;

volatile uint16_t conversion_data[NUM_OF_CONVERSIONS];

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("You have a stack overflow! WOW!! Congratulations!!!!\n");
}


void EXTI15_10_IRQHandler(void) {

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    uint32_t *gpio_port_a = (volatile uint32_t*) 0x40020010;
    uint32_t *exti_pending_reg = (volatile uint32_t*) 0x40013C14;

    // Clear Interrupt
    *exti_pending_reg |= (1 << 11);

    // If Pin Low: Falling Edge Trigger (Read ADC)
    // if ((*gpio_port_a & (1 << 11)) == 0x0) {
    // }

    // If Pin High: Rising Edge Trigger 
    // if ((*gpio_port_a & (1 << 11)) != 0x0) {
    // }  

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void DMA2_Stream0_IRQHandler(void) {
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t *LowInterruptStatusReg = (volatile uint32_t*) 0x40026400;
    uint32_t *LowInterruptFlagClearReg = (volatile uint32_t*) 0x40026408;

    // If Transfer is Complete
    if ((*LowInterruptStatusReg & (1 << 5)) != 0x0) {
        
        // Clear Half-Transfer AND Transfer Complete Interrupts
        *LowInterruptFlagClearReg = (3 << 4);
        vTaskNotifyGiveFromISR(adc_off_handle, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
    

void vADCOffTask(void *pvParameters) {
    
    while (1) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        ADC_StopConversion(ADC_NUM, ADC_REGULAR_CH);
        xTaskNotifyGive(can_transmit_handle); 
    }
    
}


void vCANTransmitTask(void *pvParameters) {

    while (1) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    
        // Test
        // uint8_t temp_data[] = {3, 11};
        // int16_t result = CAN_Transmit(CAN_NUM, MAILBOX_NUM, temp_data);

        uint8_t to_send[8];
        for (int i = 0; i < NUM_OF_CONVERSIONS; i += 4) {
            memcpy(to_send, (conversion_data + i), 4 * sizeof(uint16_t));
            int16_t result = CAN_Transmit(CAN_NUM, MAILBOX_NUM, to_send);
        }
    }
    
}


void start_tasks() {

    enable_faults(); 

    // Test (Ensuring DMA is actually altering this data)
    for (int i = 0; i < NUM_OF_CONVERSIONS; i++) {
        conversion_data[i] = 1;
    }
        
    // Setup Interrupt on Button Pin----------------------
    EXTIInit(EXTI_NUM, EXTI_PORT, HARDWARE_INTERRUPT, RISING_FALLING, 4);

    // Setup DMA for ADC Conversion Transfer-------------
    DMAConfig cfg;
    cfg.src_dest = PERIPHERAL_TO_MEM;
    cfg.src_address = (uint32_t) 0x4001204C; // ADC1_DR
    cfg.src_datasize = BIT_16;
    cfg.dest_address = (uint32_t) conversion_data;
    cfg.dest_datasize = BIT_16;
    cfg.numOfBlocks = NUM_OF_CONVERSIONS;
    cfg.channel = DMA_CH_0;
    cfg.priorityLevel = HIGH_P;
    cfg.mode = CIRCULAR;
    cfg.peripheral_flowcontrol = false;
    DMA_Init(DMA_NUM, DMA_STREAM, cfg);
    NVICInterruptInit(56, 5, HARDWARE);

    // Initialize ADC------------------------------------
    ADC_Params params;
    params.channelType = ADC_REGULAR_CH;
	params.channelNum = ADC_CH_14; // Maps to GPIO PC4
	params.conversionOrderNum = 1;
	params.cycles = ADC_SAMPLE_84_CYCLES;
	params.resolution = ADC_12BIT_RES;
	params.singleContinuous = ADC_CONTINUOUS_CONV;
	params.numOfConversions = ADC_1_CONVERSION;
    ADC_Init(ADC_NUM, params, ADC_GPIO_PORT, ADC_GPIO_PIN);
    ADC_SetExternalTrigger(ADC_NUM, params.channelType, FALLING_EDGE, EXTI_LINE11);
    ADC_UseDMA(ADC_NUM);

    // Initialize CAN------------------------------------
    CAN_SetBitTime(CAN_NUM, 1, 1, 13, 2);
    CAN_SetTXMailbox(CAN_NUM, MAILBOX_NUM, CAN_IDENTIFIER, 2);
    CAN_Init_and_Start(CAN_NUM, CAN_GPIO_PORT, can_pinNums);

    // Initialize Tasks----------------------------------
    xTaskCreate(vADCOffTask, "ADC Off Task", 256, NULL, 4, &adc_off_handle);
    xTaskCreate(vCANTransmitTask, "CAN Transmit Task", 256, NULL, 3, &can_transmit_handle);

    vTaskStartScheduler();
}








