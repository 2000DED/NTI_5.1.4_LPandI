#include "Step.h"  // подключаем заголовок обязательно
// реализация методов
void Motor::setMotor(int motor_pin_Step, int motor_pin_Dir)
{
  _pin_Step = motor_pin_Step;
  _pin_Dir = motor_pin_Dir;

  pinMode(8, OUTPUT);
  pinMode(_pin_Step, OUTPUT);
  pinMode(_pin_Dir, OUTPUT);
  digitalWrite(8, 0);
}

void Motor::setDir(bool whatDir)
{
  digitalWrite(_pin_Dir, whatDir);
}

void Motor::setSpd(long whatSpeed)
{
  step_delay = whatSpeed;
}

void Motor::go(long kolvo_steps)
{
  for (long i = 0; i < kolvo_steps; i++)
  {
    digitalWrite(_pin_Step, 1);
    digitalWrite(_pin_Step, 0);

    delayMicroseconds(step_delay);
  }
}
