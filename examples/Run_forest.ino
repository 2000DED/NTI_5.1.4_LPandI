#include "Step.h" // Подключение библиотеки

Motor MyMotor;    // Обявляем мотор

int dr = 1;
int mode = 0;
int buff = 0;
int incumingByte = 0;
bool f = 0;

void setup() {
  Serial.begin(9600);
  // Настройка шагового мотора(максимальная длина хода в mm, шагов в обороте, отношение mm к обороту, минимальная задержка в mcs между шагами, направление вращения, изначальная позиция)
  MyMotor.setMotor(15, 200, 1.245, 800, 1, 5);

  // Обявление пинов шагового мотора(пин импульса, пин направления, пин включения драйвера)
  MyMotor.setPins(2, 5, 8);
  
  MyMotor.setSpeedPercent(90);  // Указываем скорость в процентах
}

void loop() {
    /**************Прием значений из Serial порта**************/
  while (Serial.available() > 0)
  {
    buff = int(Serial.read());
    f = 1;
    if (buff == 10)
      break;
    else if ((buff >= '0') and (buff <= '9'))
      incumingByte = incumingByte * 10 + buff - '0';
    else if (buff == '-')
      dr = -1;
    else if (buff == 'p')
      mode = 1;
    else if (buff == 'a')
      mode = 2;
    else if (buff == 't')
      mode = 3;
    else if (buff == 'o')
      mode = 4;
    else if (buff == 'r')
      mode = 5;
    else if (buff == 'z')
      mode = 6;
    else if (buff == 'h')
      mode = 7;


    Serial.println(incumingByte);
  }
  Serial.print(MyMotor.getPositionA()); // Вывод абсолютной позиции
  Serial.print("  ");
  Serial.println(MyMotor.getPositionR()); // Вывод относительной позиции
  if (f)
  {
    switch (mode)
    {
      case 0:
        MyMotor.goLength(incumingByte * dr);  // Перемещение в заданную позицию
        break;
      case 1:
        MyMotor.plusLength(incumingByte * dr);  // Перемещение на длину
        break;
      case 2:
        MyMotor.plusAngle((float)(incumingByte * dr));  // Перемещение на угол
        break;
      case 3:
        MyMotor.plusTurn((float)(incumingByte * dr));   // Перемещение на оборот
        break;
      case 4:
        MyMotor.absolute(); // Переключение на абсолютную систему координат
        break;
      case 5:
        MyMotor.relative(); // Переключение на относительную систему координат
        break;
      case 6:
        MyMotor.zero(); // Обнуление относительной системы координат
        break;
      case 7:
        MyMotor.goHome(); // Перемещение в начальную позицию
        break;
      default:
        break;
    }
  }

  f = 0;
  dr = 1;
  mode = 0;
  incumingByte = 0;
}
