#include "application.h"
#include "BlindController.h"


BlindController::BlindController(double Kp, double Ki, double Kd) :
  mKp(Kp), mKi(Ki), mKd(Kd),
  mPidController(&mCurrentPosition, &mMotorSpeed, &mDesiredPosition, mKp, mKi, mKd, PID::DIRECT)
{
  mDesiredPosition = 0;
  mCurrentPosition = 0;
  mMotorSpeed = 0;
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
  mCurrentPosition = getCurrentBlindPosition();
  mPidController.Compute();
  setMotorSpeed(mMotorSpeed);
}

void BlindController::setBlindPosition(int iPercent){}
double BlindController::getCurrentBlindPosition(){ return 0;}
int BlindController::tuneController(String data){ return 0;}

void BlindController::tuneControllerPrivate(double iKp, double iKi, double iKd)
{
  mKp = iKp;
  mKi = iKi;
  mKd = iKd;
  mPidController.SetTunings(mKp, mKi, mKd);
}

void BlindController::setMotorSpeed(double iMotorSpeed)
{

}

