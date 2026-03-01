class SmartSiren {
  public:
    SmartSiren(uint8_t pin) {
      _pin = pin;
      pinMode(_pin, OUTPUT);
      _mode = 0;
      _previousMillis = 0;
      _toneValue = 400;
      _rising = true;
    }

    void fire() { _mode = 1; }
    void ambulance() { _mode = 2; }
    void police() { _mode = 3; }
    void stop() {
      _mode = 0;
      noTone(_pin);
    }

    void update() {
      unsigned long currentMillis = millis();
      if (_mode == 0) return;

      // Fire
      if (_mode == 1) {
        if (currentMillis - _previousMillis >= 10) {
          _previousMillis = currentMillis;

          if (_rising) _toneValue += 10;
          else _toneValue -= 10;

          if (_toneValue >= 1200) _rising = false;
          if (_toneValue <= 400) _rising = true;

          tone(_pin, _toneValue);
        }
      }

      // Ambulance
      if (_mode == 2) {
        if (currentMillis - _previousMillis >= 500) {
          _previousMillis = currentMillis;
          static bool toggle = false;
          toggle = !toggle;
          tone(_pin, toggle ? 800 : 1200);
        }
      }

      // Police
      if (_mode == 3) {
        if (currentMillis - _previousMillis >= 200) {
          _previousMillis = currentMillis;
          static bool toggle = false;
          toggle = !toggle;
          tone(_pin, toggle ? 1000 : 600);
        }
      }
    }

  private:
    uint8_t _pin;
    unsigned long _previousMillis;
    int _mode;
    int _toneValue;
    bool _rising;
};


// Create siren object on pin 8
SmartSiren siren(8);
unsigned long startTime = 0;
bool started = false;

void setup() {
  startTime = millis();
  siren.fire();
  // siren.ambulance();
  // siren.police();
  started = true;
}

void loop() {

  siren.update();

  if (started && millis() - startTime >= 8000) {
    siren.stop();   // Stop after 8 seconds
    started = false;
  }
}