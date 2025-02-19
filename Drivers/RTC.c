#include "RTC.h"

//Global Variables-------------------------------------------------------
RTCx *const RTC = ADDR_RTC;


void RTC_Init(void) {
	RTC->ControlReg.hour24Form0_hourAMPMForm1 = 1;
	RTC->ControlReg.enable_AlarmA = 1;
}

void Set_Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t amPm) {
	
	RTC->TimeReg.rw_SecondUnits  = (second < 10) ? second : second % 10;
	RTC->TimeReg.rw_SecondTens  = (second < 10) ? 0 : second / 10;
	RTC->TimeReg.rw_MinuteUnits  = (minute < 10) ? minute : minute % 10;
	RTC->TimeReg.rw_MinuteTens  = (minute < 10) ? 0 : minute / 10;
	RTC->TimeReg.rw_HourUnits  = (hour < 10) ? hour : hour % 10;
	RTC->TimeReg.rw_HourTens  = (hour < 10) ? 0 : hour / 10;
	RTC->TimeReg.amOr24Hour0_pm1  = amPm;
}

void Set_Date(uint8_t day, uint8_t month, uint8_t year, uint8_t weekday) {
	
	RTC->DateReg.rw_DateUnits  = (day < 10) ? day : day % 10;
	RTC->DateReg.rw_DateTens  = (day < 10) ? 0 : day / 10;
	RTC->DateReg.rw_MontUnits  = (month < 10) ? month : month % 10;
	RTC->DateReg.rw_MonthTens  = (month < 10) ? 0 : month / 10;
	RTC->DateReg.rw_WeekDayUnits  = weekday;
	RTC->DateReg.rw_YearUnits  = (year < 10) ? year : year % 10;
	RTC->DateReg.rw_YearTens  = (year < 10) ? 0 : year / 10;
}

void Set_TimeAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t amPm) {
	
	RTC->AlarmAReg.rw_SecondUnits  = (second < 10) ? second : second % 10;
	RTC->AlarmAReg.rw_SecondTens  = (second < 10) ? 0 : second / 10;
	RTC->AlarmAReg.rw_MinuteUnits  = (minute < 10) ? minute : minute % 10;
	RTC->AlarmAReg.rw_MinuteTens  = (minute < 10) ? 0 : minute / 10;
	RTC->AlarmAReg.rw_HourUnits  = (hour < 10) ? hour : hour % 10;
	RTC->AlarmAReg.rw_HourTens  = (hour < 10) ? 0 : hour / 10;
	RTC->AlarmAReg.amOr24Hour0_pm1  = amPm;
}

void Set_DateAlarm(uint8_t day, uint8_t dateWeek) {
	
	RTC->AlarmAReg.rw_DateUnits  = (day < 10) ? day : day % 10;
	RTC->AlarmAReg.rw_DateTens  = (day < 10) ? 0 : day / 10;
	RTC->AlarmAReg.dateUnits0_weekDay1 = dateWeek; //0 or 1
}

void Get_Time(void) {
	
	uint8_t second2 = RTC->TimeReg.rw_SecondUnits;
	uint8_t second1 = RTC->TimeReg.rw_SecondTens;
	uint8_t minute2 = RTC->TimeReg.rw_MinuteUnits;
	uint8_t minute1 = RTC->TimeReg.rw_MinuteTens;
	uint8_t hour2 = RTC->TimeReg.rw_HourUnits;
	uint8_t hour1 = RTC->TimeReg.rw_HourTens;
	uint8_t amPm = RTC->TimeReg.amOr24Hour0_pm1;
	
	char *hour12 = ((void*)0);
	char pm[] = "PM";
	char am[] = "AM";
	hour12 = (amPm == 1) ? pm : am;
	
	printf("%u%u:%u%u:%u%u %s", hour1, hour2, minute1, minute2, second1, second2, hour12 );
	//you don't have to dereference the char * pointer to print its value. I have no idea why not.
}

void Get_Date(void) {
	
	uint8_t date2 = RTC->DateReg.rw_DateUnits;
	uint8_t date1 = RTC->DateReg.rw_DateTens;
	uint8_t month2 = RTC->DateReg.rw_MontUnits;
	uint8_t month1 = RTC->DateReg.rw_MonthTens;
	uint8_t weekday = RTC->DateReg.rw_WeekDayUnits;
	uint8_t year2 = RTC->DateReg.rw_YearUnits;
	uint8_t year1 = RTC->DateReg.rw_YearTens;
	
	char *weekString;
	switch (weekday) {
		case SUNDAY : 
			weekString = "Sunday";
			break;
		case MONDAY : 
			weekString = "Monday";
			break;
		case TUESDAY : 
			weekString = "Tuesday";
			break;
		case WEDNESDAY : 
			weekString = "Wednesday";
			break;
		case THURSDAY : 
			weekString = "Thursday";
			break;
		case FRIDAY : 
			weekString = "Friday";
			break;
		case SATURDAY : 
			weekString = "Saturday";
			break;
	}
	
	printf("%s: %u%u/%u%u/%u%u", weekString, month1, month2, date1, date2, year1, year2 );
}

