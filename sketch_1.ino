#include <LiquidCrystal.h> // библиотека для работы с ЖК дисплеем

// микроэлектрофорез
int led_a0 = A0; // Порт A0
int led_a1 = A1; // Порт A1
int led_a2 = A2; // Порт A2
int led_a3 = A3; // Порт A3

//шаговые двигатели
int i1 = 0;
int i2 = 0;
int i3 = 0;
int t = 0;

int t12 = 14; 
int t11 = 4;
int t22 = 14; 
int t21 = 4;
int t32 = 14;
int t31 = 4;

//контакты для x двигателя
int gx1 = 0;
int gx2 = 1;
int gx3 = 2;
int gx4 = 3;
//контакты для z двигателя
int gz1 = 4;
int gz2 = 5;
int gz3 = 6;
int gz4 = 7;
//контакты для y двигателя
int gy1 = 8;
int gy2 = 9;
int gy3 = 10;
int gy4 = 11;

LiquidCrystal lcd( 41, 42, 43, 44, 45 ,46 ); // контакты, к которым подключен ЖК дисплей
float input_volt = 0.0;
float temp=0.0;
float r1=100000.0; //сопротивление резистора r1
float r2=10000.0; // сопротивление резистора r2

//микроэлектрофорез
void setup() 
{
  //микроэлектрофорез
  pinMode(led_a0, OUTPUT);
  pinMode(led_a1, OUTPUT);
  pinMode(led_a2, OUTPUT);
  pinMode(led_a3, OUTPUT);

  //щаговые двигатели
  //X
  pinMode(gx1, OUTPUT);
  pinMode(gx2, OUTPUT);
  pinMode(gx3, OUTPUT);
  pinMode(gx4, OUTPUT);

  //Y
  pinMode(gy1, OUTPUT);
  pinMode(gy2, OUTPUT);
  pinMode(gy3, OUTPUT);
  pinMode(gy4, OUTPUT);

  //Z
  pinMode(gz1, OUTPUT);
  pinMode(gz2, OUTPUT);
  pinMode(gz3, OUTPUT);
  pinMode(gz4, OUTPUT);

  //вольтметр
  Serial.begin(9600); // инициализируем последовательный порт связи для передачи на скорости 9600 бод/с
  lcd.begin(16, 2); // устанавливаем число столбцов и строк используемого нами ЖК дисплея
  lcd.print("DC DIGI VOLTMETER");
}
void loop() 
{
  //микроэлектрофорез
  // Отрезок 1 (6000 мс)
  digitalWrite(led_a0, HIGH); // A0 включен
  digitalWrite(led_a1, LOW);  // A1 выключен
  digitalWrite(led_a2, LOW);  // A2 выключен
  digitalWrite(led_a3, HIGH); // A3 включен
  delay(6000);
  
  // Отрезок 2 (4000 мс)
  digitalWrite(led_a0, HIGH); // A0 включен
  digitalWrite(led_a1, LOW);  // A1 выключен
  digitalWrite(led_a2, HIGH); // A2 включен
  digitalWrite(led_a3, LOW);  // A3 выключен
  delay(4000);
  
  // Отрезок 3 (6000 мс)
  digitalWrite(led_a0, LOW);  // A0 выключен
  digitalWrite(led_a1, HIGH); // A1 включен
  digitalWrite(led_a2, HIGH); // A2 включен
  digitalWrite(led_a3, LOW);  // A3 выключен
  delay(6000);
  
  // Отрезок 4 (4000 мс)
  digitalWrite(led_a0, HIGH); // A0 включен
  digitalWrite(led_a1, LOW);  // A1 выключен
  digitalWrite(led_a2, HIGH); // A2 включен
  digitalWrite(led_a3, LOW);  // A3 выключен
  delay(4000);

  //шаговые двигатели
  if (analogRead (A13) > (521)) 
  {
    t = t12;
    while (i1 < 1) 
    { //цикл для вращения мотора 1 вправо
      digitalWrite(7, HIGH); digitalWrite(5, LOW); delay(t);
      digitalWrite(6, HIGH); digitalWrite(4, LOW); delay(t);
      digitalWrite(5, HIGH); digitalWrite(7, LOW); delay(t);
      digitalWrite(4, HIGH); digitalWrite(6, LOW); delay(t - 2);
      i1++; prodlit11();
    } i1 = 0; stopPins();
  }

  if (analogRead (A13) < (489)) 
  {
    t = t12;
    while (i1 < 1) 
    { //цикл для вращения мотора 1 влево
      digitalWrite(4, HIGH); digitalWrite(6, LOW); delay(t);
      digitalWrite(5, HIGH); digitalWrite(7, LOW); delay(t);
      digitalWrite(6, HIGH); digitalWrite(4, LOW); delay(t);
      digitalWrite(7, HIGH); digitalWrite(5, LOW); delay(t - 2);
      i1++; prodlit12();
    } i1 = 0; stopPins();
  }

  if (analogRead (A14) > (521))
  {
    t = t22;
    while (i2 < 1) 
    { //цикл для вращения мотора 2 вправо
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t - 2);
      i2++; prodlit21();
    } 
    i2 = 0; stopPins();
  }
 
  if (analogRead (A14) < (489)) 
 {
    t = t22;
    while (i2 < 1) 
    { //цикл для вращения мотора 2 влево
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t - 2);
      i2++; prodlit22();
    } 
  i2 = 0; stopPins();
  if (analogRead (A15) > (521)) 
  {
    t = t32;
    while (i2 < 1) 
    { //цикл для вращения мотора 3 вправо
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t - 2);
      i2++; prodlit21();
    } 
    i2 = 0; stopPins();
  }

  if (analogRead (A15) < (489)) 
    {
      t = t32;
      while (i2 < 1) 
      { //цикл для вращения мотора 3 влево
        digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t);
        digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
        digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
        digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t - 2);
        i2++; prodlit22();
      } i2 = 0; stopPins();
    }
  }

  //вольтметр
  int analogvalue = analogRead(A10);
  temp = (analogvalue * 5.0) / 1024.0; // формула для конвертирования значения напряжения
  input_volt = temp / (r2/(r1+r2));
  if (input_volt < 0.1)
  {
    input_volt=0.0;
  }
  Serial.print("v= "); // выводим значение напряжения в окно монитора последовательной связи
  Serial.println(input_volt);
  lcd.setCursor(0, 1);
  lcd.print("Voltage= "); // выводим значение напряжения на экран ЖК дисплея
  lcd.print(input_volt);
  delay(300);
}

