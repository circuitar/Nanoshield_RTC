/*
This is the library to access the DS1307 RTC IC

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#include "Arduino.h"
#include <Wire.h>
#include "DS1307.h"

bool DS1307::begin(uint8_t clkout)
{
	// Initiate the Wire library and join the I2C bus as a master
  Wire.begin();

  // Configure RTC: disable all alarms and enable both the 32.768KHz
	// and 1Hz square wave output
  Wire.beginTransmission(i2cAddr);
  Wire.write(0x07);                         // Start address
  Wire.write(0b00010000 | (clkout & 0b11)); // Control
  return Wire.endTransmission() == 0;
}

bool DS1307::start()
{
	int sec;

  // Address register containing the seconds
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);
  if (Wire.endTransmission()) return false;

	// Read seconds register
  if (Wire.requestFrom((int)i2cAddr, 1) != 1) return false;
  sec = Wire.read();

  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);            // Start address
	Wire.write(sec & ~0b10000000);      // Set CH bit to  to start the RC
  return Wire.endTransmission() == 0;
}

bool DS1307::stop()
{
	int sec;

  // Address register containing the seconds
  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);
  if (Wire.endTransmission()) return false;

	// Read seconds register
  if (Wire.requestFrom((int)i2cAddr, 1) != 1) return false;
  sec = Wire.read();

  Wire.beginTransmission(i2cAddr);
  Wire.write(secondsAddr);            // Start address
	Wire.write(sec | 0b10000000);       // Set CH bit to 1 to stop the RC
  return Wire.endTransmission() == 0;
}
