// Arduino RBD Button Library v1.0.1 - Read and debounce buttons and switches.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Button.h>
#include <RBD_Timer.h>

namespace RBD {

  // input pullup enabled by default
  Button::Button(int pin)
  : _pressed_debounce(), _released_debounce() {
    _pin = pin;
    inputPullup();
    setDebounceTimeout(_debounce_timeout);
  }

  // overloaded constructor to disable input pullup
  Button::Button(int pin, bool input_pullup)
  : _pressed_debounce(), _released_debounce() {
    _pin = pin;
    if(input_pullup) {inputPullup();}
    else {disableInputPullup();}
    setDebounceTimeout(_debounce_timeout);
  }

  void Button::inputPullup() {
    pinMode(_pin, INPUT_PULLUP);
    invertReading();
  }

  void Button::disableInputPullup() {
    pinMode(_pin, INPUT);
    resetReading();
  }

  void Button::invertReading() {
    _invert = true;
  }

  void Button::resetReading() {
    _invert = false;
  }

  void Button::setDebounceTimeout(unsigned long value) {
    _debounce_timeout = value;
    _pressed_debounce.setTimeout(_debounce_timeout);
    _released_debounce.setTimeout(_debounce_timeout);
  }

  bool Button::isPressed() {
    _temp_reading = digitalRead(_pin);
    if(_invert) {return !_temp_reading;}
    else {return _temp_reading;}
  }

  bool Button::isReleased() {
    return !isPressed();
  }

  bool Button::onPressed() {
    if(isPressed()) {
      if(!_has_been_pressed && _pressed_debounce.isExpired()) {
        _pressed_debounce.restart();
        _has_been_pressed = true;
        return true;
      }
      else {
        return false;
      }
    }
    else {
      _pressed_debounce.restart();
      _has_been_pressed = false;
      return false;
    }
  }

  bool Button::onReleased() {
    if(isReleased()) {
      if(!_has_been_released && _released_debounce.isExpired()) {
        _released_debounce.restart();
        _has_been_released = true;
        return true;
      }
      else {
        return false;
      }
    }
    else {
      _released_debounce.restart();
      _has_been_released = false;
      return false;
    }
  }
}