/**
 * @file Nanoshield_RTCPlus.h
 * This is the library to access the RTCPlus Nanoshield
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
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
    /**
     * @brief Constructor.
     * 
     * Creates the object to access the Nanoshield RTCPlus.
     */
    Nanoshield_RTCPlus();

    /**
     * @brief Initializes the Nanoshield RTCPlus object.
     * 
     * Disables all alarms and sets the clock output to 32768 and clkout.
     * 
     * @param clkout The clock output. Use one of these:
     *               - NANOSHIELD_RTC_PLUS_CLKOUT_1_HZ
     *               - NANOSHIELD_RTC_PLUS_CLKOUT_1024_HZ
     *               - NANOSHIELD_RTC_PLUS_CLKOUT_4096_HZ
     *               - NANOSHIELD_RTC_PLUS_CLKOUT_8192_HZ
     * @return True on success. False if there were errors.
     */
    bool begin(uint8_t clkout = NANOSHIELD_RTC_PLUS_CLKOUT_1_HZ);

    /**
     * @deprecated DS3231 is always running when powered by VCC, so keep this
     *             function here just for backwards compatibility with the
     *             Nanoshield_RTC library.
     * 
     * @return Always true.
     */
    bool start();

    /**
     * @deprecated DS3231 is always running when powered by VCC, so keep this
     *             function here just for backwards compatibility with the
     *             Nanoshield_RTC library.
     * 
     * @return Always true.
     */
    bool stop();

    /**
     * @brief Sets the RTC date and time.
     * 
     * @param sec Seconds from 0 to 59.
     * @param min Minutes from 0 to 59.
     * @param hour Hour from 0 to 23.
     * @param day Day from 1 to 31.
     * @param wday Weekday from 1 to 7 as Sunday to Saturday respectively.
     * @param mon Month from 1 to 12.
     * @param year Year (4 digits).
     * @return True on success. False if there were errors.
     */
    bool write(int sec, int min, int hour, int day, int wday, int mon, int year);

    /**
     * @brief Sets the RTC weekday.
     * 
     * @param wday Weekday from 1 to 7 as Sunday to Saturday respectively.
     * @return True on success. False if there were errors.
     */
    bool writeWeekday(int wday);

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
};

#endif
