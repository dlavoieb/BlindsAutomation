#include <pid.h>

class BlindController
{

public:
  BlindController(double Kp, double Ki, double Kd);

  void setup();

  void loop();

  void setBlindPosition(int iPercent);
  double getCurrentBlindPosition();
  int tuneController(String data);
  
private:
  double mDesiredPosition;
  double mCurrentPosition;
  double mMotorSpeed;
  double mKp;
  double mKi;
  double mKd;

  int mMotorOutputPin = D7;

  PID mPidController;

  void tuneControllerPrivate(double iKp, double iKi, double iKd);
  void setMotorSpeed();
};