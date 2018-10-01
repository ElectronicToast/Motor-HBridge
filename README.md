# Motor-HBridge
Arduino library for bidirectional PWM control of brushed motors

## Description
This is a simple Arduino library for bidirectional control of brushed DC motors with PWM using a L239D or similar H-bridge. 

## Installation
Copy the `Motor_HBridge` directory to the Arduino IDE libraries path.

## Use
Motors are encapsulated as `MotorHB` objects. Call `MotorHB()` to instantiate an empty `MotorHB` object. The digital input and PWM pins of the H-bridge may be set with `MotorHB.attach()` or with the constructor. An optional argument is present to reverse the motor direction. 

Call `MotorHB.set()` with an integer argument from -255 to 255 to set the motor speed. 

### Examples
- `MotorHB (7, 8, 9);` Sets up a motor with an H-bridge with digital inputs from pins 7 and 8, and PWM input from pin 9.
- `MotorHB (7, MTR_NO_PIN, 9, MTR_REVERSED);` Sets up a motor with an H-bridge with a single digital input from pin 7 and PWM input from pin 9. The motor direction is reversed.

### Notes
This library depends on the built-in Arduino PWM `analogWrite()` functionality. Therefore, ensure that other timer-dependent code does not conflict with the timer used for motor control.

## Author
- Ray Sun - Undergraduate, Electrical Engineering, Caltech, Class of 2020

## License
This software is licensed under the terms of the MIT license.
