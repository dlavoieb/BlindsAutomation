/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/dlboutin/source/repos/BlindsProject/BlindsControl/src/BlindsControl.ino"
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
#line 11 "c:/Users/dlboutin/source/repos/BlindsProject/BlindsControl/src/BlindsControl.ino"
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
  gBlindController.setBlindPosition(100);
}

void openEventHandler(const char *event, const char *data)
{
  gBlindController.setBlindPosition(0);
}
