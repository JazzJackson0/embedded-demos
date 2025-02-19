//STM32F407 Driver
#ifndef RTC_H_
#define RTC_H_
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>     // for formatting stdint types 

//RTC
typedef struct _rtc RTCx;
#define RTC_BASE 0x40002800
#define ADDR_RTC ( (RTCx*) (RTC_BASE) )

//RTC_DATE Register
/*Weekday Units*/
#define MONDAY 0x01
#define TUESDAY 0x02
#define WEDNESDAY 0x03
#define THURSDAY 0x04
#define FRIDAY 0x05
#define SATURDAY 0x06
#define SUNDAY 0x07
	

//RTC_CONTROL Register
/*Wakeup Clock Type*/
#define RTC_DIV_16 0x00
#define RTC_DIV_8 0x01
#define RTC_DIV_4 0x02
#define RTC_DIV_2 0x03
#define SYNC_PRESCALE 0x05
#define SYNC_PRESCALE_AND_2_TO16POW 0x07

/*Output Selection*/
#define ALARM_A 0x01
#define ALARM_B 0x02
#define WAKEUP 0x03

/*RTC Pins ---------------------------
		These are 'Additional Functions' not 'Alternate Functions'
		Meaning: Functions are directly selected/enabled through peripheral registers.
		They are not selected through GPIOx_AFR registers.
		
		+ RTC_TAMP1: PI8, PC13
		+ RTC_TAMP2: PI8
		+ RTC_TS: PI8, PC13
		+ RTC_OUT: PC13
		+ RTC_REFIN: PB15
		------------------------------------*/

#include <stdint.h>

//DECLARATIONS
/**
 * @brief Initialize RTC
 * 
 * @return ** void 
 */
void RTC_Init(void);
/**
 * @brief Set the Time
 * 
 * @param hour Hour Value
 * @param minute Minute Value
 * @param second Second Value
 * @param amPm AM or PM
 * @return ** void 
 */
void Set_Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t amPm);
/**
 * @brief Set the Date
 * 
 * @param day Day Value
 * @param month Month Value
 * @param year Year Value
 * @param weekday Weekday (1: Monday - 7: Sunday)
 * @return ** void 
 */
void Set_Date(uint8_t day, uint8_t month, uint8_t year, uint8_t weekday);
/**
 * @brief Set time for Alarm
 * 
 * @param hour Hour Value
 * @param minute Minute Value
 * @param second Second Value
 * @param amPm AM or PM
 * @return ** void 
 */
void Set_TimeAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t amPm);
/**
 * @brief Set Date for Alarm
 * 
 * @param day Day Value
 * @param dateWeek 0: Date Units or 1: Weekday Values
 * @return ** void 
 */
void Set_DateAlarm(uint8_t day, uint8_t dateWeek);
/**
 * @brief Get current Time
 * 
 * @return ** void 
 */
void Get_Time(void);
/**
 * @brief Get current date
 * 
 * @return ** void 
 */
void Get_Date(void);

//Unused Enums----------------------------------------------------------------------
/*
RTC_TIME & ALARMS & TIMESTAMP_TIME
AM PM
typedef enum {
	AM = 0x00,
	PM = 0x01
}E_AMPM;
	*/

// Registers----------------------------------------------------------------------------

typedef struct {
	const uint32_t reserved:32;
}RTC_RESERVED;

typedef struct {
	volatile uint32_t rw_SecondUnits:4;
	volatile uint32_t rw_SecondTens:3;
	const uint32_t reserved0:1;
	volatile uint32_t rw_MinuteUnits:4;
	volatile uint32_t rw_MinuteTens:3;
	const uint32_t reserved1:1;
	volatile uint32_t rw_HourUnits:4;
	volatile uint32_t rw_HourTens:2;
	volatile uint32_t amOr24Hour0_pm1:1; //Macro available
	const uint32_t reserved2:9;
}RTC_TIME;