//шаговые двигатели
void setupShG() 
{
  //X
  pinMode(gx1, OUTPUT);
  pinMode(gx2, OUTPUT);
  pinMode(gx3, OUTPUT);
  pinMode(gx4, OUTPUT);

  //Y
  pinMode(gy1, OUTPUT);
  pinMode(gy2, OUTPUT);
  pinMode(gy3, OUTPUT);
  pinMode(gy4, OUTPUT);

  //Z
  pinMode(gz1, OUTPUT);
  pinMode(gz2, OUTPUT);
  pinMode(gz3, OUTPUT);
  pinMode(gz4, OUTPUT);
  
}

void prodlit11() 
{ //функция для продления цикла
  if (analogRead (A13) < (520)) 
  {
    i1++;
  }
  if (analogRead (A13) > (521) && analogRead (A13) < (999))
  {
    i1--;
    t = t12;
  }
  if (analogRead (A13) > (1000)) 
  {
    i1--;
    t = t11;
  }
}
void prodlit12() 
{ //функция для продления цикла
  if (analogRead (A13) > (490)) 
  {
    i1++;
  }
  if (analogRead (A13) > (51) && analogRead (A13) < (489)) 
  {
    i1--;
    t = 12;
  }
  if (analogRead (A13) < (50)) 
  {
    i1--;
    t = t11;
  }
}

void prodlit21() 
{ //функция для продления цикла
  if (analogRead (A14) < (520)) 
  {
    i2++;
  }
  if (analogRead (A14) > (521) && analogRead (A14) < (999)) 
  {
    i2--;
    t = t22;
    }
  if (analogRead (A14) > (1000)) 
  {
    i2--;
    t = t21;
  }
}
void prodlit22() { //функция для продления цикла
  if (analogRead (A14) > (490)) 
  {
    i2++;
  }
  if (analogRead (A14) > (51) && analogRead (A14) < (489)) 
  {
    i2--;
    t = t22;
  }
  if (analogRead (A14) < (50)) 
  {
    i2--;
    t = t21;
  }
}
 
