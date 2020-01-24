
#include "MotorController.h"
#include "pid.h"

class SliderController
{
  
public:
  SliderController(double Kp, double Ki, double Kd);

  void loop();
  void sendToNewPosition(double position);
private:

  double mDesiredPosition;
  double mCurrentPosition;
  double mMotorSpeed;
  double mKp;
  double mKi;
  double mKd;

  int mPotPin;
  double mPotMax, mPotMin;

  MotorController mMotor;
  PID mPid;

  void readCurrentPosition();
};