typedef struct {
	volatile uint32_t rw_DateUnits:4;
	volatile uint32_t rw_DateTens:2;
	const uint32_t reserved0:2;
	volatile uint32_t rw_MontUnits:4;
	volatile uint32_t rw_MonthTens:1;
	volatile uint32_t rw_WeekDayUnits:3;
	volatile uint32_t rw_YearUnits:4;
	volatile uint32_t rw_YearTens:4;
	const uint32_t reserved1:8;
}RTC_DATE;

typedef struct {
	volatile uint32_t select_WakeupClock:3;
	volatile uint32_t timstampEventRiseEdge0_timestampEventFallEdge1:1;
	volatile uint32_t enable_ReferenceClockDetection:1;
	volatile uint32_t enable_BypassShadowRegisters:1;
	volatile uint32_t hour24Form0_hourAMPMForm1:1;
	volatile uint32_t enable_DigitalCallibration:1;
	volatile uint32_t enable_AlarmA:1;
	volatile uint32_t enable_AlarmB:1;
	volatile uint32_t enable_WakeUpTimer:1;
	volatile uint32_t enable_TimeStamp:1;
	volatile uint32_t enable_AlarmAInterrupt:1;
	volatile uint32_t enable_AlarmBInterrupt:1;
	volatile uint32_t enable_WakeUpTimerInterrupt:1;
	volatile uint32_t enable_TimeStampInterrupt:1;
	volatile uint32_t rw_SpringForwardAddHour:1;
	volatile uint32_t rw_FallBackRemoveHour:1;
	volatile uint32_t rw_DaylightSavingsAppliedFlag:1;
	volatile uint32_t calibrationOut512Hz0_calibrationOut1Hz1:1;
	volatile uint32_t rtcOutPolarityHigh0_rtcOutPolarityLow1:1;
	volatile uint32_t rw_OutputType:2;
	volatile uint32_t enable_CalibrationOutput:1;
	const uint32_t reserved:8;
}RTC_CONTROL;

typedef struct {
	volatile uint32_t r_AlarmAValueIsChangeable:1;
	volatile uint32_t r_AlarmBValueIsChangeable:1;
	volatile uint32_t r_WakeUpValueIsChangeable:1;
	volatile uint32_t shiftOperationPending:1;
	volatile uint32_t calendarInitialized:1;
	volatile uint32_t calendarShadowRegsSynced:1;
	volatile uint32_t calendarRegsUpdateable:1;
	volatile uint32_t freeRunMode0_initializeMode1:1;
	volatile uint32_t alarmAConditionMet:1;
	volatile uint32_t alarmBConditionMet:1;
	volatile uint32_t wakeupConditionMet:1;
	volatile uint32_t timeStampConditionMet:1;
	volatile uint32_t timeStampOverflowOccurred:1;
	volatile uint32_t tamperingDetectedInput1:1;
	volatile uint32_t tamperingDetectedInput2:1;
	const uint32_t reserved0:1;
	volatile uint32_t reCalibrationPending:1;
	const uint32_t reserved1:15;
}RTC_INITIALIZATION_AND_STATUS;

typedef struct {
	volatile uint32_t rw_SynchronousPrescaler:15;
	const uint32_t reserved0:1;
	volatile uint32_t rw_AsynchronousPrescaler:7;
	const uint32_t reserved1:9;
}RTC_PRESCALER;

typedef struct {
	volatile uint32_t rw_WakeUpAutoReloadValue:16;
	const uint32_t reserved:16;
}RTC_WAKEUP_TIMER;

typedef struct {
	volatile uint32_t rw_DigitalCalibrationValue:5;
	const uint32_t reserved0:2;
	volatile uint32_t positiveCalibration0_negativeCalibration1:1;
	const uint32_t reserved1:24;
}RTC_CALIBRATION1;

