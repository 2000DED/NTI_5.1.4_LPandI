#pragma once
#include <Arduino.h>
// описание класса
class Motor {
  public:
    // constructors:
    void setMotor(int motor_pin_Step, int motor_pin_Dir);

    void setDir(bool whatDir);

    // speed setter method:
    void setSpd(long whatSpd);

    // mover method:
    void go(long kolvo_steps);

  private:

    unsigned long step_delay = 800; // delay between steps, in ms, based on speed
    long _steps = 100;

    int _pin_Step = 2;
    int _pin_Dir = 5;

};
