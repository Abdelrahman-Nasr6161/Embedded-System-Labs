#include <SmartSiren.h>

SmartSiren siren(8);

unsigned long startTime;
bool sirenRunning = true;

void setup() {
  siren.fire();          // Start fire siren
  startTime = millis();  // Record start time
}

void loop() {

  if (sirenRunning) {
    siren.update();

    // Stop after 8 seconds
    if (millis() - startTime >= 8000) {
      siren.stop();
      sirenRunning = false;
    }
  }
}