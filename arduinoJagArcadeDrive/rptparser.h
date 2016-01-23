#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <hid.h>

struct GamePadEventData
{
  uint8_t x;
  uint8_t y;
  uint8_t slider;
  uint8_t buttons_1to8;
  uint8_t buttons_9to11;
};

class JoystickEvents
{
  public:
    virtual void OnGamePadChanged(const GamePadEventData *evt);
};

#define RPT_GAMEPAD_LEN	sizeof(GamePadEventData)/sizeof(uint8_t)

class JoystickReportParser : public HIDReportParser
{
    JoystickEvents		*joyEvents;

    uint8_t oldPad[RPT_GAMEPAD_LEN];

  public:
    JoystickReportParser(JoystickEvents *evt);

    virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__
