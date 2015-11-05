// Arduino RBD Button Library Example v1.0.1 - Debounce a button with events. INPUT_PULLUP Disabled Warning: this example requires resistors in your circuit.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h>
#include <RBD_Button.h>

// INPUT_PULLUP Disabled Warning: this example requires resistors in your circuit
RBD::Button button(2, false); // pin number, input_pullup flag

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