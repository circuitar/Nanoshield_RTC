/**
 * @file Nanoshield_RTC.h
 * This is the library to access the RTC Nanoshield
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
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
		/**
		 * @brief Constructor.
		 * 
		 * Creates the object to access the Nanoshield RTC.
		 */
		Nanoshield_RTC();

		/**
		 * @brief Initializes the Nanoshield RTC object.
		 * 
		 * Disables all alarms and set the clock output to clkout.
		 * 
		 * @param clkout The clock output. Use one of these:
		 *							 - NANOSHIELD_RTC_CLKOUT_32768_HZ
		 *							 - NANOSHIELD_RTC_CLKOUT_1024_HZ
		 *							 - NANOSHIELD_RTC_CLKOUT_32_HZ
		 *							 - NANOSHIELD_RTC_CLKOUT_1_HZ
		 * @return True on success. False if there were errors.
		 */
		bool begin(uint8_t clkout = NANOSHIELD_RTC_CLKOUT_1_HZ);

		/**
		 * @brief Starts the RTC.
		 * 
		 * @return True on success. False if there were errors.
		 */
		bool start();

		/**
		 * @brief Stops the RTC.
		 * 
		 * @return True on success. False if there were errors.
		 */
		bool stop();

		/**
		 * @brief Sets the RTC date and time.
		 * 
		 * @param sec Seconds from 0 to 59.
		 * @param min Minutes from 0 to 59.
		 * @param hour Hour from 0 to 23.
		 * @param day Day from 1 to 31.
		 * @param wday Weekday from 0 to 6 as Sunday to Saturday respectively.
		 * @param mon Month from 1 to 12.
		 * @param year Year (4 digits).
		 * @return True on success. False if there were errors.
		 */
		bool write(int sec, int min, int hour, int day, int wday, int mon, int year);

		/**
		 * @brief Sets the RTC seconds.
		 * 
		 * @param sec Seconds from 0 to 59.
		 * @return True on success. False if there were errors.
		 */
		bool writeSeconds(int sec);

		/**
		 * @brief Sets the RTC minutes.
		 * 
		 * @param min Minutes from 0 to 59.
		 * @return True on success. False if there were errors.
		 */
		bool writeMinutes(int min);

		/**
		 * @brief Sets the RTC hour.
		 * 
		 * @param hour Hour from 0 to 23.
		 * @return True on success. False if there were errors.
		 */
		bool writeHours(int hour);

		/**
		 * @brief Sets the RTC day.
		 * 
		 * @param day Day from 1 to 31.
		 * @return True on success. False if there were errors.
		 */
		bool writeDay(int day);

		/**
		 * @brief Sets the RTC weekday.
		 * 
		 * @param wday Weekday from 0 to 6 as Sunday to Saturday respectively.
		 * @return True on success. False if there were errors.
		 */
		bool writeWeekday(int wday);

		/**
		 * @brief Sets the RTC month.
		 * 
		 * @param mon Month from 1 to 12.
		 * @return True on success. False if there were errors.
		 */
		bool writeMonth(int mon);

		/**
		 * @brief Sets the RTC year.
		 * 
		 * @param year Year (4 digits).
		 * @return True on success. False if there were errors.
		 */
		bool writeYear(int year);

		/**
		 * @brief Read datetime from RTC and stores internally.
		 * 
		 * The datetime can be accessed with getters or getTime, that returns a
		 * timestamp string.
		 *
		 * @return True on success. False if there were errors.
		 * 
		 * @see getTime()
		 * @see getSeconds()
		 * @see getMinutes()
		 * @see getHours()
		 * @see getDay()
		 * @see getWeekday()
		 * @see getMonth()
		 * @see getYear()
		 */
		bool read();

		/**
		 * @brief Get a timestamp of the last reading.
		 * 
		 * The timestamp is in format YYYY-MM-DD HH:MM:SS.
		 * 
		 * @param time Output pointer to timestamp.
		 */
		void getTime(char* time);

		/**
		 * @brief Gets the seconds of the last reading.
		 * 
		 * @return Seconds of the last reading.
		 */
		int getSeconds();

		/**
		 * @brief Gets the minutes of the last reading.
		 * 
		 * @return Minutes of the last reading.
		 */
		int getMinutes();

		/**
		 * @brief Gets the hour of the last reading.
		 * 
		 * @return Hour of the last reading.
		 */
		int getHours();

		/**
		 * @brief Gets the day of the last reading.
		 * 
		 * @return Day of the last reading.
		 */
		int getDay();

		/**
		 * @brief Gets the weekday of the last reading.
		 * 
		 * @return Weekday of the last reading.
		 */
		int getWeekday();

		/**
		 * @brief Gets the month of the last reading.
		 * 
		 * @return Month of the last reading.
		 */
		int getMonth();

		/**
		 * @brief Gets the year of the last reading.
		 * 
		 * @return Year of the last reading.
		 */
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