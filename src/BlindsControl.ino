/*
 * Project BlindsControl
 * Description:
 * Author:
 * Date:
 */

#include "BlindController.h"
#include "SliderController.h"

BlindController gBlindController(2, 5, 1);
SliderController gSliderController(2, 5, 1);

int MotorEnablePin = D4;

void setup() 
{
  Particle.subscribe("CloseBlinds", closeEventHandler, ALL_DEVICES);
  Particle.subscribe("OpenBlinds", openEventHandler, ALL_DEVICES);

  gBlindController.setup();

  pinMode(MotorEnablePin, OUTPUT);
  digitalWrite(MotorEnablePin, HIGH);
  Serial.begin();
  Serial.println("Device init complete");
}

void loop() 
{
  gBlindController.loop();
  gSliderController.loop();
}

void closeEventHandler(const char *event, const char *data)
{
  Particle.publish("blind-closing", "", 60, PRIVATE);
  gBlindController.setBlindPosition(100);
  gSliderController.sendToNewPosition(100);
}

void openEventHandler(const char *event, const char *data)
{
  Particle.publish("blind-opening", "", 60, PRIVATE);
  gBlindController.setBlindPosition(0);
  gSliderController.sendToNewPosition(0);
}
