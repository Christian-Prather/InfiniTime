#pragma once

#include <lvgl/lvgl.h>
#include "port/TouchPanel.h"

namespace Pinetime {
  namespace Drivers {
    class St7789;
  }

  namespace Components {
    class LittleVgl {
    public:
      enum class FullRefreshDirections { None, Up, Down, Left, Right, LeftAnim, RightAnim };
      LittleVgl(Pinetime::Drivers::St7789& lcd, Pinetime::Drivers::TouchPanel& touchPanel);

      LittleVgl(const LittleVgl&) = delete;
      LittleVgl& operator=(const LittleVgl&) = delete;
      LittleVgl(LittleVgl&&) = delete;
      LittleVgl& operator=(LittleVgl&&) = delete;

      void Init();

      void FlushDisplay(const lv_area_t* area, lv_color_t* color_p);
      bool GetTouchPadInfo(lv_indev_data_t* ptr);
      void SetFullRefresh(FullRefreshDirections direction);
      void SetNewTouchPoint(uint16_t x, uint16_t y, bool contact);

      bool GetFullRefresh() {
        bool returnValue = fullRefresh;
        if (fullRefresh) {
          fullRefresh = false;
        }
        return returnValue;
      }

    private:
      void InitDisplay();
      void InitTouchpad();
      void InitTheme();

      Pinetime::Drivers::St7789& lcd;
      Pinetime::Drivers::TouchPanel& touchPanel;

      lv_disp_buf_t disp_buf_2;
      lv_color_t buf2_1[LV_HOR_RES_MAX * 4];
      lv_color_t buf2_2[LV_HOR_RES_MAX * 4];

      lv_disp_drv_t disp_drv;

      bool fullRefresh = false;
      static constexpr uint8_t nbWriteLines = 4;
      static constexpr uint16_t totalNbLines = 320;
      static constexpr uint16_t visibleNbLines = 240;
      static constexpr uint8_t MaxScrollOffset() {
        return LV_VER_RES_MAX - nbWriteLines;
      }
      FullRefreshDirections scrollDirection = FullRefreshDirections::None;
      uint16_t writeOffset = 0;
      uint16_t scrollOffset = 0;

      uint16_t tap_x = 0;
      uint16_t tap_y = 0;
      bool tapped = false;
    };
  }
}
