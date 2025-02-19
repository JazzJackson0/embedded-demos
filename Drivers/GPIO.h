//STM32F407 Driver
#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
#include <stddef.h>

//CLOCK
#define CLOCK 0x40023800
#define AHB1 0x30
#define ADDR_GPIOx_CLOCK ( (GPIOx_CLOCK*) ((CLOCK) + AHB1) )

//GPIOx
typedef struct _gpio GPIOx;
#define GPIO_BASE 0x40000000
#define ADDR_GPIOA ( (GPIOx*) ((GPIO_BASE) + 0x20000) )
#define ADDR_GPIOB ( (GPIOx*) ((GPIO_BASE) + 0x20400) )
#define ADDR_GPIOC ( (GPIOx*) ((GPIO_BASE) + 0x20800) )
#define ADDR_GPIOD ( (GPIOx*) ((GPIO_BASE) + 0x20C00) )
#define ADDR_GPIOE ( (GPIOx*) ((GPIO_BASE) + 0x21000) )
#define ADDR_GPIOF ( (GPIOx*) ((GPIO_BASE) + 0x21400) )
#define ADDR_GPIOG ( (GPIOx*) ((GPIO_BASE) + 0x21800) )
#define ADDR_GPIOH ( (GPIOx*) ((GPIO_BASE) + 0x21C00) )
#define ADDR_GPIOI ( (GPIOx*) ((GPIO_BASE) + 0x22000) )

typedef enum _PinModes E_PinModes;
typedef enum _OutSpeeds E_OutSpeeds;
typedef enum _PullUpDown E_PullUpDown;



//DECLARATIONS
/**
 * @brief Initialize given pin.
 * 
 * @param port Port ID (A - I)
 * @param pinNum Pin Number
 * @param modeType Pin Mode: IN, OUT, ANALOG, AF0-AF15 (Analog Functions)
 * @return ** void 
 */
void Pin_Init(char port, uint8_t pinNum, E_PinModes modeType);
/**
 * @brief Get Get Input from given Pin
 * 
 * @param port Port ID (A - I)
 * @param pinNum Pin Number
 * @return ** uint8_t 
 */
uint8_t Pin_GetInput(char port, uint8_t pinNum);
/**
 * @brief Send signal out on given pin
 * 
 * @param port Port ID (A - I)
 * @param pinNum Pin Number
 * @param pinState Pin State: LOW = 0, HIGH = 1
 * @return ** void 
 */
void Pin_Out(char port, uint8_t pinNum, uint8_t pinState);
/**
 * @brief Set Output Speed on given pin
 * 
 * @param port Port ID (A - I)
 * @param pinNum Pin Number
 * @param speed Pin Output Speed: LOW, MED, HIGH, VERY_HIGH
 * @return ** void 
 */
void Pin_OutputSpeed(char port, uint8_t pinNum, E_OutSpeeds speed);
/**
 * @brief Alter Pin's PullUp PullDown Settings
 * 
 * @param port Port ID (A - I)
 * @param pinNum Pin Number
 * @param upDown Set Pin PullUp/PullDown setting to: NONE, UP or DOWN
 * @return ** void 
 */
void Pin_PullUp_PullDown(char port, uint8_t pinNum, E_PullUpDown upDown);

//Enums----------------------------------------------------------------------
//GPIOx_MODE Register & GPIOx_ALTERNATE_FUNCT Registers
/*Pin Modes & Alternate Functions*/
enum _PinModes {
	AF0 = 0x00, AF1 = 0x01, AF2 = 0x02,
	AF3 = 0x03, AF4 = 0x04, AF5 = 0x05,
	AF6 = 0x06, AF7 = 0x07, AF8 = 0x08,
	AF9 = 0x09, AF10 = 0x0A, AF11 = 0x0B,
	AF12 = 0x0C, AF13 = 0x0D, AF14 = 0x0E,
	AF15 = 0x0F,
	IN = 0x10, OUT = 0x11, AF = 0x12, ANALOG = 0x13
};

