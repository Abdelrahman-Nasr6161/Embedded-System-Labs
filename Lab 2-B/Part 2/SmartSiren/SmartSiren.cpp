#include "Arduino.h"
#include "SmartSiren.h"

SmartSiren::SmartSiren(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _mode = 0;
  _previousMillis = 0;
  _toneValue = 500;
  _rising = true;
}

void SmartSiren::fire()
{
  _mode = 1;
}

void SmartSiren::ambulance()
{
  _mode = 2;
}

void SmartSiren::police()
{
  _mode = 3;
}

void SmartSiren::stop()
{
  _mode = 0;
  noTone(_pin);
}

void SmartSiren::update()
{
  unsigned long currentMillis = millis();

  if (_mode == 0) return;

  if (currentMillis - _previousMillis >= 10)
  {
    _previousMillis = currentMillis;

    if (_mode == 1) // Fire
    {
      if (_rising) _toneValue += 10;
      else _toneValue -= 10;

      if (_toneValue >= 1200) _rising = false;
      if (_toneValue <= 400) _rising = true;

      tone(_pin, _toneValue);
    }

    if (_mode == 2) // Ambulance
    {
      static bool toggle = false;
      if (currentMillis - _previousMillis >= 500)
      {
        toggle = !toggle;
        tone(_pin, toggle ? 800 : 1200);
      }
    }

    if (_mode == 3) // Police
    {
      tone(_pin, (_toneValue % 2 == 0) ? 1000 : 600);
      _toneValue++;
    }
  }
}