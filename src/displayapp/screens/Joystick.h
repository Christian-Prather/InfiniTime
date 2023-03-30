#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include "displayapp/screens/Screen.h"

namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }

  namespace Applications {
    namespace Screens {

      class Joystick : public Screen {
      public:
        Joystick(Pinetime::Components::LittleVgl& lvgl);
        ~Joystick() override;

        void Refresh() override;

        bool OnTouchEvent(TouchEvents event) override;
        bool OnTouchEvent(uint16_t x, uint16_t y) override;

      private:
        Pinetime::Components::LittleVgl& lvgl;

        const uint8_t joystickSize = 50;
        bool notTouching = true;

        int16_t homeX = (LV_HOR_RES - joystickSize) / 2;
        int16_t homeY = (LV_VER_RES - joystickSize) / 2;

        int8_t dx = 0; // Position the ball should be at
        int8_t dy = 0; 

        lv_obj_t* joystick;
        lv_obj_t* background;

        lv_task_t* taskRefresh;
      };
    }
  }
}
