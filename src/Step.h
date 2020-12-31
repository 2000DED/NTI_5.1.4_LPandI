#pragma once
#include <Arduino.h>
#define PIN_S 2
#define PIN_D 5
#define PIN_E 8
#define STEPS_PER_TURN 200
#define MAX_STEP_DELAY 5000
#define STEP_DELAY 800
#define COF 1.245

class Motor {
  public:

    // Обявление шагового мотора(максимальная длина хода в mm, шагов в обороте, отношение mm к обороту, минимальная задержка в mcs между шагами, направление вращения, изначальная позиция)
    void setMotor(float maxium, int stp, float coefficient, int StepD = 800, bool TurnDirection = 1, float S = 0);

    // Обявление пинов шагового мотора(пин импульса, пин направления, пин включения драйвера)
    void setPins(int motor_pin_Step, int motor_pin_Dir, int motor_pin_E);

    void setSpeedPercent(float whatSpd);  // Выбор скорости в процентах

    float getPositionA(); // Возвращает позицию в абсолютной системе координат
    float getPositionR(); // Возвращает позицию в относительной системе координат

    void absolute();  // Переключение на абсолютную систему координат
    void relative();  // Переключение на относительную систему координат

    void goHome();          // Перемещение в начальную позицию
    void goLength(int S);   // Перемещение в заданную позицию

    void plusLength(int S);   // Перемещение на длину
    void plusAngle(float a);  // Перемещение на угол
    void plusTurn(float a);   // Перемещение на оборот

    void zero();  // Обнуление относительной системы координат

  private:
    void check(int k);  // Проверка на невыход за пределы абсолютной системе координат

    void setDir(bool whatDir);    // Задает направление движения мотора
    void steps(long kolvo_steps); // Шагает мотором

    bool Dir = 1;                       // Направление движения
    bool coordinate_system = 0;         // Абсолютная или относительная системе координат
    long min_step_delay = STEP_DELAY;   // Минимальная задержка в mcs между шагами
    long step_delay = STEP_DELAY;       // Задержка в mcs между шагами
    int stepsPerTurn = STEPS_PER_TURN;  // Шагов в обороте
    float k = COF;                      // Отношение mm к обороту

    long lenA = 10, posA = 0; // Максимальная длина хода в mm, Абсолютная позиция
    long start = 0, pos = 0;  // Растояние от начала абсолютной до начала относительной системы координат

    int _pin_Step = PIN_S;    // Пин импульса
    int _pin_Dir = PIN_D;     // Пин направления
    int _pin_E = PIN_E;       // Пин включения драйвера
};
