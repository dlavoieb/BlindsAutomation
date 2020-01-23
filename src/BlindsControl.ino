/*
 * Project BlindsControl
 * Description:
 * Author:
 * Date:
 */

#include "BlindController.h"
#include "pid.h"

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
