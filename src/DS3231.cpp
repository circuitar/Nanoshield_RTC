/**
 * @file DS3231.cpp
 * This is the library to access the RTCPlus Nanoshield
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */

#include "Arduino.h"
#include <Wire.h>
#include "DS3231.h"

DS3231::DS3231() {
  i2cAddr = 0x68;
  secondsAddr = 0x00;
  minutesAddr = 0x01;
  hoursAddr = 0x02;
  weekdayAddr = 0x03;
  dayAddr = 0x04;
  monthAddr = 0x05;
  yearAddr = 0x06;
}

bool DS3231::begin(uint8_t clkout)
{
  // Initiate the Wire library and join the I2C bus as a master
  Wire.begin();

  // Configure RTC: disable all alarms and enable both the 32.768KHz
  // and 1Hz square wave output
  Wire.beginTransmission(i2cAddr);
  Wire.write(0x0E);                                // Start address
  Wire.write(0b00000100 | ((clkout & 0b11) << 3)); // Control
  Wire.write(0b00001000);                          // Status
  return Wire.endTransmission() == 0;
}

bool DS3231::start()
{
  // DS3231 is always running when powered by VCC, so keep this
  // function here just for backwards compatibility with the
  // Nanoshield_RTC library
  return true;
}

bool DS3231::stop()
{
  // DS3231 is always running when powered by VCC, so keep this
  // function here just for backwards compatibility with the
  // Nanoshield_RTC library
  return true;
}

bool DS3231::write(int sec, int min, int hour, int day, int wday, int mon, int year)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);            // Start address
  Wire.write(decToBcd(sec));          // Second (0-59)
  Wire.write(decToBcd(min));          // Minute (0-59)
  Wire.write(decToBcd(hour));         // Hour (0-23)
  Wire.write(decToBcd(wday + 1));     // Weekday (1-7 = Sunday-Saturday)
  Wire.write(decToBcd(day));          // Day (1-31)
  if (year >= 2000) {
    Wire.write(decToBcd(mon) | 0x80); // Month (1-12, century bit (bit 7) = 1)
  } else {
    Wire.write(decToBcd(mon) & 0x7F); // Month (1-12, century bit (bit 7) = 0)
  }
  Wire.write(decToBcd(year % 100));   // Year (00-99)
  return Wire.endTransmission() == 0;
}

bool DS3231::writeWeekday(int wday)
{
  // Number of days on DS3231 are 1-7 instead of 0-6
  return Nanoshield_RTC::writeWeekday(wday + 1);
}

bool DS3231::read()
{
  int century = 0;

  // Address register containing the seconds
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);
  if (Wire.endTransmission()) return false;

  // Read time and date registers
  if (Wire.requestFrom((int)i2cAddr, 7) != 7) return false;
  seconds = bcdToDec(Wire.read() & 0x7F);
  minutes = bcdToDec(Wire.read() & 0x7F);
  hours   = bcdToDec(Wire.read() & 0x3F);
  weekday = Wire.read() & 0x07;
  day     = bcdToDec(Wire.read() & 0x3F);
  month   = Wire.read();
  century = month >> 7;
  month   = bcdToDec(month & 0x1F);
  year    = bcdToDec(Wire.read()) + 1900;
  if (century) year += 100;
  
  return true;
}
