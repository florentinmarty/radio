#include "Input.h"


Input::Input() {}

Input::Input(int pinToSet) {
  _pin = pinToSet;
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);

}

void Input::updateState() {
  _oldState = _state;
  _state = digitalRead(_pin);
  char buf [64];

  if (_state == PRESSED & _oldState == RELEASED) {
    _justPressedDown = true;
    _pressed_time = millis();
  } else
  {
    _justPressedDown = false;
  }

  if (_state == RELEASED & _oldState == PRESSED &!_longPress) {
    _justReleased = true;
    _released_time = millis();
  } else
  {
    _longPress = false;
    _justReleased = false;
  }

  if (_state == PRESSED) {
    _longPress = millis() -_pressed_time > 500;
    Serial.println(millis() -_pressed_time );
  } else{
    _longPress = false;
    _pressed_time = millis();
  } 

}

bool Input::getFallingEdge() {
  return _justPressedDown;
}

bool Input::getRisingEdge() {
  return _justReleased;
}

bool Input::isPressed() {
  return _longPress;  

}