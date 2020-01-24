/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/david/Documents/BlindsAutomation/src/BlindsControl.ino"
/*
 * Project BlindsControl
 * Description:
 * Author:
 * Date:
 */

#include "BlindController.h"
#include "SliderController.h"

void setup();
void loop();
void closeEventHandler(const char *event, const char *data);
void openEventHandler(const char *event, const char *data);
#line 11 "c:/Users/david/Documents/BlindsAutomation/src/BlindsControl.ino"
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
}

void openEventHandler(const char *event, const char *data)
{
  Particle.publish("blind-opening", "", 60, PRIVATE);
  gBlindController.setBlindPosition(0);
}
