#include "includes/tasks.h"

static float unit_conversion(int input_high, int input_low, int output_high, int output_low, uint16_t input_value);

uint8_t can_pinNums[] = {8, 9};
TaskHandle_t can_receive_handle;
TaskHandle_t freq_analysis_handle;
TaskHandle_t dac_out_handle;  


volatile uint16_t data_out[SAMPLE_SIZE];
volatile int current = 0;

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

    while (1) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // CAN Receive------------------------------------------
        Received_Data *data = CAN_Receive(CAN_NUM, MAILBOX_NUM);
        if (data != NULL) {

            if (current > 508) { current = 0; }
            data_out[current++] = ((uint16_t) data->byte0) << 8 | (uint16_t) data->byte1;
            data_out[current++] = ((uint16_t) data->byte2) << 8 | (uint16_t) data->byte3;
            data_out[current++] = ((uint16_t) data->byte4) << 8 | (uint16_t) data->byte5;
            data_out[current++] = ((uint16_t) data->byte6) << 8 | (uint16_t) data->byte7;

            free(data);
        }

        if (current == 512) {
            xTaskNotifyGive(dac_out_handle);
        }
    }
}


void vDACOutTask(void *pvParameters) {
    
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // DAC Out-----------------------------------------------
        for (int i = 0; i < SAMPLE_SIZE; i++) {
            uint16_t result = DAC_Out(DAC_NUM, data_out[i]);
            int x = 1 + 1; // Temporary BS
            // printf("%d\n", result);
        }
    }
}    



void vFrequencyAnalysisTask(void *pvParameters) {


    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        float samples[SAMPLE_SIZE];

        for (int i = 0; i < SAMPLE_SIZE; i++) {
            samples[i] = unit_conversion(BYT_HIGH, BYTE_LOW, VOLT_HIGH, VOLT_LOW, data_out[i]);
        }
        // samples per sec = f_clk / 84 cycles per adc conversion
        frequencyBin_data* frequencies = fourier_transform(samples, (int)190476.1905);
    }
    
}


void start_tasks() {

    // Test
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        data_out[i] = 500 + (i * 7);
    }

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
    // xTaskCreate(vFrequencyAnalysisTask, "Frequencey Analysis Task", 128, NULL, 3, &freq_analysis_handle);
    xTaskCreate(vDACOutTask, "DAC Out Task", 128, NULL, 2, &dac_out_handle);

    vTaskStartScheduler();
}


static float unit_conversion(int input_high, int input_low, int output_high, int output_low, uint16_t input_value) {

    float slope = (output_high - output_low) / (input_high - input_low);
    float intercept = slope * input_low - output_low;

    return (slope * (float) input_value) + intercept;
}







