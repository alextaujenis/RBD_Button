// Arduino RBD Button Library v2.1.1 - Unit test coverage.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2016 Alex Taujenis
// MIT License

// Overview:
// To make all tests pass, this suite must run while connected to a circuit that
// acts like a push-button. A button press or release is simulated within the
// test suite by setting digital pin 3 HIGH or LOW, which is connected to a
// transistor that controls a connection from digital pin 2 to ground. This
// mimics an input_pullup button on digital pin 2 with a low-side switch.

// Test Wiring Harness - Low Side Switch:
// 1. Connect Arduino ground to the emitter of an NPN transistor
// 2. Connect Arduino digital pin 2 to the NPN collector
// 3. Connect Arduino digital pin 3 to the NPN base with a 1k resistor

#include <ArduinoUnit.h> // https://github.com/mmurdoch/arduinounit
#include <RBD_Timer.h>   // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h>  // https://github.com/alextaujenis/RBD_Button

RBD::Button button(2);

// constructor: input_pullup
  test(constructor_should_enable_input_pullup_by_default) {
    assertTrue(digitalRead(2));
  }

// setDebounceTimeout
  test(setDebounceTimeout_should_default_to_ten_milliseconds) {
    pressButton();
    assertTrue(button.onPressed());
    // bounce
    releaseButton();
    assertFalse(button.onPressed());
    delay(8);
    pressButton();
    // onPressed should have been debounced and should only fire once
    assertFalse(button.onPressed());
    testCleanup();
  }

  test(setDebounceTimeout_should_change_the_debounce_timeout) {
    button.setDebounceTimeout(20);
    pressButton();
    assertTrue(button.onPressed());
    // bounce
    releaseButton();
    assertFalse(button.onPressed());
    delay(18);
    pressButton();
    // onPressed should have been debounced and should only fire once
    assertFalse(button.onPressed());
    testCleanup();
  }

// isPressed
  test(isPressed_should_return_true_when_pressed) {
    pressButton();
    assertTrue(button.isPressed());
    testCleanup();
  }

  test(isPressed_should_return_false_when_released) {
    releaseButton();
    assertFalse(button.isPressed());
    testCleanup();
  }

// isReleased
  test(isReleased_should_return_true_when_released) {
    releaseButton();
    assertTrue(button.isReleased());
    testCleanup();
  }

  test(isReleased_should_return_false_when_pressed) {
    pressButton();
    assertFalse(button.isReleased());
    testCleanup();
  }

// onPressed
  test(onPressed_should_return_true_when_pressed) {
    pressButton();
    assertTrue(button.onPressed());
    testCleanup();
  }

  test(onPressed_should_return_false_when_released) {
    releaseButton();
    assertFalse(button.onPressed());
    testCleanup();
  }

  test(onPressed_should_return_true_only_once) {
    pressButton();
    assertTrue(button.onPressed());
    assertFalse(button.onPressed());
    assertFalse(button.onPressed());
    testCleanup();
  }

  test(onPressed_should_be_debounced) {
    pressButton();
    assertTrue(button.onPressed());
    delay(1);
    releaseButton(); // bounce
    assertFalse(button.onPressed());
    delay(1);
    pressButton();
    assertFalse(button.onPressed());
    testCleanup();
  }

  test(onPressed_should_return_true_after_the_debounce_timeout) {
    // simulate two legit button presses
    pressButton();
    assertTrue(button.onPressed());
    delay(11);
    releaseButton();
    assertFalse(button.onPressed());
    delay(11);
    pressButton();
    assertTrue(button.onPressed());
    testCleanup();
  }

// onReleased
  test(onReleased_should_return_true_when_released) {
    releaseButton();
    assertTrue(button.onReleased());
    testCleanup();
  }

  test(onReleased_should_return_false_when_pressed) {
    pressButton();
    assertFalse(button.onReleased());
    testCleanup();
  }

  test(onReleased_should_return_true_only_once) {
    releaseButton();
    assertTrue(button.onReleased());
    assertFalse(button.onReleased());
    assertFalse(button.onReleased());
    testCleanup();
  }

  test(onReleased_should_be_debounced) {
    releaseButton();
    assertTrue(button.onReleased());
    delay(1);
    pressButton(); // bounce
    assertFalse(button.onReleased());
    delay(1);
    releaseButton();
    assertFalse(button.onReleased());
    testCleanup();
  }

  test(onReleased_should_return_true_after_the_debounce_timeout) {
    // simulate two legit button releases
    releaseButton();
    assertTrue(button.onReleased());
    delay(11);
    pressButton();
    assertFalse(button.onReleased());
    delay(11);
    releaseButton();
    assertTrue(button.onReleased());
    testCleanup();
  }

// invertReading
  test(invertReading_should_flip_the_button_reading) {
    pressButton();
    assertTrue(button.isPressed());
    button.invertReading();
    assertFalse(button.isPressed());
    button.invertReading(); // toggle back to normal
    testCleanup();
  }

// setup and run tests
void setup() {
  testSetup();
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  Test::run();
}

// configure pin 3 as a simulated button
int pin = 3;

void testSetup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void testCleanup() {
  button.setDebounceTimeout(1);
  delay(2);
  releaseButton();
  button.onPressed();
  pressButton();
  button.onReleased();
  button.setDebounceTimeout(10); // reset the default debounce timeout
  delay(21);                     // wait for debounce to expire between tests
}

void pressButton() {
  digitalWrite(pin, HIGH);
}

void releaseButton() {
  digitalWrite(pin, LOW);
}