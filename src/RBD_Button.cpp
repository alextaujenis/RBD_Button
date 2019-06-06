// Arduino RBD Button Library v2.2.0 - Read and debounce buttons and switches.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2019 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h> // https://github.com/alextaujenis/RBD_Button

namespace RBD {
  // input pullup enabled by default
  Button::Button(int pin)
  : _debounce_timer() {
    _pin = pin;
    _inputPullup();
    setDebounceTimeout(10); // default 10 ms
  }

  // overloaded constructor to disable input pullup
  Button::Button(int pin, bool input_pullup)
  : _debounce_timer() {
    _pin = pin;
    if(input_pullup) {_inputPullup();}
    else {_disableInputPullup();}
    setDebounceTimeout(10); // default 10 ms
  }

  void Button::setDebounceTimeout(unsigned long value) {
    _debounce_timer.setTimeout(value);
  }

  bool Button::isPressed() {
    _updateState();
    if (_invert) { return !_state; }
    else { return _state; }
  }

  bool Button::isReleased() {
    return !isPressed();
  }

  bool Button::onPressed() {
    if (isPressed() && !_has_been_pressed) {
      return _has_been_pressed = true;
    }
    return false;
  }

  bool Button::onReleased() {
    if (isReleased() && !_has_been_released) {
      return _has_been_released = true;
    }
    return false;
  }

  void Button::invertReading() {
    _invert = !_invert;
  }

  // private

  void Button::_updateState() {
    if (_debounce_timer.isExpired()) {
      _temp_state = digitalRead(_pin);
      if (_state != _temp_state) { // state change
        _debounce_timer.restart();
        _state = _temp_state;
        if (_invert) {
          if (_state) { // button released
            _has_been_pressed = false;
          } else {  // button pressed
            _has_been_released = false;
          }
        } else {
          if (_state) { // button pressed
            _has_been_released = false;
          } else { // button released
            _has_been_pressed = false;
          }
        }
      }
    }
  }

  void Button::_inputPullup() {
    pinMode(_pin, INPUT_PULLUP);
  }

  void Button::_disableInputPullup() {
    pinMode(_pin, INPUT);
  }
}
