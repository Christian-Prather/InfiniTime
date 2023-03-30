
#include "BleJoystick.h""
#include "HidService.h"

using namespace Pinetime::Controllers;

BleJoystick::BleJoystick(HidService& hidService) : hidService{hidService} {

}

void BleJoystick::Move(uint8_t x, uint8_t y) {
  hidService.SendJSReport(x, y);
}