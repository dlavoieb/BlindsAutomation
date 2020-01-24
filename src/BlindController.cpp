#include "application.h"
#include "BlindController.h"
#include "cstdio"
#include "vector"

BlindController::BlindController(double Kp, double Ki, double Kd) :
  mKp(Kp), mKi(Ki), mKd(Kd),
  mPidController(&mCurrentPosition, &mMotorSpeed, &mDesiredPosition, mKp, mKi, mKd, PID::DIRECT),
  mMotor(D0, D1, D7)
{
  mDesiredPosition = 0;
  mCurrentPosition = 0;
  mMotorSpeed = 0;
  mPidController.SetOutputLimits(-255, 255);
  mPidController.SetMode(PID::AUTOMATIC);
}

void BlindController::setup()
{
  Particle.variable("desired_position", mDesiredPosition);
  Particle.variable("current_position", mCurrentPosition);
  Particle.variable("motor_command", mMotorSpeed);

  Particle.function("tune_controller", &BlindController::tuneController, this);
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

int BlindController::tuneController(String iData)
{ 
  String wData(iData);

  std::vector<float> parameters;
  bool continueLoop = true;
  while(continueLoop)
  {
    int commaIndex = wData.indexOf(',');
    float currentParameter;
    if (commaIndex < 0)
    {
      currentParameter = wData.toFloat();
      continueLoop = false;
    }
    else
    {
      currentParameter = wData.substring(0, commaIndex).toFloat();
      wData = wData.substring(commaIndex + 1);    
    }
    parameters.push_back(currentParameter);
  }
  tuneControllerPrivate(parameters[0], parameters[1], parameters[2]);
  return parameters[2];
}

void BlindController::tuneControllerPrivate(double iKp, double iKi, double iKd)
{
  mKp = iKp;
  mKi = iKi;
  mKd = iKd;
  mPidController.SetTunings(mKp, mKi, mKd);

  Particle.publish("new-tuning", String::format("{Kp: %f, Ki: %f, Kd: %f}", mKp, mKi, mKd), 60, PRIVATE);
}

void BlindController::setMotorSpeed()
{
  mMotor.setSpeed(mMotorSpeed);
  mCurrentPosition += (mMotorSpeed) / 1000.0;
}

