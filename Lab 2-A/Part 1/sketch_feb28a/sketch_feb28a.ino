#include "MAX30100.h"

MAX30100* pulseOxymeter;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  pulseOxymeter = new MAX30100();
  pinMode(2, OUTPUT);
}

void loop(){
  // 1. Update the sensor reading
  pulseoxymeter_t result = pulseOxymeter->update();
  if(result.pulseDetected){
    Serial.print("SaO2:");
    Serial.println(result.SaO2);
  }
}