//GPIOx_OUTPUTSPEED Register
/*Pin Out Speeds*/
enum _OutSpeeds {
	LOW = 0x00, MED = 0x01,
	HIGH = 0x02, VERY_HIGH = 0x03
};

//GPIOx_PULLUP_PULLDOWN Register
/*PullUP PullDown Settings*/
enum _PullUpDown {
	NONE = 0x00, UP = 0x01, DOWN = 0x02
};


//Registers------------------------------------------------------------------
typedef struct {
	volatile uint32_t gpioA_StartTick:1;
	volatile uint32_t gpioB_StartTick:1;
	volatile uint32_t gpioC_StartTick:1;
	volatile uint32_t gpioD_StartTick:1;
	volatile uint32_t gpioE_StartTick:1;
	volatile uint32_t gpioF_StartTick:1;
	volatile uint32_t gpioG_StartTick:1;
	volatile uint32_t gpioH_StartTick:1;
	volatile uint32_t gpioI_StartTick:1;
	const uint32_t reserved:23;
}GPIOx_CLOCK;

typedef volatile struct {
	uint32_t rw_Pin0_Mode:2;
	uint32_t rw_Pin1_Mode:2;
	uint32_t rw_Pin2_Mode:2;
	uint32_t rw_Pin3_Mode:2;
	uint32_t rw_Pin4_Mode:2;
	uint32_t rw_Pin5_Mode:2;
	uint32_t rw_Pin6_Mode:2;
	uint32_t rw_Pin7_Mode:2;
	uint32_t rw_Pin8_Mode:2;
	uint32_t rw_Pin9_Mode:2;
	uint32_t rw_Pin10_Mode:2;
	uint32_t rw_Pin11_Mode:2;
	uint32_t rw_Pin12_Mode:2;
	uint32_t rw_Pin13_Mode:2;
	uint32_t rw_Pin14_Mode:2;
	uint32_t rw_Pin15_Mode:2;
}GPIOx_MODE;


typedef struct {
	volatile uint32_t rw_Pin0_OutType:1;
	volatile uint32_t rw_Pin1_OutType:1;
	volatile uint32_t rw_Pin2_OutType:1;
	volatile uint32_t rw_Pin3_OutType:1;
	volatile uint32_t rw_Pin4_OutType:1;
	volatile uint32_t rw_Pin5_OutType:1;
	volatile uint32_t rw_Pin6_OutType:1;
	volatile uint32_t rw_Pin7_OutType:1;
	volatile uint32_t rw_Pin8_OutType:1;
	volatile uint32_t rw_Pin9_OutType:1;
	volatile uint32_t rw_Pin10_OutType:1;
	volatile uint32_t rw_Pin11_OutType:1;
	volatile uint32_t rw_Pin12_OutType:1;
	volatile uint32_t rw_Pin13_OutType:1;
	volatile uint32_t rw_Pin14_OutType:1;
	volatile uint32_t rw_Pin15_OutType:1;
	const uint32_t reserved:16;
}GPIOx_OUTPUTTYPE;


typedef volatile struct {	
	uint32_t rw_Pin0_OutSpeed:2;
	uint32_t rw_Pin1_OutSpeed:2;
	uint32_t rw_Pin2_OutSpeed:2;
	uint32_t rw_Pin3_OutSpeed:2;
	uint32_t rw_Pin4_OutSpeed:2;
	uint32_t rw_Pin5_OutSpeed:2;
	uint32_t rw_Pin6_OutSpeed:2;
	uint32_t rw_Pin7_OutSpeed:2;
	uint32_t rw_Pin8_OutSpeed:2;
	uint32_t rw_Pin9_OutSpeed:2;
	uint32_t rw_Pin10_OutSpeed:2;
	uint32_t rw_Pin11_OutSpeed:2;
	uint32_t rw_Pin12_OutSpeed:2;
	uint32_t rw_Pin13_OutSpeed:2;
	uint32_t rw_Pin14_OutSpeed:2;
	uint32_t rw_Pin15_OutSpeed:2;
}GPIOx_OUTPUTSPEED;


