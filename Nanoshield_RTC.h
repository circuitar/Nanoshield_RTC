/*
This is the library to access the RTC Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#ifndef NANOSHIELD_RTC_h
#define NANOSHIELD_RTC_h

#ifdef ARDUPI
	#include "arduPi.h"
#else
	#include "Arduino.h"
	#include <Wire.h>
#endif

#define NANOSHIELD_RTC_CLKOUT_32768_HZ 0
#define NANOSHIELD_RTC_CLKOUT_1024_HZ  1
#define NANOSHIELD_RTC_CLKOUT_32_HZ    2
#define NANOSHIELD_RTC_CLKOUT_1_HZ     3

class Nanoshield_RTC {
	public:
		Nanoshield_RTC();
		bool begin(uint8_t clkout = NANOSHIELD_RTC_CLKOUT_1_HZ);
		bool start();
		bool stop();
		bool write(int sec, int min, int hour, int day, int wday, int mon, int year);
		bool writeSeconds(int sec);
		bool writeMinutes(int min);
		bool writeHours(int hour);
		bool writeDay(int day);
		bool writeWeekday(int wday);
		bool writeMonth(int mon);
		bool writeYear(int year);
		bool read();
		void getTime(char* time);
		int getSeconds();
		int getMinutes();
		int getHours();
		int getDay();
		int getWeekday();
		int getMonth();
		int getYear();

	protected:
		uint8_t bcdToDec(uint8_t value);
		uint8_t decToBcd(uint8_t value);
		
		int seconds;
		int minutes;
		int hours;
		int day;
		int weekday;
		int month;
		int year;
		
		uint8_t i2cAddr;
		
		uint8_t secondsAddr;
		uint8_t minutesAddr;
		uint8_t hoursAddr;
		uint8_t dayAddr;
		uint8_t weekdayAddr;
		uint8_t monthAddr;
		uint8_t yearAddr;
};

#endif