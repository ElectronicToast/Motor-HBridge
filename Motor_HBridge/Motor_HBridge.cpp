/**
 * Motor_HBridge.cpp - Library for bidirectional PWM DC brushed motor control
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


#include "Arduino.h"
#include "Motor_HBridge.h"


/**
 * Initializes a MotorHB object - empty constructor
 */
MotorHB::MotorHB()
{
    this->attached = false;
}



/**
 * Initializes a MotorHB object
 *
 * @param pin1    Drive pin 1
 * @param pin2    Drive pin 2
 * @param pinPwm  PWM pin (EN on L293D)
 */
MotorHB::MotorHB(byte pin1, byte pin2, byte pinPwm)
{
    this->attach(pin1, pin2, pinPwm);
}



/**
 * Initializes a MotorHB object
 *
 * @param pin1      Drive pin 1
 * @param pin2      Drive pin 2
 * @param pinPwm    PWM pin (EN on L293D)
 * @param rev       Whether the motor is reversed or not
 */
MotorHB::MotorHB(byte pin1, byte pin2, byte pinPwm, bool rev)
{
    this->attach(pin1, pin2, pinPwm, rev);
}



/**
 * Attaches a motor to the specified Arduino pins
 *
 * @param pin1      Drive pin 1
 * @param pin2      Drive pin 2
 * @param pinPwm    PWM pin (EN on L293D)
 */
void MotorHB::attach(byte pin1, byte pin2, byte pinPwm)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pinPwm = pinPwm;

    pinMode(pin1, OUTPUT);
    pinMode(pinPwm, OUTPUT);

    if (pin2 != MTR_NO_PIN)
    {
        pinMode(pin2, OUTPUT);
        this->dualDrivePins = true;
    }
    else
        this->dualDrivePins = false;

    this->attached = true;
}



/**
 * Attaches a motor to the specified Arduino pins
 *
 * @param pin1      Drive pin 1
 * @param pin2      Drive pin 2
 * @param pinPwm    PWM pin (EN on L293D)
 * @param rev       Whether the motor is reversed or not
 */
void MotorHB::attach(byte pin1, byte pin2, byte pinPwm, bool rev)
{
    this->attach(pin1, pin2, pinPwm);
    this->reversed = rev;
}



/**
 * Assigns a motor power to the motor
 *
 * @param pwr       Motor power, from [-255, 255]
 */
void MotorHB::set(int pwr)
{
    if (this->attached)
    {
        if (pwr == 0)
        {
            digitalWrite(pinPwm, LOW);
            digitalWrite(pin1, LOW);

            if (this->dualDrivePins)
                digitalWrite(pin2, LOW);
        }
        else
        {
            if (pwr > 255)
                pwr = 255;
            if (pwr < -255)
                pwr = -255;
            
            bool rev = (pwr < 0) ? true : false;

            analogWrite(pinPwm, abs(pwr));

            if (!this->reversed)
            {
              digitalWrite(pin1, ! rev);

              if (this->dualDrivePins)
                digitalWrite(pin2, rev);
            }
            else
            {
              digitalWrite(pin1, rev);

              if (this->dualDrivePins)
                digitalWrite(pin2, ! rev);
            }
        }

        this->setting = pwr;
    }
}



/**
 * Returns whether or not a motor is reversed
 *
 * @return      true if the motor is reversed
 */
bool MotorHB::isReversed()
{
    return this->reversed;
}



/**
 * Reverses the motor, if specified
  *
 * @param rev   Whether the motor is to be reversed or not
 */
void MotorHB::reverse(bool rev)
{
    this->reversed = rev;
}
