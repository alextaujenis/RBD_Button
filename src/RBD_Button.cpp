// Arduino RBD Button Library v2.1.1 - Read and debounce buttons and switches.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2016 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h> // https://github.com/alextaujenis/RBD_Button

namespace RBD {
  // input pullup enabled by default
  Button::Button(int pin)
  : _pressed_debounce(), _released_debounce() {
    _pin = pin;
    _inputPullup();
    setDebounceTimeout(_debounce_timeout);
  }

  // overloaded constructor to disable input pullup
  Button::Button(int pin, bool input_pullup)
  : _pressed_debounce(), _released_debounce() {
    _pin = pin;
    if(input_pullup) {_inputPullup();}
    else {_disableInputPullup();}
    setDebounceTimeout(_debounce_timeout);
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
      _pressed_debounce.restart();
      if(!_has_been_pressed) {
        return _has_been_pressed = true;
      }
      return false;
    }
    // else
    if(_pressed_debounce.isExpired()) {
      return _has_been_pressed = false;
    }
    else {
      return false;
    }
  }

  bool Button::onReleased() {
    if(isReleased()) {
      _released_debounce.restart();
      if(!_has_been_released) {
        return _has_been_released = true;
      }
      return false;
    }
    // else isPressed()
    if(_released_debounce.isExpired()) {
      return _has_been_released = false;
    }
    else {
      return false;
    }
  }

  void Button::invertReading() {
    _invert = !_invert;
  }


  // private

  void Button::_inputPullup() {
    pinMode(_pin, INPUT_PULLUP);
  }

  void Button::_disableInputPullup() {
    pinMode(_pin, INPUT);
  }
}