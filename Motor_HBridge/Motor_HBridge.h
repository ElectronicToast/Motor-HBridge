/**
 * Motor_HBridge.h - Library for bidirectional PWM DC brushed motor control
 * with the L293D or similar H-bridge
 *
 * Author:      Ray Sun
 * Version:     1.3
 * Date:        30 September 2018
 *
 * Copyright (c) 2018 Ray Sun
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef MTR_HB
#define MTR_HB


#include "Arduino.h"

#define MTR_NO_PIN      255
#define MTR_FORWARD     false
#define MTR_REVERSED    true


class MotorHB
{
    private:
        int setting = 0;

        bool attached       = false;
        bool dualDrivePins  = false;
        bool reversed       = false;

        byte pin1    = MTR_NO_PIN;
        byte pin2    = MTR_NO_PIN;
        byte pinPwm  = MTR_NO_PIN;

    public:
        MotorHB();
        MotorHB(byte pin1, byte pin2, byte pinPwm);
        MotorHB(byte pin1, byte pin2, byte pinPwm, bool rev);

        void attach(byte pin1, byte pin2, byte pinPwm);
        void attach(byte pin1, byte pin2, byte pinPwm, bool rev);

        void set(int pwr);
        bool isReversed();
        void reverse(bool rev);
};


#endif
