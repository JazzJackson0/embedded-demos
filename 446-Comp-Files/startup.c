#include <stdint.h>

#define SRAM_START 0x20000000U 
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data; 

extern uint32_t _sbss;
extern uint32_t _ebss;
//^ Newlib puts sections between _etext & _sdata. So, _etext can't be used as the source address,
//a load address is required.

void __libc_init_array(void);

// weak: Linker will automatically replace function with any stringer definitions found 
int main(void);
void Reset_Handler(void);
void NMI_Handler			(void)__attribute__((weak, alias ("Default_Handler")));
void HardFault_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void MemManage_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void BusFault_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void UsageFault_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void SVCall_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void Debug_Monitor_Handler	(void)__attribute__((weak, alias ("Default_Handler")));
void PendSV_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void SysTick_Handler		(void)__attribute__((weak, alias ("Default_Handler")));
void WWDG_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void PVD_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TAMP_STAMP_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void RTC_WKUP_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void RCC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI2_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream0_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream1_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream2_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream3_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream4_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream5_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream6_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void ADC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN1_TX_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN1_RX0_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN1_RX1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN1_SCE_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler			(void)__attribute__((weak, alias ("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM2_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM3_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM4_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SPI1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SPI2_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void USART1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void USART2_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void USART3_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_FS_WKUP_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void TIM8_CC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream7_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void FSMC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SDIO_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM5_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SPI3_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void UART4_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void UART5_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void TIM7_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream0_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream1_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream2_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream3_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream4_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void CAN2_TX_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN2_RX0_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN2_RX1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void CAN2_SCE_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_FS_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream5_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream6_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream7_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void USART6_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C3_EV_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void I2C3_ER_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_HS_WKUP_IRQHandler	(void)__attribute__((weak, alias ("Default_Handler")));
void OTG_HS_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void DCMI_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void FPU_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SPI4_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SAI1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SAI2_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void QuadSPI_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void HDMICEC_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void SPIDIFRx_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void FMPI2C1_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));
void FMPI2Cerror_IRQHandler		(void)__attribute__((weak, alias ("Default_Handler")));


uint32_t vectors[] __attribute__((section (".isr_vector"))) = {

	STACK_START,
	(uint32_t) Reset_Handler, // 0x0000 0004
	(uint32_t) NMI_Handler, // 0x0000 0008
	(uint32_t) HardFault_Handler, // 0x0000 000C
	(uint32_t) MemManage_Handler, // 0x0000 0010
	(uint32_t) BusFault_Handler, // 0x0000 0014
	(uint32_t) UsageFault_Handler, // 0x0000 0018
	0, // 0x0000 001C - 0x0000 002B
	0,
	0,
	0,
	(uint32_t) SVCall_Handler, // 0x0000 002C
	(uint32_t) Debug_Monitor_Handler, // 0x0000 0030
	0, // 0x0000 0034
	(uint32_t) PendSV_Handler, // 0x0000 0038
	(uint32_t) SysTick_Handler, // 0x0000 003C
	(uint32_t) WWDG_IRQHandler, // 0x0000 0040
	(uint32_t) PVD_IRQHandler, // 0x0000 0044
	(uint32_t) TAMP_STAMP_IRQHandler, // 0x0000 0048
	(uint32_t) RTC_WKUP_IRQHandler, // 0x0000 004C
	0, // 0x0000 0050 [Setting Flash Space as Reserved]
	(uint32_t) RCC_IRQHandler, // 0x0000 0054
	(uint32_t) EXTI0_IRQHandler, // 0x0000 0058
	(uint32_t) EXTI1_IRQHandler, // 0x0000 005C
	(uint32_t) EXTI2_IRQHandler, // 0x0000 0060
	(uint32_t) EXTI3_IRQHandler, // 0x0000 0064
	(uint32_t) EXTI4_IRQHandler, // 0x0000 0068
	(uint32_t) DMA1_Stream0_IRQHandler, // 0x0000 006C
	(uint32_t) DMA1_Stream1_IRQHandler, // 0x0000 0070
	(uint32_t) DMA1_Stream2_IRQHandler, // 0x0000 0074
	(uint32_t) DMA1_Stream3_IRQHandler, // 0x0000 0078
	(uint32_t) DMA1_Stream4_IRQHandler, // 0x0000 007C
	(uint32_t) DMA1_Stream5_IRQHandler, // 0x0000 0080
	(uint32_t) DMA1_Stream6_IRQHandler, // 0x0000 0084
	(uint32_t) ADC_IRQHandler, // 0x0000 0088
	(uint32_t) CAN1_TX_IRQHandler, // 0x0000 008C
	(uint32_t) CAN1_RX0_IRQHandler, // 0x0000 0090
	(uint32_t) CAN1_RX1_IRQHandler, // 0x0000 0094
	(uint32_t) CAN1_SCE_IRQHandler, // 0x0000 0098
	(uint32_t) EXTI9_5_IRQHandler, // 0x0000 009C
	(uint32_t) TIM1_BRK_TIM9_IRQHandler, // 0x0000 00A0
	(uint32_t) TIM1_UP_TIM10_IRQHandler, // 0x0000 00A4
	(uint32_t) TIM1_TRG_COM_TIM11_IRQHandler, // 0x0000 00A8
	(uint32_t) TIM1_CC_IRQHandler, // 0x0000 00AC
	(uint32_t) TIM2_IRQHandler, // 0x0000 00B0
	(uint32_t) TIM3_IRQHandler, // 0x0000 00B4
	(uint32_t) TIM4_IRQHandler, // 0x0000 00B8
	(uint32_t) I2C1_EV_IRQHandler, // 0x0000 00BC
	(uint32_t) I2C1_ER_IRQHandler, // 0x0000 00C0
	(uint32_t) I2C1_EV_IRQHandler, // 0x0000 00C4
	(uint32_t) I2C1_ER_IRQHandler, // 0x0000 00C8
	(uint32_t) SPI1_IRQHandler, // 0x0000 00CC
	(uint32_t) SPI2_IRQHandler, // 0x0000 00D0
	(uint32_t) USART1_IRQHandler, // 0x0000 00D4
	(uint32_t) USART2_IRQHandler, // 0x0000 00D8
	(uint32_t) USART3_IRQHandler, // 0x0000 00DC
	(uint32_t) EXTI15_10_IRQHandler, // 0x0000 00E0
	(uint32_t) RTC_Alarm_IRQHandler, // 0x0000 00E4
	(uint32_t) OTG_FS_WKUP_IRQHandler, // 0x0000 00E8
	(uint32_t) TIM8_BRK_TIM12_IRQHandler, // 0x0000 00EC
	(uint32_t) TIM8_UP_TIM13_IRQHandler, // 0x0000 00F0
	(uint32_t) TIM8_TRG_COM_TIM14_IRQHandler, // 0x0000 00F4
	(uint32_t) TIM8_CC_IRQHandler, // 0x0000 00F8
	(uint32_t) DMA1_Stream7_IRQHandler, // 0x0000 00FC
	(uint32_t) FSMC_IRQHandler, // 0x0000 0100
	(uint32_t) SDIO_IRQHandler, // 0x0000 0104
	(uint32_t) TIM5_IRQHandler, // 0x0000 0108
	(uint32_t) SPI3_IRQHandler, // 0x0000 010C
	(uint32_t) UART4_IRQHandler, // 0x0000 0110
	(uint32_t) UART5_IRQHandler, // 0x0000 0114
	(uint32_t) TIM6_DAC_IRQHandler, // 0x0000 0118
	(uint32_t) TIM7_IRQHandler, // 0x0000 011C
	(uint32_t) DMA2_Stream0_IRQHandler, // 0x0000 0120
	(uint32_t) DMA2_Stream1_IRQHandler, // 0x0000 0124
	(uint32_t) DMA2_Stream2_IRQHandler, // 0x0000 0128
	(uint32_t) DMA2_Stream3_IRQHandler, // 0x0000 012C
	(uint32_t) DMA2_Stream4_IRQHandler, // 0x0000 0130
	0, // 0x0000 0134
	0, // 0x0000 0138
	(uint32_t) CAN2_TX_IRQHandler, // 0x0000 013C
	(uint32_t) CAN2_RX0_IRQHandler, // 0x0000 0140
	(uint32_t) CAN2_RX1_IRQHandler, // 0x0000 0144
	(uint32_t) CAN2_SCE_IRQHandler, // 0x0000 0148
	(uint32_t) OTG_FS_IRQHandler, // 0x0000 014C
	(uint32_t) DMA2_Stream5_IRQHandler, // 0x0000 0150
	(uint32_t) DMA2_Stream6_IRQHandler, // 0x0000 0154
	(uint32_t) DMA2_Stream7_IRQHandler, // 0x0000 0158
	(uint32_t) USART6_IRQHandler, // 0x0000 015C
	(uint32_t) I2C3_EV_IRQHandler, // 0x0000 0160
	(uint32_t) I2C3_ER_IRQHandler, // 0x0000 0164
	(uint32_t) OTG_HS_EP1_OUT_IRQHandler, // 0x0000 0168
	(uint32_t) OTG_HS_EP1_IN_IRQHandler, // 0x0000 016C
	(uint32_t) OTG_HS_WKUP_IRQHandler, // 0x0000 0170
	(uint32_t) OTG_HS_IRQHandler, // 0x0000 0174
	(uint32_t) DCMI_IRQHandler, // 0x0000 0178
	0, // 0x0000 017C
	0, // 0x0000 0180
	(uint32_t) FPU_IRQHandler, // 0x0000 0184
	0, // 0x0000 0188
	0, // 0x0000 018C
	(uint32_t) SPI4_IRQHandler, // 0x0000 0190
	0, // 0x0000 0194
	0, // 0x0000 0198
	(uint32_t) SAI1_IRQHandler, // 0x0000 019C
	0, // 0x0000 01A0
	0, // 0x0000 01A4
	0, // 0x0000 01A8
	(uint32_t) SAI2_IRQHandler, // 0x0000 01AC
	(uint32_t) QuadSPI_IRQHandler, // 0x0000 01B0
	(uint32_t) HDMICEC_IRQHandler, // 0x0000 01B4
	(uint32_t) SPIDIFRx_IRQHandler, // 0x0000 01B8
	(uint32_t) FMPI2C1_IRQHandler, // 0x0000 01BC
	(uint32_t) FMPI2Cerror_IRQHandler, // 0x0000 01C0
};


void Default_Handler(void) { while(1); }

void Reset_Handler(void) {
	
	uint32_t size = (uint32_t) &_edata - (uint32_t) &_sdata;
	
	uint8_t *pDestAddrs = (uint8_t*) &_sdata; //SRAM
	uint8_t *pSourceAddrs = (uint8_t*) &_la_data; //Flash

	//Copy .data section into SRAM
	for (uint32_t i=0; i<size; i++) {

		*pDestAddrs++ = *pSourceAddrs++;
	}

	//Initialize .bss section to 0 in SRAM	
	size = (uint32_t) &_ebss - (uint32_t) &_sbss;
	
	pDestAddrs = (uint8_t*) &_sbss;
	
	for (uint32_t i=0; i<size; i++) {
		
		*pDestAddrs++ = 0;
	}

	//Initialize Newlib
	__libc_init_array();

	//Start main
	main();
}




