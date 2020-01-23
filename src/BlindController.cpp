#include "application.h"
#include "BlindController.h"


BlindController::BlindController(double Kp, double Ki, double Kd) :
  mKp(Kp), mKi(Ki), mKd(Kd),
  mPidController(&mCurrentPosition, &mMotorSpeed, &mDesiredPosition, mKp, mKi, mKd, PID::DIRECT)
{
  mDesiredPosition = 0;
  mCurrentPosition = 0;
  mMotorSpeed = 0;
  // mPidController.SetOutputLimits(-255/2, 255/2);
  mPidController.SetMode(PID::AUTOMATIC);
}

void BlindController::setup()
{
  Particle.variable("desired_position", mDesiredPosition);
  Particle.variable("current_position", mCurrentPosition);
  Particle.variable("motor_command", mMotorSpeed);

  Particle.function("tune_controller", &BlindController::tuneController, this);

  pinMode(mMotorOutputPin, OUTPUT);
}

void BlindController::loop()
{
  // mCurrentPosition = getCurrentBlindPosition();
  if (mPidController.Compute())
  {
    setMotorSpeed();
  }

}

void BlindController::setBlindPosition(int iPercent)
{
  mDesiredPosition = iPercent;
}

double BlindController::getCurrentBlindPosition()
{ 
  return 0;
}

int BlindController::tuneController(String data)
{ 
  Particle.publish("tuning-updated", data, 60, PRIVATE);
  Particle.publish("tuning-updated", String::format("length: %d", data.length()), 60, PRIVATE);
  
  double wInputParameters[3] = {0, 0, 0};
  int wBeginIndex = 0;
  int wCurrentParameter = 0;

  for (int i = 0; i < data.length(); i++)
  {
    if ((data.charAt(i) == ',' || i == data.length() - 1))
    { 
      Particle.publish("character-of-interest", String::format("beginIndex: %d, i: %d, substring: %s", wBeginIndex, i, data.substring(wBeginIndex, i - 1)), 60, PRIVATE);
      if (wCurrentParameter < 3)
      {
        wInputParameters[wCurrentParameter++] = data.substring(wBeginIndex, i - 1).toFloat();
      }
      wBeginIndex = i + 1;
    }
  }

  tuneControllerPrivate(wInputParameters[0], wInputParameters[1], wInputParameters[2]);
  return wInputParameters[2];
}

void BlindController::tuneControllerPrivate(double iKp, double iKi, double iKd)
{
  mKp = iKp;
  mKi = iKi;
  mKd = iKd;
  mPidController.SetTunings(mKp, mKi, mKd);

  Particle.publish("new-tuning", String::format("{Kp: %d, Ki: %d, Kd: %d}", mKp, mKi, mKd), 60, PRIVATE);

}

void BlindController::setMotorSpeed()
{
  analogWrite(mMotorOutputPin, mMotorSpeed);
  mCurrentPosition += (mMotorSpeed-255/2) / 1000.0;
}

