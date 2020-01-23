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
#include "pid.h"

void setup();
void loop();
void closeEventHandler(const char *event, const char *data);
void openEventHandler(const char *event, const char *data);
#line 11 "c:/Users/david/Documents/BlindsAutomation/src/BlindsControl.ino"
BlindController gBlindController(2, 5, 1);

void setup() 
{
  Particle.subscribe("CloseBlinds", closeEventHandler, ALL_DEVICES);
  Particle.subscribe("OpenBlinds", openEventHandler, ALL_DEVICES);

  gBlindController.setup();
}

void loop() 
{
  gBlindController.loop();
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
