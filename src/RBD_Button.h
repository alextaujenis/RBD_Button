// Arduino RBD Button Library v2.2.0 - Read and debounce buttons and switches.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2019 Alex Taujenis
// MIT License

#ifndef RBD_BUTTON_H
#define RBD_BUTTON_H

#include <Arduino.h>
#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer

namespace RBD {
  class Button {
    public:
      Button(int pin);                    // constructor: input pullup enabled by default
      Button(int pin, bool input_pullup); // overloaded constructor: flag available to disable input pullup
      void setDebounceTimeout(unsigned long value);
      bool isPressed();
      bool isReleased();
      bool onPressed();
      bool onReleased();
      void invertReading();
    private:
      int _pin;
      bool _invert = true;
      bool _temp_state = false;
      bool _state = false;
      bool _has_been_pressed  = false;
      bool _has_been_released = false;
      void _inputPullup();
      void _disableInputPullup();
      void _updateState();
      Timer _debounce_timer;
  };
}
#endif
