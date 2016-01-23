//Only use on Arduino Mega
#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <avr/interrupt.h>
#include "rptparser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 5;
const int pin4 = 6;

extern uint8_t x;
extern uint8_t y;
extern uint8_t slider;
extern uint8_t buttons_1to8;
extern uint8_t buttons_9to11;

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);

void setup()
{
  TCCR3B = TCCR3B & 0b11111000 | 0x04; //Set timer 3 to 122Hz
  TCCR4B = TCCR4B & 0b11111000 | 0x04; //Set timer 4 to 122Hz

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  analogWrite(pin1, 47); //47 corresponds to neutral
  analogWrite(pin2, 47);
  analogWrite(pin3, 47);
  analogWrite(pin4, 47);

  Serial.begin( 115200 );

#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );
}

void loop()
{
  Usb.Task();
  arcadeDrive(pin1, pin2, pin3, pin4, x, y);
}

uint8_t convert(uint8_t i) //Converts values from joystick's 0-255 to Jag's 20-74
{
  return i * 18 / 85 + 20;
}

void arcadeDrive(int fl, int fr, int rl, int rr, int x, int y)
{
  int left = convert(bound((255 - y) + x - 254, 127, -127) + 127);
  int right = convert(bound((255 - y) - x, 127, -127) + 127);
  analogWrite(fl, left);
  analogWrite(fr, right);
  analogWrite(rl, left);
  analogWrite(rr, right);
}

int bound(int n, int upper, int lower)
{
  if (n > upper) return upper;
  else if (n < lower) return lower;
  else return n;
}

