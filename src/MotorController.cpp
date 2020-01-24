#include "application.h"
#include "MotorController.h"

MotorController::MotorController(int mode1Pin, int mode2Pin, int controlPin) : mMode1Pin(mode1Pin), mMode2Pin(mode2Pin), mControlPin(controlPin)
{
  pinMode(mMode1Pin, OUTPUT);
  pinMode(mMode2Pin, OUTPUT);
  pinMode(mControlPin, OUTPUT);

  digitalWrite(mMode1Pin, LOW);
  digitalWrite(mMode2Pin, LOW);
  digitalWrite(mControlPin, LOW);
}

void MotorController::setSpeed(int speed) 
{
  if (speed > 0)
  {
    setMode(CW);
  }
  else if (speed < 0)
  {
    setMode(CCW);
  }
  else 
  {
    setMode(STOP);
  }
  analogWrite(mControlPin, abs(speed));
}

void MotorController::setMode(Mode iMode)
{
  switch (iMode)
  {
  case STOP:
    digitalWrite(mMode1Pin, LOW);
    digitalWrite(mMode2Pin, LOW);
    break;
  case SHORT:
    digitalWrite(mMode1Pin, HIGH);
    digitalWrite(mMode2Pin, HIGH);
    break;
  case CW:
    digitalWrite(mMode1Pin, LOW);
    digitalWrite(mMode2Pin, HIGH);
    break;
  case CCW:
    digitalWrite(mMode1Pin, HIGH);
    digitalWrite(mMode2Pin, LOW);
    break;
  default:
    break;
  }
}