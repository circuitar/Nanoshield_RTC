/*
This is the library to access the RTCPlus Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#ifndef NANOSHIELD_RTCPLUS_h
#define NANOSHIELD_RTCPLUS_h

#include "Arduino.h"
#include "Nanoshield_RTC.h"

#define NANOSHIELD_RTC_PLUS_CLKOUT_1_HZ    0
#define NANOSHIELD_RTC_PLUS_CLKOUT_1024_HZ 1
#define NANOSHIELD_RTC_PLUS_CLKOUT_4096_HZ 2
#define NANOSHIELD_RTC_PLUS_CLKOUT_8192_HZ 3

class Nanoshield_RTCPlus: public Nanoshield_RTC {
	public:
		Nanoshield_RTCPlus();
		bool begin(uint8_t clkout = NANOSHIELD_RTC_PLUS_CLKOUT_1_HZ);
		bool start();
		bool stop();
		bool write(int sec, int min, int hour, int day, int wday, int mon, int year);
		bool writeWeekday(int wday);
		bool read();
};

#endif
