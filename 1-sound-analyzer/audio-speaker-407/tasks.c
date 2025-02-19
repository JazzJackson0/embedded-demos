#include "includes/tasks.h"

uint8_t can_pinNums[] = {8, 9};
TaskHandle_t can_receive_handle;
TaskHandle_t freq_analysis_handle;
TaskHandle_t dac_out_handle;  


volatile int16_t data_out;

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("You have a stack overflow! Congratulations!!\n");
}


void CAN1_RX0_IRQHandler(void) {

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    uint32_t *fifo0_reg = (volatile uint32_t *) 0x4000640C;
    uint32_t full_status = (*fifo0_reg & 0x8);
    uint32_t overrun_status = (*fifo0_reg & 0x10);

    if (full_status != 0x00000000) {
        // Clear 
        *fifo0_reg &= ~(0x8);
    }

    if (overrun_status != 0x00000000) {
        // Clear 
        *fifo0_reg &= ~(0x10);
    }

    vTaskNotifyGiveFromISR(can_receive_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void vCANReceiveTask(void *pvParameters) {

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // CAN Receive------------------------------------------
    Received_Data *data = CAN_Receive(CAN_NUM, MAILBOX_NUM, 2);
    if (data != NULL) {
        data_out = ((int16_t) data->byte0) << 8 | (int16_t) data->byte1;
        free(data);
    }
}


void vFrequencyAnalysisTask(void *pvParameters) {

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
}


void vDACOutTask(void *pvParameters) {
    
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    // DAC Out-----------------------------------------------
    DAC_Out(DAC_NUM, data_out);
    // Decibel_Out();
}


void start_tasks() {

    // Initialize DAC------------------------------------
    DAC_Init(DAC_NUM);

    // Initialize CAN------------------------------------
    Filter filter;
    filter.filterNum = 0;
    filter.filterSize = _16BIT_CAN;
    filter.filterType = LIST_MODE;
    filter.filterVal = IDENTIFIER;
    filter.mailboxFIFONum = 0;
    CAN_InterruptManager interrupt_manager;
    interrupt_manager.FIFO0MessagePendingInterrupt_ON = true;
    interrupt_manager.FIFO0FullInterrupt_ON = true;
    interrupt_manager.FIFO0OverrunInterrupt_ON = true;
    CAN_SetBitTime(CAN_NUM, 1, 1, 13, 2);
    CAN_SetAcceptanceFilter(CAN_NUM, &filter);
    CAN_SetRXMailbox(CAN_NUM, MAILBOX_NUM, CAN_IDENTIFIER, 2);
    CAN_Init_and_Start(CAN_NUM, CAN_GPIO_PORT, can_pinNums);
    CAN_EnableInterrupts(CAN_NUM, interrupt_manager);

    // Initialize Tasks----------------------------------
    xTaskCreate(vCANReceiveTask, "CAN Receive Task", 128, NULL, 4, &can_receive_handle);
    xTaskCreate(vFrequencyAnalysisTask, "Frequencey Analysis Task", 128, NULL, 3, &freq_analysis_handle);
    xTaskCreate(vDACOutTask, "DAC Out Task", 128, NULL, 2, &dac_out_handle);

    vTaskStartScheduler();
}








