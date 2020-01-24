#include "application.h"
#include "SliderController.h"


// bring the slider to the desired position using a pid controller
// when close enough, disable the controller
// wait for further input, and monitor the slider position
// if slider position changes, issue new command to move the blinds
// when new blind position is commanded, activate PID loop and move slider to the same position


SliderController::SliderController(double Kp, double Ki, double Kd) : 
  mKp(Kp), mKi(Ki), mKd(Kd),
  mPotPin(A1), mPotMax(4096 ), mPotMin(0),
  mMotor(D2, D3, D8),
  mPid(&mCurrentPosition, &mMotorSpeed, &mDesiredPosition, mKp, mKi, mKd, PID::DIRECT)
{
  mDesiredPosition = 0;
  mCurrentPosition = 0;
  mMotorSpeed = 0;
  pinMode(mPotPin, INPUT_PULLDOWN);
}

double threshold = 0.5;
void SliderController::loop()
{

  readCurrentPosition();

  if (mPid.GetMode() == PID::AUTOMATIC && abs(mCurrentPosition - mDesiredPosition) < threshold)
  {
    mPid.SetMode(PID::MANUAL); // turning off the pid controller when we have reached our goal
  }

  if (mPid.GetMode() == PID::MANUAL)
  {
    // check if current position is significantly different from the last command, and if the slider stopped moving
    // issue new blind command when position of slider changed
  }


  mPid.Compute();
  mMotor.setSpeed(mMotorSpeed);

}

void SliderController::readCurrentPosition()
{
  double wReading = static_cast<double>(analogRead(mPotPin));
  mCurrentPosition = wReading / (mPotMax - mPotMin);
}

void SliderController::sendToNewPosition(double newPosition)
{
  mDesiredPosition = newPosition;
  mPid.SetMode(PID::AUTOMATIC);
}
