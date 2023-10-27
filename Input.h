#include "Arduino.h"
#include "SoftwareSerial.h"
#define PRESSED 0
#define RELEASED 1

class Input{
  public: 
      Input();
      Input(int pin);
      void updateState();
      bool getRisingEdge();
      bool getFallingEdge();
      bool isPressed();
  private:
      int _pin;
      int _oldState = RELEASED;
      int _state = RELEASED;
      int _justReleased = false;
      int _justPressedDown = false;
      long _pressed_time = 0;
      long _released_time = 0;
      bool _longPress = false;
};