/*
This a simple serial port clock application using the RTC Nanoshield.

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#include <Wire.h>
#include <stdio.h>
#include "Nanoshield_RTC.h"

Nanoshield_RTC rtc;

#define BUFFER_SIZE 50
char buf[BUFFER_SIZE];
char date[11];
char time[9];
char itime[20];

void setup()
{
  Serial.begin(115200);
  Serial.println("-------------------------");
  Serial.println(" Nanoshield Serial Clock");
  Serial.println("-------------------------");
  Serial.println("");

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Failed starting RTC");
    while(true);
  };

  // Print current time and ask for the new time
  Serial.print("Current time:\n");
  rtc.read();
  
  // Set date and time
  rtc.writeYear(2018);
  rtc.writeMonth(03);
  rtc.writeDay(21);
  rtc.writeHours(14);
  rtc.writeMinutes(40);
  rtc.writeSeconds(00);
}

void loop()
{
  // Read time from RTC
  rtc.read();

  // Print time in the serial port
  sprintf(date, "%04d-%02d-%02d", rtc.getYear(), rtc.getMonth(), rtc.getDay());
  sprintf(time, "%02d:%02d:%02d", rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
  Serial.print(date);
  Serial.print(" ");
  Serial.println(time);
  
  //Wait for next second
  delay(1000);
}