typedef struct {
	volatile uint32_t rw_SecondUnits:4;
	volatile uint32_t rw_SecondTens:3;
	volatile uint32_t enable_NoSecondsInAlarmA:1;
	volatile uint32_t rw_MinuteUnits:4;
	volatile uint32_t rw_MinuteTens:3;
	volatile uint32_t enable_NoMinutesInAlarmA:1;
	volatile uint32_t rw_HourUnits:4;
	volatile uint32_t rw_HourTens:2;
	volatile uint32_t amOr24Hour0_pm1:1; //Macro available
	volatile uint32_t enable_NoHoursInAlarmA:1;
	volatile uint32_t rw_DateUnits:4;
	volatile uint32_t rw_DateTens:2;
	volatile uint32_t dateUnits0_weekDay1:1;
	volatile uint32_t enable_NoDateInAlarmA:1;
}RTC_ALARM_A;

typedef struct {
	volatile uint32_t rw_SecondUnits:4;
	volatile uint32_t rw_SecondTens:3;
	volatile uint32_t enable_NoSecondsInAlarmA:1;
	volatile uint32_t rw_MinuteUnits:4;
	volatile uint32_t rw_MinuteTens:3;
	volatile uint32_t enable_NoMinutesInAlarmA:1;
	volatile uint32_t rw_HourUnits:4;
	volatile uint32_t rw_HourTens:2;
	volatile uint32_t amOr24Hour0_pm1:1; //Macro available
	volatile uint32_t enable_NoHoursInAlarmA:1;
	volatile uint32_t rw_DateUnits:4;
	volatile uint32_t rw_DateTens:2;
	volatile uint32_t dateUnits0_weekDay1:1;
	volatile uint32_t enable_NoDateInAlarmA:1;
}RTC_ALARM_B;

typedef struct {
	volatile uint32_t set_WriteProtectionKey:8;
	const uint32_t reserved:24;
}RTC_WRITE_PROTECTION;

typedef struct {
	volatile uint32_t read_SubSecondValue:16;
	const uint32_t reserved:16;
}RTC_SUB_SECOND;

typedef struct {
	volatile uint32_t set_FractionOfSecToSubtract:15;
	const uint32_t reserved:16;
	volatile uint32_t add_1SecToClock:1;
}RTC_SHIFT_CONTROL;

typedef struct {
	volatile uint32_t rw_SecondUnits:4;
	volatile uint32_t rw_SecondTens:3;
	const uint32_t reserved0:1;
	volatile uint32_t rw_MinuteUnits:4;
	volatile uint32_t rw_MinuteTens:3;
	const uint32_t reserved1:1;
	volatile uint32_t rw_HourUnits:4;
	volatile uint32_t rw_HourTens:2;
	volatile uint32_t amOr24Hour0_pm1:1; //Macro available
	const uint32_t reserved2:9;
}RTC_TIMESTAMP_TIME;

typedef struct {
	volatile uint32_t rw_DateUnits:4;
	volatile uint32_t rw_DateTens:2;
	const uint32_t reserved0:2;
	volatile uint32_t rw_MontUnits:4;
	volatile uint32_t rw_MonthTens:1;
	volatile uint32_t rw_WeekDayUnits:3;
	const uint32_t reserved1:16;
}RTC_TIMESTAMP_DATE;

typedef struct {
	volatile uint32_t read_SubSecondValue:16;
	const uint32_t reserved:16;
}RTC_TIMESTAMP_SUBSECOND;

typedef struct {
	volatile uint32_t reduce_RTCFrequency:9;
	const uint32_t reserved0:4;
	volatile uint32_t enable_16SecCalibrationCycle:1;
	volatile uint32_t enable_8SecCalibrationCycle:1;
	volatile uint32_t increase_RTCFrequency:9;
	const uint32_t reserved1:16;
}RTC_CALIBRATION2;

typedef struct {
	volatile uint32_t enable_Tamper1Detection:1;
	volatile uint32_t t1RiseEdgeOrLowTrig0_t1FallEdgeOrHighTrig1:1;
	volatile uint32_t enable_TamperInterrupt:1;
	volatile uint32_t enable_Tamper2Detection:1;
	volatile uint32_t t2RiseEdgeOrLowTrig0_t2FallEdgeOrHighTrig1:1;
	const uint32_t reserved0:2;
	volatile uint32_t enable_TamperDetectionTimeStamp:1;
	volatile uint32_t rw_TamperSamplingFrrequency:3;
	volatile uint32_t rw_TamperFilterCount:2;
	volatile uint32_t rw_TamperPreChargeDuration:2;
	volatile uint32_t disable_TamperPinPreCharge:1;
	volatile uint32_t rtcAF1AsTamperOne0_rtcAF2AsTamperOne1:1;
	volatile uint32_t rtcAF1AsTimeStamp0_rtcAF2AsTimeStamp1:1;
	volatile uint32_t rtcAlarmAsOpenDrain0_rtcAlarmAsPushPull1:1;
	const uint32_t reserved1:13;
}RTC_TAMPER_AND_ALTFUNC_CONFIG;

