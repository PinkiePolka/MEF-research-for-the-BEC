#include <LiquidCrystal.h>

// микроэлектрофорез
const int led_a0 = A0;
const int led_a1 = A1;
const int led_a2 = A2;
const int led_a3 = A3;

// шаговые двигатели
int i1 = 0, i2 = 0, i3 = 0, t = 0;
int t12 = 14, t11 = 4, t22 = 14, t21 = 4, t32 = 14, t31 = 4;

// контакты для шаговых двигателей (ИСПРАВЛЕНО - уникальные пины)
const int gx1 = 22, gx2 = 23, gx3 = 24, gx4 = 25;  // X двигатель
const int gy1 = 26, gy2 = 27, gy3 = 28, gy4 = 29;  // Y двигатель
const int gz1 = 30, gz2 = 31, gz3 = 32, gz4 = 33;  // Z двигатель

LiquidCrystal lcd(41, 42, 43, 44, 45, 46);

float input_volt = 0.0, temp = 0.0;
const float r1 = 100000.0, r2 = 10000.0;

void setup() {
  // микроэлектрофорез
  pinMode(led_a0, OUTPUT);
  pinMode(led_a1, OUTPUT);
  pinMode(led_a2, OUTPUT);
  pinMode(led_a3, OUTPUT);
  
  // шаговые двигатели
  pinMode(gx1, OUTPUT); pinMode(gx2, OUTPUT);
  pinMode(gx3, OUTPUT); pinMode(gx4, OUTPUT);
  pinMode(gy1, OUTPUT); pinMode(gy2, OUTPUT);
  pinMode(gy3, OUTPUT); pinMode(gy4, OUTPUT);
  pinMode(gz1, OUTPUT); pinMode(gz2, OUTPUT);
  pinMode(gz3, OUTPUT); pinMode(gz4, OUTPUT);
  
  // вольтметр
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("DC DIGI VOLTMETER");
}

void loop() {
  // микроэлектрофорез
  digitalWrite(led_a0, HIGH); digitalWrite(led_a1, LOW);
  digitalWrite(led_a2, LOW);  digitalWrite(led_a3, HIGH);
  delay(6000);
  
  digitalWrite(led_a0, HIGH); digitalWrite(led_a1, LOW);
  digitalWrite(led_a2, HIGH); digitalWrite(led_a3, LOW);
  delay(4000);
  
  digitalWrite(led_a0, LOW);  digitalWrite(led_a1, HIGH);
  digitalWrite(led_a2, HIGH); digitalWrite(led_a3, LOW);
  delay(6000);
  
  digitalWrite(led_a0, HIGH); digitalWrite(led_a1, LOW);
  digitalWrite(led_a2, HIGH); digitalWrite(led_a3, LOW);
  delay(4000);
  
  // управление шаговыми двигателями
  controlStepperMotor();
  
  // вольтметр
  measureVoltage();
}

void controlStepperMotor() {
  // Мотор X (A13)
  int valX = analogRead(A13);
  if (valX > 521) {
    rotateMotorX(true);  // вправо
  } else if (valX < 489) {
    rotateMotorX(false); // влево
  }
  
  // Мотор Y (A14)
  int valY = analogRead(A14);
  if (valY > 521) {
    rotateMotorY(true);
  } else if (valY < 489) {
    rotateMotorY(false);
  }
  
  // Мотор Z (A15)
  int valZ = analogRead(A15);
  if (valZ > 521) {
    rotateMotorZ(true);
  } else if (valZ < 489) {
    rotateMotorZ(false);
  }
}

void rotateMotorX(bool clockwise) {
  t = t12;
  if (clockwise) {
    digitalWrite(gx4, HIGH); digitalWrite(gx2, LOW); delay(t);
    digitalWrite(gx3, HIGH); digitalWrite(gx1, LOW); delay(t);
    digitalWrite(gx2, HIGH); digitalWrite(gx4, LOW); delay(t);
    digitalWrite(gx1, HIGH); digitalWrite(gx3, LOW); delay(t-2);
  } else {
    digitalWrite(gx1, HIGH); digitalWrite(gx3, LOW); delay(t);
    digitalWrite(gx2, HIGH); digitalWrite(gx4, LOW); delay(t);
    digitalWrite(gx3, HIGH); digitalWrite(gx1, LOW); delay(t);
    digitalWrite(gx4, HIGH); digitalWrite(gx2, LOW); delay(t-2);
  }
  stopAllMotors();
}

void rotateMotorY(bool clockwise) {
  t = t22;
  if (clockwise) {
    digitalWrite(gy4, HIGH); digitalWrite(gy2, LOW); delay(t);
    digitalWrite(gy3, HIGH); digitalWrite(gy1, LOW); delay(t);
    digitalWrite(gy2, HIGH); digitalWrite(gy4, LOW); delay(t);
    digitalWrite(gy1, HIGH); digitalWrite(gy3, LOW); delay(t-2);
  } else {
    digitalWrite(gy1, HIGH); digitalWrite(gy3, LOW); delay(t);
    digitalWrite(gy2, HIGH); digitalWrite(gy4, LOW); delay(t);
    digitalWrite(gy3, HIGH); digitalWrite(gy1, LOW); delay(t);
    digitalWrite(gy4, HIGH); digitalWrite(gy2, LOW); delay(t-2);
  }
  stopAllMotors();
}

void rotateMotorZ(bool clockwise) {
  t = t32;
  if (clockwise) {
    digitalWrite(gz4, HIGH); digitalWrite(gz2, LOW); delay(t);
    digitalWrite(gz3, HIGH); digitalWrite(gz1, LOW); delay(t);
    digitalWrite(gz2, HIGH); digitalWrite(gz4, LOW); delay(t);
    digitalWrite(gz1, HIGH); digitalWrite(gz3, LOW); delay(t-2);
  } else {
    digitalWrite(gz1, HIGH); digitalWrite(gz3, LOW); delay(t);
    digitalWrite(gz2, HIGH); digitalWrite(gz4, LOW); delay(t);
    digitalWrite(gz3, HIGH); digitalWrite(gz1, LOW); delay(t);
    digitalWrite(gz4, HIGH); digitalWrite(gz2, LOW); delay(t-2);
  }
  stopAllMotors();
}

void stopAllMotors() {
  digitalWrite(gx1, LOW); digitalWrite(gx2, LOW);
  digitalWrite(gx3, LOW); digitalWrite(gx4, LOW);
  digitalWrite(gy1, LOW); digitalWrite(gy2, LOW);
  digitalWrite(gy3, LOW); digitalWrite(gy4, LOW);
  digitalWrite(gz1, LOW); digitalWrite(gz2, LOW);
  digitalWrite(gz3, LOW); digitalWrite(gz4, LOW);
  delay(100);
}

void measureVoltage() {
  int analogvalue = analogRead(A10);
  temp = (analogvalue * 5.0) / 1024.0;
  input_volt = temp / (r2 / (r1 + r2));
  if (input_volt < 0.1) input_volt = 0.0;
  
  Serial.print("v= ");
  Serial.println(input_volt);
  lcd.setCursor(0, 1);
  lcd.print("Voltage= ");
  lcd.print(input_volt);
  delay(300);
}