void prodlit31() 
{ //функция для продления цикла
  if (analogRead (A15) < (520)) 
  {
    i2++;
  }
  if (analogRead (A15) > (521) && analogRead (A15) < (999)) 
  {
    i2--;
    t = t22;
  }
  if (analogRead (A15) > (1000)) 
  {
    i2--;
    t = t21;
  }
}
void prodlit32() 
{ //функция для продления цикла
  if (analogRead (A15) > (490)) 
  {
    i2++;
  }
  if (analogRead (A15) > (51) && analogRead (A15) < (489)) 
  {
    i2--;
    t = t22;
  }
  if (analogRead (A15) < (50)) 
  {
    i2--;
    t = t21;
  }
}

void stopPins() 
{
  digitalWrite(gx1, LOW); 
  digitalWrite(gx2, LOW); 
  digitalWrite(gx3, LOW);
  digitalWrite(gx4, LOW); 
  digitalWrite(gy1, LOW); 
  digitalWrite(gy2, LOW);
  digitalWrite(gy3, LOW); 
  digitalWrite(gy4, LOW);
  digitalWrite(gz1, LOW); 
  digitalWrite(gz2, LOW);
  digitalWrite(gz3, LOW); 
  digitalWrite(gz4, LOW); 
  delay(100);
}


void loopShG() 
{
  if (analogRead (A13) > (521)) 
  {
    t = t12;
    while (i1 < 1) 
    { //цикл для вращения мотора 1 вправо
      digitalWrite(7, HIGH); digitalWrite(5, LOW); delay(t);
      digitalWrite(6, HIGH); digitalWrite(4, LOW); delay(t);
      digitalWrite(5, HIGH); digitalWrite(7, LOW); delay(t);
      digitalWrite(4, HIGH); digitalWrite(6, LOW); delay(t - 2);
      i1++; prodlit11();
    } i1 = 0; stopPins();
  }

  if (analogRead (A13) < (489)) 
  {
    t = t12;
    while (i1 < 1) 
    { //цикл для вращения мотора 1 влево
      digitalWrite(4, HIGH); digitalWrite(6, LOW); delay(t);
      digitalWrite(5, HIGH); digitalWrite(7, LOW); delay(t);
      digitalWrite(6, HIGH); digitalWrite(4, LOW); delay(t);
      digitalWrite(7, HIGH); digitalWrite(5, LOW); delay(t - 2);
      i1++; prodlit12();
    } i1 = 0; stopPins();
  }

  if (analogRead (A14) > (521))
  {
    t = t22;
    while (i2 < 1) 
    { //цикл для вращения мотора 2 вправо
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t - 2);
      i2++; prodlit21();
    } 
    i2 = 0; stopPins();
  }
 
  if (analogRead (A14) < (489)) 
 {
    t = t22;
    while (i2 < 1) 
    { //цикл для вращения мотора 2 влево
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t - 2);
      i2++; prodlit22();
    } 
  i2 = 0; stopPins();
  if (analogRead (A15) > (521)) 
  {
    t = t32;
    while (i2 < 1) 
    { //цикл для вращения мотора 3 вправо
      digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t);
      digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
      digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
      digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t - 2);
      i2++; prodlit21();
    } 
    i2 = 0; stopPins();
  }

  if (analogRead (A15) < (489)) 
    {
      t = t32;
      while (i2 < 1) 
      { //цикл для вращения мотора 3 влево
        digitalWrite(10, HIGH); digitalWrite(12, LOW); delay(t);
        digitalWrite(11, HIGH); digitalWrite(13, LOW); delay(t);
        digitalWrite(12, HIGH); digitalWrite(10, LOW); delay(t);
        digitalWrite(13, HIGH); digitalWrite(11, LOW); delay(t - 2);
        i2++; prodlit22();
      } i2 = 0; stopPins();
    }
  }
}


//вольтметр
void setupv()
{
  Serial.begin(9600); // инициализируем последовательный порт связи для передачи на скорости 9600 бод/с
  lcd.begin(16, 2); // устанавливаем число столбцов и строк используемого нами ЖК дисплея
  lcd.print("DC DIGI VOLTMETER");
}



void loopv()
{
  int analogvalue = analogRead(A0);
  temp = (analogvalue * 5.0) / 1024.0; // формула для конвертирования значения напряжения
  input_volt = temp / (r2/(r1+r2));
  if (input_volt < 0.1)
  {
    input_volt=0.0;
  }
  Serial.print("v= "); // выводим значение напряжения в окно монитора последовательной связи
  Serial.println(input_volt);
  lcd.setCursor(0, 1);
  lcd.print("Voltage= "); // выводим значение напряжения на экран ЖК дисплея
  lcd.print(input_volt);
  delay(300);
}