typedef volatile struct {
	uint32_t rw_Pin0_PUp_PDwn:2;
	uint32_t rw_Pin1_PUp_PDwn:2;
	uint32_t rw_Pin2_PUp_PDwn:2;
	uint32_t rw_Pin3_PUp_PDwn:2;
	uint32_t rw_Pin4_PUp_PDwn:2;
	uint32_t rw_Pin5_PUp_PDwn:2;
	uint32_t rw_Pin6_PUp_PDwn:2;
	uint32_t rw_Pin7_PUp_PDwn:2;
	uint32_t rw_Pin8_PUp_PDwn:2;
	uint32_t rw_Pin9_PUp_PDwn:2;
	uint32_t rw_Pin10_PUp_PDwn:2;
	uint32_t rw_Pin11_PUp_PDwn:2;
	uint32_t rw_Pin12_PUp_PDwn:2;
	uint32_t rw_Pin13_PUp_PDwn:2;
	uint32_t rw_Pin14_PUp_PDwn:2;
	uint32_t rw_Pin15_PUp_PDwn:2;
}GPIOx_PULLUP_PULLDOWN;


typedef struct {
	volatile uint32_t read_Pin0:1;
	volatile uint32_t read_Pin1:1;
	volatile uint32_t read_Pin2:1;
	volatile uint32_t read_Pin3:1;
	volatile uint32_t read_Pin4:1;
	volatile uint32_t read_Pin5:1;
	volatile uint32_t read_Pin6:1;
	volatile uint32_t read_Pin7:1;
	volatile uint32_t read_Pin8:1;
	volatile uint32_t read_Pin9:1;
	volatile uint32_t read_Pin10:1;
	volatile uint32_t read_Pin11:1;
	volatile uint32_t read_Pin12:1;
	volatile uint32_t read_Pin13:1;
	volatile uint32_t read_Pin14:1;
	volatile uint32_t read_Pin15:1;
	const uint32_t reserved:16;
}GPIOx_INPUT;


typedef struct {
	volatile uint32_t rw_Pin0_Out:1;
	volatile uint32_t rw_Pin1_Out:1;
	volatile uint32_t rw_Pin2_Out:1;
	volatile uint32_t rw_Pin3_Out:1;
	volatile uint32_t rw_Pin4_Out:1;
	volatile uint32_t rw_Pin5_Out:1;
	volatile uint32_t rw_Pin6_Out:1;
	volatile uint32_t rw_Pin7_Out:1;
	volatile uint32_t rw_Pin8_Out:1;
	volatile uint32_t rw_Pin9_Out:1;
	volatile uint32_t rw_Pin10_Out:1;
	volatile uint32_t rw_Pin11_Out:1;
	volatile uint32_t rw_Pin12_Out:1;
	volatile uint32_t rw_Pin13_Out:1;
	volatile uint32_t rw_Pin14_Out:1;
	volatile uint32_t rw_Pin15_Out:1;
	const uint32_t reserved:16;
}GPIOx_OUTPUT;

