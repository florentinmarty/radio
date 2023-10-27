#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include <ezButton.h>
const int SHORT_PRESS_TIME = 500; // 500 milliseconds
const int LONG_PRESS_TIME = 500; // 500 milliseconds


class Input{
  public: 
      Input();
      Input(int pin);
      void updateState();
      bool getRisingEdge();
      bool getFallingEdge();
      bool isShortPressed();
      bool isLongPressed();
  private:
      ezButton button = NULL;
      bool _isPressing = false;
      bool _justPressedDown = false;
      bool _justReleased = false;

      long _pressedTime = 0;
      long _releasedTime = 0;
      bool _shortPressDetected = false;
      bool _isLongDetected = false;
};

#endif