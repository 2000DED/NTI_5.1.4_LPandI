#include "Step.h"

void Motor::setMotor(float maxium, int stp, float coefficient, int StepD = 800, bool TurnDirection = 1, float S = 0)
{
  stepsPerTurn = stp;
  k = coefficient;
  Dir = TurnDirection;
  min_step_delay = StepD;
  lenA = (maxium / k) * stepsPerTurn;
  posA = (S / k) * stepsPerTurn;
  pos = posA;

  pinMode(_pin_E, OUTPUT);
  pinMode(_pin_Step, OUTPUT);
  pinMode(_pin_Dir, OUTPUT);
  digitalWrite(_pin_E, 0);
  digitalWrite(_pin_Dir, Dir);
}

void Motor::setPins(int motor_pin_Step, int motor_pin_Dir, int motor_pin_E)
{
  _pin_Step = motor_pin_Step;
  _pin_Dir = motor_pin_Dir;
  _pin_E = motor_pin_E;

  pinMode(_pin_E, OUTPUT);
  pinMode(_pin_Step, OUTPUT);
  pinMode(_pin_Dir, OUTPUT);
  digitalWrite(_pin_E, 0);
  digitalWrite(_pin_Dir, Dir);
}

float Motor::getPositionA()
{
  return ((float)posA / stepsPerTurn) * k;
}

float Motor::getPositionR()
{
  return ((float)pos / stepsPerTurn) * k;
}

void Motor::goHome()
{
  if (!coordinate_system)
  {
    setDir(!Dir);

    steps(posA);
    posA = 0;
    pos = -start;

    setDir(Dir);
  }
  else
  {
    if (pos > 0)
      setDir(!Dir);

    steps(pos);
    pos = 0;
    posA = start;

    setDir(Dir);
  }
}

void Motor::absolute()
{
  coordinate_system = 0;
}

void Motor::relative()
{
  coordinate_system = 1;
}

void Motor::goLength(int S)
{
  int number_of_steps = (S / k) * stepsPerTurn;

  if (!coordinate_system)
  {
    if (number_of_steps < posA)
      setDir(!Dir);

    if (number_of_steps <= lenA && number_of_steps >= 0)
    {
      steps(posA - number_of_steps);
      posA = number_of_steps;
      pos = posA - start;
    }

    setDir(Dir);
  }
  else
  {
    if (number_of_steps < pos)
      setDir(!Dir);

    if (start + number_of_steps <= lenA && start + number_of_steps >= 0)
    {
      steps(pos - number_of_steps);
      posA = start + number_of_steps;
      pos = number_of_steps;
    }

    setDir(Dir);
  }
}

void Motor::plusLength(int S)
{
  int number_of_steps = (S / k) * stepsPerTurn;

  check(number_of_steps);
}

void Motor::plusAngle(float a)
{
  int number_of_steps = round((a / 360.0) * stepsPerTurn);

  check(number_of_steps);
}

void Motor::plusTurn(float a)
{
  int number_of_steps = round(a * stepsPerTurn);

  check(number_of_steps);
}

void Motor::check(int k)
{
  if (k < 0)
    setDir(!Dir);

  if (posA + k <= lenA && posA + k >= 0)
  {
    steps(k);
    posA += k;
    pos += k;
  }

  setDir(Dir);
}

void Motor::zero()
{
  start = posA;
  pos = 0;
}

void Motor::setDir(bool whatDir)
{
  digitalWrite(_pin_Dir, whatDir);
}

void Motor::setSpeedPercent(float whatSpeed)
{
  whatSpeed = constrain(whatSpeed, 0, 100);
  step_delay = round(map(whatSpeed, 0, 100, MAX_STEP_DELAY, min_step_delay));
}

void Motor::steps(long kolvo_steps)
{
  for (long i = 0; i < abs(kolvo_steps); i++)
  {
    digitalWrite(_pin_Step, 1);
    digitalWrite(_pin_Step, 0);

    delayMicroseconds(step_delay);
  }
}
