#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include "displayapp/screens/Screen.h"
#include <FreeRTOS.h>
#include <timers.h>
#include "components/ble/BleJoystick.h"

#define MAKETIMEMS(A) ((TickType_t) A * configTICK_RATE_HZ / 1000)

namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }

  namespace Applications {
    namespace Screens {

      class Joystick : public Screen {
      public:
        Joystick(Pinetime::Components::LittleVgl& lvgl, Controllers::BleJoystick& bleJoystick);
        ~Joystick() override;

        void Refresh() override;

        bool OnTouchEvent(TouchEvents event) override;
        bool OnTouchEvent(uint16_t x, uint16_t y) override;
        // static void timeout(TimerHandle_t xTimer);
        // void zeroJS();

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
        Controllers::BleJoystick& bleJoystick;

        // static TimerHandle_t one_shot_timer;
        // static const TickType_t touch_delay = MAKETIMEMS(5000);
      };
    }
  }
}
