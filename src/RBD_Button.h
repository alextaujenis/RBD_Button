// Arduino RBD Button Library v1.0.1 - Read and debounce buttons and switches.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef RBD_BUTTON_H
#define RBD_BUTTON_H

#include <Arduino.h>
#include <RBD_Timer.h>

namespace RBD {

  class Button {
    public:
      Button(int pin);                    // constructor: input pullup enabled by default
      Button(int pin, bool input_pullup); // overloaded constructor: flag available to disable input pullup
      void setDebounceTimeout(unsigned long value);
      void inputPullup();
      void disableInputPullup();
      void invertReading();
      void resetReading();
      bool isPressed();
      bool isReleased();
      bool onPressed();
      bool onReleased();
    private:
      int _pin;
      unsigned long _debounce_timeout = 10; // ms
      bool _has_been_pressed  = false;
      bool _has_been_released = false;
      bool _invert = true;
      bool _temp_reading;
      Timer _pressed_debounce;
      Timer _released_debounce;
  };
}
#endif