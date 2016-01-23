#include "rptparser.h"

uint8_t x = 127;
uint8_t y = 127;
uint8_t slider;
uint8_t buttons_1to8;
uint8_t buttons_9to11;

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
  joyEvents(evt)
{}

void JoystickReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
  bool match = true;

  // Checking if there are changes in report since the method was last called
  for (uint8_t i = 0; i < RPT_GAMEPAD_LEN; i++) {
    if ( buf[i] != oldPad[i] ) {
      match = false;
      break;
    }
  }
  // Calling Game Pad event handler
  if (!match && joyEvents) {
    joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

    for (uint8_t i = 0; i < RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
  }
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
  x = evt->x;
  y = evt->y;
  slider = evt->slider;
  buttons_1to8 = evt->buttons_1to8;
  buttons_9to11 = evt->buttons_9to11;
}
