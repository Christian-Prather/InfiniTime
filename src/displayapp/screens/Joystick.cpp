#include "displayapp/screens/Joystick.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/LittleVgl.h"

#include <cstdlib> // for rand()

using namespace Pinetime::Applications::Screens;

Joystick::Joystick(Pinetime::Components::LittleVgl& lvgl) : lvgl {lvgl} {
  background = lv_obj_create(lv_scr_act(), nullptr);
  lv_obj_set_size(background, LV_HOR_RES + 1, LV_VER_RES);
  lv_obj_set_pos(background, -1, 0);
  lv_obj_set_style_local_radius(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_bg_color(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_obj_set_style_local_border_color(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_set_style_local_border_width(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);

  //   points = lv_label_create(lv_scr_act(), nullptr);
  //   lv_obj_set_style_local_text_font(points, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  //   lv_label_set_text_static(points, "0000");
  //   lv_obj_align(points, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 10);

  joystick = lv_obj_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_bg_color(joystick, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_set_style_local_radius(joystick, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  lv_obj_set_size(joystick, joystickSize, joystickSize);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

Joystick::~Joystick() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void Joystick::Refresh() {
  // Get current position of the finger to put the joystick there

  //   joystickX += dx;
  //   joystickY += dy;
  if (notTouching) {
    lv_obj_set_pos(joystick, homeX, homeY);
  } else {
    lv_obj_set_pos(joystick, dx, dy);
  }
}

bool Joystick::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  if (event == TouchEvents::None) {
    notTouching = true;
  } else {
    notTouching = false;
  }
  return true;
}

bool Joystick::OnTouchEvent(uint16_t x, uint16_t y) {

  dx = x;
  dy = y;
  // sets the center paddle pos. (30px offset) with the the y_coordinate of the finger
  // but clamp it such that the paddle never clips off screen
  //   if (y < 31) {
  //     lv_obj_set_pos(paddle, 0, 1);
  //   } else if (y > LV_VER_RES - 31) {
  //     lv_obj_set_pos(paddle, 0, LV_VER_RES - 61);
  //   } else {
  //     lv_obj_set_pos(paddle, 0, y - 30);
  //   }
  //   paddlePos = y;
  return true;
}
