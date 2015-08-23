/**
 * @file DS1307.h
 * This is the library to access the DS1307 RTC IC
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */

#ifndef DS1307_h
#define DS1307_h

#include "Arduino.h"
#include "DS3231.h"

#define DS1307_CLKOUT_1_HZ     0
#define DS1307_CLKOUT_4096_HZ  1
#define DS1307_CLKOUT_8192_HZ  2
#define DS1307_CLKOUT_32768_HZ 3

class DS1307: public DS3231 {
  public:
    /**
     * @brief Initializes the DS1307 object.
     * 
     * Disable all alarms and enable both the clkout and 1Hz square 
     * wave output.
     * 
     * @param clkout Output clock. Default at 32768. Use one of these:
     *         - DS1307_CLKOUT_1_HZ
             - DS1307_CLKOUT_4096_HZ
             - DS1307_CLKOUT_8192_HZ
             - DS1307_CLKOUT_32768_HZ
     * @return True on success. False if there were errors.
     */
    bool begin(uint8_t clkout = DS1307_CLKOUT_32768_HZ);

    /**
     * @brief Starts the RTC.
     * @return True on success. False if there were errors.
     */
    bool start();

    /**
     * @brief Stops the RTC.
     * @return True on success. False if there were errors.
     */
    bool stop();
};

#endif
