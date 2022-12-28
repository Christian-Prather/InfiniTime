#include "touchhandler/TouchHandler.h"
#ifdef PINETIME_IS_RECOVERY
  #include "displayapp/DummyLittleVgl.h"
#else
  #include "displayapp/LittleVgl.h"
#endif

using namespace Pinetime::Controllers;
using namespace Pinetime::Applications;

namespace {
  TouchEvents ConvertGesture(Pinetime::Drivers::TouchPanels::Gestures gesture) {
    switch (gesture) {
      case Pinetime::Drivers::TouchPanels::Gestures::SingleTap:
        return TouchEvents::Tap;
      case Pinetime::Drivers::TouchPanels::Gestures::LongPress:
        return TouchEvents::LongTap;
      case Pinetime::Drivers::TouchPanels::Gestures::DoubleTap:
        return TouchEvents::DoubleTap;
      case Pinetime::Drivers::TouchPanels::Gestures::SlideRight:
        return TouchEvents::SwipeRight;
      case Pinetime::Drivers::TouchPanels::Gestures::SlideLeft:
        return TouchEvents::SwipeLeft;
      case Pinetime::Drivers::TouchPanels::Gestures::SlideDown:
        return TouchEvents::SwipeDown;
      case Pinetime::Drivers::TouchPanels::Gestures::SlideUp:
        return TouchEvents::SwipeUp;
      case Pinetime::Drivers::TouchPanels::Gestures::None:
      default:
        return TouchEvents::None;
    }
  }
}

TouchHandler::TouchHandler(Pinetime::Drivers::TouchPanel& touchPanel, Components::LittleVgl& lvgl) : touchPanel {touchPanel}, lvgl {lvgl} {
}

void TouchHandler::CancelTap() {
  if (info.touching) {
    isCancelled = true;
    lvgl.SetNewTouchPoint(-1, -1, true);
  }
}

Pinetime::Applications::TouchEvents TouchHandler::GestureGet() {
  auto returnGesture = gesture;
  gesture = Pinetime::Applications::TouchEvents::None;
  return returnGesture;
}

bool TouchHandler::GetNewTouchInfo() {
  info = touchPanel.GetTouchInfo();

  if (!info.isValid) {
    return false;
  }

  if (info.gesture != Pinetime::Drivers::TouchPanels::Gestures::None) {
    if (gestureReleased) {
      if (info.gesture == Pinetime::Drivers::TouchPanels::Gestures::SlideDown ||
          info.gesture == Pinetime::Drivers::TouchPanels::Gestures::SlideLeft ||
          info.gesture == Pinetime::Drivers::TouchPanels::Gestures::SlideUp ||
          info.gesture == Pinetime::Drivers::TouchPanels::Gestures::SlideRight ||
          info.gesture == Pinetime::Drivers::TouchPanels::Gestures::LongPress) {
        if (info.touching) {
          gesture = ConvertGesture(info.gesture);
          gestureReleased = false;
        }
      } else {
        gesture = ConvertGesture(info.gesture);
      }
    }
  }

  if (!info.touching) {
    gestureReleased = true;
  }

  return true;
}

void TouchHandler::UpdateLvglTouchPoint() {
  if (info.touching) {
    if (!isCancelled) {
      lvgl.SetNewTouchPoint(info.x, info.y, true);
    }
  } else {
    if (isCancelled) {
      lvgl.SetNewTouchPoint(-1, -1, false);
      isCancelled = false;
    } else {
      lvgl.SetNewTouchPoint(info.x, info.y, false);
    }
  }
}
