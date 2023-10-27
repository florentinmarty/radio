#include "Input.h"

Input::Input() {}

Input::Input(int pinToSet) {
  ezButton tempButton(pinToSet);
  button = tempButton;
  button.setDebounceTime(50);
  //pinMode(_pin, INPUT);
  //digitalWrite(_pin, HIGH);

}

void Input::updateState() {
  button.loop();
  _shortPressDetected = false;
  _justPressedDown = button.isPressed();
  _justReleased = button.isReleased();


  if (_justPressedDown) {
    _pressedTime = millis();
    _isPressing = true;
    _isLongDetected = false;
  } else if(_justReleased)
  {
    _isPressing = false;
    _releasedTime = millis();

    long pressDuration = _releasedTime - _pressedTime;
    if (pressDuration < SHORT_PRESS_TIME){
      _shortPressDetected = true;
    }
  }

  if(_isPressing && !_isLongDetected){
    long pressDuration = millis() - _pressedTime;
    if( pressDuration > LONG_PRESS_TIME ) {
        _isLongDetected = true;
      }
  }
}

bool Input::getFallingEdge() {
  return _justPressedDown;
}

bool Input::getRisingEdge() {
  return _justReleased;
}

bool Input::isShortPressed() {
  return _shortPressDetected;  

}
bool Input::isLongPressed() {
  return _isLongDetected;  

}