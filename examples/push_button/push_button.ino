// Arduino RBD Button Library Example v1.0.1 - Debounce a button with events. INPUT_PULLUP enabled.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h>
#include <RBD_Button.h>

// input pullup enabled by default
RBD::Button button(2);

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(button.onPressed()) {
    Serial.println("Button Pressed");
  }

  if(button.onReleased()) {
    Serial.println("Button Released");
  }
}