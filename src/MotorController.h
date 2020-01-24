/**
 * Class to handle TB6612FNG motor controller 
 */

#ifndef MOTOR_CONTROLLER_H__
#define MOTOR_CONTROLLER_H__

class MotorController
{

enum Mode
{
  STOP,
  CCW,
  CW,
  SHORT
};

public:
  MotorController(int mode1Pin, int mode2Pin, int controlPin);

  void setSpeed(int speed) ;

private:  
  int mMode1Pin;
  int mMode2Pin;
  int mControlPin;

  void setMode(Mode iMode);

};


#endif //  MOTOR_CONTROLLER_H__
