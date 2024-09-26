#include <Stepper.h>

#define b1 8
#define b2 9
#define b3 10
#define b4 11
#define c1 2
#define c2 3
#define c3 4
#define c4 5

String inputString = "";
int passosPorVolta = 32;
int leitura_VRX, leitura_VRY, leitura_botao;
bool canetaCima = true;

Stepper mp_cima(passosPorVolta, c1, c3, c2, c4);
Stepper mp_baixo(passosPorVolta, b1, b3, b2, b4);

void setup() {
  pinMode(12, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(13, INPUT_PULLUP);
}

void loop() {
  leitura_VRX = analogRead(A0);
  if (leitura_VRX > 0 && leitura_VRX < 2000) {
    motor_baixo(500, 1);
  } else if (leitura_VRX > 3000) {
    motor_baixo(500, -1);
  }

  leitura_VRY = analogRead(A1);
  if (leitura_VRY > 0 && leitura_VRY < 2000) {
    motor_cima(500, 1);
  } else if (leitura_VRY > 3000) {
    motor_cima(500, -1);
  }

  leitura_botao = digitalRead(13);
  if (leitura_botao == 0 && canetaCima) {
    caneta_baixo();
    canetaCima = false;
  } else if (leitura_botao == 0 && !canetaCima) {
    caneta_cima();
    canetaCima = true;
  }
}

void motor_baixo(int vel, int passos) {
  mp_baixo.setSpeed(vel);
  mp_baixo.step(passos);
}

void motor_cima(int vel, int passos) {
  mp_cima.setSpeed(vel);
  mp_cima.step(passos);
}

void caneta_cima() {
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(12, HIGH);

  delay(70);

  digitalWrite(6, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);
}

void caneta_baixo() {
  digitalWrite(6, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, HIGH);

  delay(80);

  digitalWrite(6, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);
}