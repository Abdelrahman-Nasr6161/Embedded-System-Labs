#ifndef SmartSiren_h
#define SmartSiren_h

#include "Arduino.h"

class SmartSiren
{
  public:
    SmartSiren(uint8_t pin);

    void fire();
    void ambulance();
    void police();
    void stop();
    void update();

  private:
    uint8_t _pin;
    unsigned long _previousMillis;
    int _mode;
    int _toneValue;
    bool _rising;
};

#endif