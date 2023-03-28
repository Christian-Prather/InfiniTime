#pragma once

#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class HidService;
    class BleJoystick {
      public:
        explicit BleJoystick(HidService& hidService);

        void Move(uint8_t x, uint8_t y);

      private:
        HidService& hidService;
    };
  }
}