typedef struct {
	volatile uint32_t rw_SubSecondValue:15;
	const uint32_t reserved0:9;
	volatile uint32_t rw_SectionOfSubSecondToIgnore:4;
	const uint32_t reserved1:4;
}RTC_ALARM_A_SUBSECOND;

typedef struct {
	volatile uint32_t rw_SubSecondValue:15;
	const uint32_t reserved0:9;
	volatile uint32_t rw_SectionOfSubSecondToIgnore:4;
	const uint32_t reserved1:4;
}RTC_ALARM_B_SUBSECOND;

typedef struct {
	volatile uint32_t rw_BackupRegister:32;
}RTC_BACKUPS;








struct _rtc {
	RTC_TIME TimeReg; // 0x00
	RTC_DATE DateReg; // 0x04
	RTC_CONTROL ControlReg; // 0x08
	RTC_INITIALIZATION_AND_STATUS InitAndStatusReg; // 0x0C
	RTC_PRESCALER PrescalerReg; // 0x10
	RTC_WAKEUP_TIMER WakeupTimerReg; // 0x14
	RTC_CALIBRATION1 Calibration1Reg; // 0x18
	RTC_ALARM_A AlarmAReg; // 0x1C
	RTC_ALARM_B AlarmBReg; // 0x20
	RTC_WRITE_PROTECTION WriteProtectionReg; // 0x24
	RTC_SUB_SECOND SubSecondReg; // 0x28
	RTC_SHIFT_CONTROL ShiftControlReg; // 0x2C
	RTC_TIMESTAMP_TIME TimestampTimeReg; // 0x30
	RTC_TIMESTAMP_DATE TimestampDateReg; // 0x34
	RTC_TIMESTAMP_SUBSECOND TimestampSubSecondReg; // 0x38
	RTC_CALIBRATION2 Calibration2Reg; // 0x3C
	RTC_TAMPER_AND_ALTFUNC_CONFIG TamperAndAltFuncConfigReg; // 0x40
	RTC_ALARM_A_SUBSECOND AlarmASubSecReg; // 0x44
	RTC_ALARM_B_SUBSECOND AlarmBSubSecReg; // 0x48
	RTC_RESERVED reserved; // 0x4C
	RTC_BACKUPS BackupReg1; // 0x50
	RTC_BACKUPS BackupReg2; // 0x54
	RTC_BACKUPS BackupReg3; // 0x58
	RTC_BACKUPS BackupReg4; // 0x5C
	RTC_BACKUPS BackupReg5; // 0x60
	RTC_BACKUPS BackupReg6; // 0x64
	RTC_BACKUPS BackupReg7; // 0x68
	RTC_BACKUPS BackupReg8; // 0x6C
	RTC_BACKUPS BackupReg9; // 0x70
	RTC_BACKUPS BackupReg10; // 0x74
	RTC_BACKUPS BackupReg11; // 0x78
	RTC_BACKUPS BackupReg12; // 0x7C
	RTC_BACKUPS BackupReg13; // 0x80
	RTC_BACKUPS BackupReg14; // 0x84
	RTC_BACKUPS BackupReg15; // 0x88
	RTC_BACKUPS BackupReg16; // 0x8C
	RTC_BACKUPS BackupReg17; // 0x90
	RTC_BACKUPS BackupReg18; // 0x94
	RTC_BACKUPS BackupReg19; // 0x98
	RTC_BACKUPS BackupReg20; // 0x9C
};


#endif
