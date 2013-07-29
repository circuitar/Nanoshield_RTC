/*
This is the library to access the DS1307 RTC IC

Copyright (c) 2013 Luis Fernando Chavier
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#ifndef DS1307_h
#define DS1307_h

#include "Arduino.h"
#include "Nanoshield_RTCPlus.h"

#define DS1307_CLKOUT_1_HZ     0
#define DS1307_CLKOUT_4096_HZ  1
#define DS1307_CLKOUT_8192_HZ  2
#define DS1307_CLKOUT_32768_HZ 3

class DS1307: public Nanoshield_RTCPlus {
	public:
		bool begin(uint8_t clkout = DS1307_CLKOUT_32768_HZ);
		bool start();
		bool stop();
};

#endif