typedef struct {
	volatile uint32_t set_Pin0:1;
	volatile uint32_t set_Pin1:1;
	volatile uint32_t set_Pin2:1;
	volatile uint32_t set_Pin3:1;
	volatile uint32_t set_Pin4:1;
	volatile uint32_t set_Pin5:1;
	volatile uint32_t set_Pin6:1;
	volatile uint32_t set_Pin7:1;
	volatile uint32_t set_Pin8:1;
	volatile uint32_t set_Pin9:1;
	volatile uint32_t set_Pin10:1;
	volatile uint32_t set_Pin11:1;
	volatile uint32_t set_Pin12:1;
	volatile uint32_t set_Pin13:1;
	volatile uint32_t set_Pin14:1;
	volatile uint32_t set_Pin15:1;
	volatile uint32_t reset_Pin0:1;
	volatile uint32_t reset_Pin1:1;
	volatile uint32_t reset_Pin2:1;
	volatile uint32_t reset_Pin3:1;
	volatile uint32_t reset_Pin4:1;
	volatile uint32_t reset_Pin5:1;
	volatile uint32_t reset_Pin6:1;
	volatile uint32_t reset_Pin7:1;
	volatile uint32_t reset_Pin8:1;
	volatile uint32_t reset_Pin9:1;
	volatile uint32_t reset_Pin10:1;
	volatile uint32_t reset_Pin11:1;
	volatile uint32_t reset_Pin12:1;
	volatile uint32_t reset_Pin13:1;
	volatile uint32_t reset_Pin14:1;
	volatile uint32_t reset_Pin15:1;
}GPIOx_BIT_SETRESET;

typedef struct {
	volatile uint32_t rw_Pin0_Locked:1;
	volatile uint32_t rw_Pin1_Locked:1;
	volatile uint32_t rw_Pin2_Locked:1;
	volatile uint32_t rw_Pin3_Locked:1;
	volatile uint32_t rw_Pin4_Locked:1;
	volatile uint32_t rw_Pin5_Locked:1;
	volatile uint32_t rw_Pin6_Locked:1;
	volatile uint32_t rw_Pin7_Locked:1;
	volatile uint32_t rw_Pin8_Locked:1;
	volatile uint32_t rw_Pin9_Locked:1;
	volatile uint32_t rw_Pin10_Locked:1;
	volatile uint32_t rw_Pin11_Locked:1;
	volatile uint32_t rw_Pin12_Locked:1;
	volatile uint32_t rw_Pin13_Locked:1;
	volatile uint32_t rw_Pin14_Locked:1;
	volatile uint32_t rw_Pin15_Locked:1;
	const uint32_t reserved:16;
}GPIOx_CONFIG_LOCK;

typedef volatile struct {
	uint32_t rw_Pin0_AltFunction:4;
	uint32_t rw_Pin1_AltFunction:4;
	uint32_t rw_Pin2_AltFunction:4;
	uint32_t rw_Pin3_AltFunction:4;
	uint32_t rw_Pin4_AltFunction:4;
	uint32_t rw_Pin5_AltFunction:4;
	uint32_t rw_Pin6_AltFunction:4;
	uint32_t rw_Pin7_AltFunction:4;
}GPIOx_ALTERNATE_FUNCT_LOW;


typedef volatile struct {
	uint32_t rw_Pin8_AltFunction:4;
	uint32_t rw_Pin9_AltFunction:4;
	uint32_t rw_Pin10_AltFunction:4;
	uint32_t rw_Pin11_AltFunction:4;
	uint32_t rw_Pin12_AltFunction:4;
	uint32_t rw_Pin13_AltFunction:4;
	uint32_t rw_Pin14_AltFunction:4;
	uint32_t rw_Pin15_AltFunction:4;
}GPIOx_ALTERNATE_FUNCT_HIGH;


struct _gpio {

	GPIOx_MODE ModeReg; // 0x00
	GPIOx_OUTPUTTYPE OutTypeReg; // 0x04
	GPIOx_OUTPUTSPEED OutSpeedReg; // 0x08
	GPIOx_PULLUP_PULLDOWN PullupPullDownReg; // 0x0C
	GPIOx_INPUT InputReg; // 0x10
	GPIOx_OUTPUT OutputReg; // 0x14
	GPIOx_BIT_SETRESET BitSetResetReg; // 0x18
	GPIOx_CONFIG_LOCK ConfigLockReg; // 0x1C
	GPIOx_ALTERNATE_FUNCT_LOW AltFuncLowReg; // 0x20
	GPIOx_ALTERNATE_FUNCT_HIGH AltFuncHighReg; // 0x24
};


#endif
