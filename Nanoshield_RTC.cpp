/*
This is the library to access the RTC Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#include "Arduino.h"
#include <Wire.h>
#include "Nanoshield_RTC.h"

Nanoshield_RTC::Nanoshield_RTC() {
	i2cAddr = 0x51;
	secondsAddr = 0x02;
	minutesAddr = 0x03;
	hoursAddr = 0x04;
	dayAddr = 0x05;
	weekdayAddr = 0x06;
	monthAddr = 0x07;
	yearAddr = 0x08;
}

bool Nanoshield_RTC::begin(uint8_t clkout)
{
	// Initiate the Wire library and join the I2C bus as a master
  Wire.begin();

  // Configure RTC: disable all alarms/timers and enable 1.024kHz output clock
  Wire.beginTransmission(i2cAddr);
  Wire.write(0x00);            // Start address
  Wire.write(0);               // Control and status 1
  Wire.write(0);               // Control and status 2
  if (Wire.endTransmission()) return false;

  Wire.beginTransmission(i2cAddr);
  Wire.write(0x09);                         // Start address
  Wire.write(0b10000000);                   // Minute alarm (and alarm disabled)
  Wire.write(0b10000000);                   // Hour alarm (and alarm disabled)
  Wire.write(0b10000000);                   // Day alarm (and alarm disabled)
  Wire.write(0b10000000);                   // Weekday alarm (and alarm disabled)
  Wire.write(0b10000000 | (clkout & 0b11)); // Output clock frequency     
  Wire.write(0);                            // Timer (countdown) disabled
  Wire.write(0);                            // Timer value
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::start()
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(0x00);            // Start address
  Wire.write(0);               // Control and status 1: start RTC
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::stop()
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(0x00);            // Start address
  Wire.write(0x00100000);      // Control and status 1: stop RTC
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::write(int sec, int min, int hour, int day, int wday, int mon, int year)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);            // Start address
  Wire.write(decToBcd(sec));          // Second (0-59)
  Wire.write(decToBcd(min));          // Minute (0-59)
  Wire.write(decToBcd(hour));         // Hour (0-23)
  Wire.write(decToBcd(day));          // Day (1-31)
  Wire.write(decToBcd(wday));         // Weekday (0-6 = Sunday-Saturday)
	if (year >= 2000) {
		Wire.write(decToBcd(mon) | 0x80); // Month (1-12, century bit (bit 7) = 1)
	} else {
		Wire.write(decToBcd(mon) & 0x7F); // Month (1-12, century bit (bit 7) = 0)
	}
  Wire.write(decToBcd(year % 100));   // Year (00-99)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeSeconds(int sec)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);     // Start address
  Wire.write(decToBcd(sec));   // Second (0-59)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeMinutes(int min)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(minutesAddr);     // Start address
  Wire.write(decToBcd(min));   // Minute (0-59)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeHours(int hour)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(hoursAddr);       // Start address
  Wire.write(decToBcd(hour));  // Hour (0-23)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeDay(int day)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(dayAddr);         // Start address
  Wire.write(decToBcd(day));   // Day (1-31)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeWeekday(int wday)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(weekdayAddr);     // Start address
  Wire.write(decToBcd(wday));  // Weekday (0-6 = Sunday-Saturday)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeMonth(int mon)
{
	int century;

  // Address register containing the months and century
  Wire.beginTransmission(i2cAddr);
  Wire.write(monthAddr);
  if (Wire.endTransmission()) return false;

	// Read month register
  if (Wire.requestFrom((int)i2cAddr, 1) != 1) return false;
  century = Wire.read() & 0x80;

  Wire.beginTransmission(i2cAddr);
  Wire.write(monthAddr);              // Start address
	if (century) {
		Wire.write(decToBcd(mon) | 0x80); // Month (1-12, century bit (bit 7) = 1)
	} else {
		Wire.write(decToBcd(mon) & 0x7F); // Month (1-12, century bit (bit 7) = 0)
	}
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::writeYear(int year)
{
	int mon;

  // Address register containing the months and century
  Wire.beginTransmission(i2cAddr);
  Wire.write(monthAddr);
  if (Wire.endTransmission()) return false;

	// Read month register
  if (Wire.requestFrom((int)i2cAddr, 1) != 1) return false;
  mon = bcdToDec(Wire.read() & 0x1F);

	// Rewrite month along with century bit
  Wire.beginTransmission(i2cAddr);
  Wire.write(monthAddr);              // Start address
	if (year / 100 == 19) {             // Set century bit to zero if 20th century
		Wire.write(decToBcd(mon) & 0x7F); // Month (1-12, century bit (bit 7) = 0)
	} else {
		Wire.write(decToBcd(mon) | 0x80); // Month (1-12, century bit (bit 7) = 1)
	}
  if (Wire.endTransmission() != 0) return false;

	// Write year
  Wire.beginTransmission(i2cAddr);
  Wire.write(yearAddr);              // Start address
  Wire.write(decToBcd(year % 100));  // Year (00-99)
  return Wire.endTransmission() == 0;
}

bool Nanoshield_RTC::read()
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
  day     = bcdToDec(Wire.read() & 0x3F);
  weekday = Wire.read() & 0x07;
  month   = Wire.read();
	century = month >> 7;
	month   = bcdToDec(month & 0x1F);
  year    = bcdToDec(Wire.read()) + 1900;
	if (century) year += 100;
	
	return true;
}

void Nanoshield_RTC::getTime(char* time)
{
	// Format time to YYYY-MM-DD HH:MM:SS
	sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hours, minutes, seconds);
}

int Nanoshield_RTC::getSeconds()
{
	return seconds;
}

int Nanoshield_RTC::getMinutes()
{
	return minutes;
}

int Nanoshield_RTC::getHours()
{
	return hours;
}

int Nanoshield_RTC::getDay()
{
	return day;
}

int Nanoshield_RTC::getWeekday()
{
	return weekday;
}

int Nanoshield_RTC::getMonth()
{
	return month;
}

int Nanoshield_RTC::getYear()
{
	return year;
}

uint8_t Nanoshield_RTC::bcdToDec(uint8_t value)
{
  return ((value / 16) * 10 + value % 16);
}

uint8_t Nanoshield_RTC::decToBcd(uint8_t value){
  return (value / 10 * 16 + value % 10);
}
