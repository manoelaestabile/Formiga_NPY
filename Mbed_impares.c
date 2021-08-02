#include "mbed.h"
#include "math.h"
#include "Servo.h"

// Criacao dos servos

// Perna 1
Servo P1_SERVO_LEV; // servo elevacao
Servo P1_SERVO_ROT; // servo rotacao
// Perna 3  
Servo P3_SERVO_LEV; // servo elevacao
Servo P3_SERVO_ROT; // servo rotacao
// Perna 5
Servo P5_SERVO_LEV; // servo elevacao
Servo P5_SERVO_ROT; // servo rotacao

// Angulos para controlar os movimentos das pernas (incrementos)

int P1_LEV_SUBIR = 0;
int P1_ROT_AVANCAR = 0;
int P1_LEV_DESCER = 0;
int P1_ROT_RECUAR = 0;

// Elementos de defasagem do movimento das pernas
boolean P1_SINC = LOW;
boolean P2_SINC = LOW;

// Parametros para controlar o movimento das pernas
int dir = 0; // valor enviado por CAN
int speedV = 30;

// Configuracao e definicao da pinagem dos motores
void setup() {

//
// Config da CAN
//        
  // Perna 1
  Servo P1_SERVO_LEV(p21);
  Servo P1_SERVO_ROT(p22);
  // Perna 3
  Servo P3_SERVO_LEV(p23);
  Servo P3_SERVO_ROT(p24);
  // Perna 5
  Servo P5_SERVO_LEV(p25);
  Servo P5_SERVO_RO(p26);

//
//Deslocamento para Posicao Inicial
//
  // Perna 1
  P1_SERVO_LEV.write(60);
  P1_SERVO_ROT.write(100);
  // Perna 3
  P3_SERVO_LEV.write(50);
  P3_SERVO_ROT.write(80);
  // Perna 5
  P5_SERVO_LEV.write(80);
  P5_SERVO_ROT.write(25);


  delay(3000);
}
void loop() {
// 
// Buscar pela Comunicação CAN
//
  if
    // Para frente
    if (dir == 2) {
      moveLeg1();
      moveLeg3();
      moveLeg5();
    }
    // Girar para esquerda
    if (dir == 3) {
      moveLeg1();
      moveLeg3();
      moveLeg5Left();
    }
    // Girar para direita
    if (dir == 4) {
      moveLeg1Right();
      moveLeg3Right();
      moveLeg5();
    }
    // Para tras
    if (dir == 5) {
      moveLeg1Rev();
      moveLeg3Rev();
      moveLeg5Rev();
    }
    // Posicao de repouso 
    if (dir == 0) {
      initialPosition();
    }
  }

  // Falha de comunicacao -> posicao de repouso
  else {
    dir = 0;
    initialPosition();
  }
  
  delay(speedV);
  
}


void moveLeg1() {
//    
// Movimentos com a perna no ar
//    
  // Elevar a perna
  if (P1_LEV_SUBIR <= 10) {
    P1_SERVO_LEV.write(60 - P1_LEV_SUBIR * 2);
    P1_LEV_SUBIR++;
  }
  // Girar a perna
  if (P1_ROT_AVANCAR <= 30) {
    P1_SERVO_ROT.write(100 - P1_ROT_AVANCAR);
    P1_ROT_AVANCAR++;

  }
  // Descer a perna e continuar avancando
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_SERVO_LEV.write(40 + P1_LEV_DESCER * 2);
    P1_LEV_DESCER++;
  }
//    
// Movimentos com a perna no solo
//  
  // Voltar para posição inicial
  if (P1_ROT_AVANCAR >= 30) {
    P1_SERVO_ROT.write(70 + P1_ROT_RECUAR);
    P1_ROT_RECUAR++;
    P1_SINC = HIGH;
  }
  // Zerar os contadores
  if (P1_ROT_RECUAR >= 30) {
    P1_LEV_SUBIR = 0;
    P1_ROT_AVANCAR = 0;
    P1_LEV_DESCER = 0;
    P1_ROT_RECUAR = 0;
  }
}
// Analogia Perna 3
void moveLeg3() {
  if (P1_LEV_SUBIR <= 10) {
    P3_SERVO_LEV.write(50 - P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P3_SERVO_ROT.write(80 - P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P3_SERVO_LEV.write(30 + P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P3_SERVO_ROT.write(50 + P1_ROT_RECUAR);
  }
}
// Analogia Perna 5
void moveLeg5() {
  if (P1_LEV_SUBIR <= 10) {
    P5_SERVO_LEV.write(80 + P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P5_SERVO_ROT.write(30 + P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P5_SERVO_LEV.write(100 - P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P5_SERVO_ROT.write(60 - P1_ROT_RECUAR);
  }
}
// Analogia Perna 1 Reverso
void moveLeg1Rev() {
  if (P1_LEV_SUBIR <= 10) {
    P1_SERVO_LEV.write(60 - P1_LEV_SUBIR * 2);
    P1_LEV_SUBIR++;
  }
  if (P1_ROT_AVANCAR <= 30) {
    P1_SERVO_ROT.write(70 + P1_ROT_AVANCAR);
    P1_ROT_AVANCAR++;

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_SERVO_LEV.write(40 + P1_LEV_DESCER * 2);
    P1_LEV_DESCER++;
  }
  if (P1_ROT_AVANCAR >= 30) {
    P1_SERVO_ROT.write(100 - P1_ROT_RECUAR);
    P1_ROT_RECUAR++;
    P1_SINC = HIGH;
  }
  if (P1_ROT_RECUAR >= 30) {
    P1_LEV_SUBIR = 0;
    P1_ROT_AVANCAR = 0;
    P1_LEV_DESCER = 0;
    P1_ROT_RECUAR = 0;
  }
}
// Analogia Perna 3 Reverso
void moveLeg3Rev() {
  if (P1_LEV_SUBIR <= 10) {
    P3_SERVO_LEV.write(50 - P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P3_SERVO_ROT.write(50 + P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P3_SERVO_LEV.write(30 + P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P3_SERVO_ROT.write(80 - P1_ROT_RECUAR);
  }
}
// Analogia Perna 5 Reverso
void moveLeg5Rev() {
  if (P1_LEV_SUBIR <= 10) {
    P5_SERVO_LEV.write(80 + P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P5_SERVO_ROT.write(60 - P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P5_SERVO_LEV.write(100 - P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P5_SERVO_ROT.write(30 + P1_ROT_RECUAR);
  }
}
// Analogia Perna 1 Direita
void moveLeg1Right() {
  if (P1_LEV_SUBIR <= 10) {
    P1_SERVO_LEV.write(60 - P1_LEV_SUBIR * 2);
    P1_LEV_SUBIR++;
  }
  if (P1_ROT_AVANCAR <= 30) {
    P1_SERVO_ROT.write(70 + P1_ROT_AVANCAR);
    P1_ROT_AVANCAR++;

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_SERVO_LEV.write(40 + P1_LEV_DESCER * 2);
    P1_LEV_DESCER++;
  }
  if (P1_ROT_AVANCAR >= 30) {
    P1_SERVO_ROT.write(100 - P1_ROT_RECUAR);
    P1_ROT_RECUAR++;
    P1_SINC = HIGH;
  }
  if (P1_ROT_RECUAR >= 30) {
    P1_LEV_SUBIR = 0;
    P1_ROT_AVANCAR = 0;
    P1_LEV_DESCER = 0;
    P1_ROT_RECUAR = 0;
  }
}
// Analogia Perna 3 Direita
void moveLeg3Right() {
  if (P1_LEV_SUBIR <= 10) {
    P3_SERVO_LEV.write(50 - P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P3_SERVO_ROT.write(50 + P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P3_SERVO_LEV.write(30 + P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P3_SERVO_ROT.write(80 - P1_ROT_RECUAR);
  }
}
// Analogia Perna 5 Esquerda
void moveLeg5Left() {
  if (P1_LEV_SUBIR <= 10) {
    P5_SERVO_LEV.write(80 + P1_LEV_SUBIR * 2);
  }
  if (P1_ROT_AVANCAR <= 30) {
    P5_SERVO_ROT.write(60 - P1_ROT_AVANCAR);

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P5_SERVO_LEV.write(100 - P1_LEV_DESCER * 2);
  }
  if (P1_ROT_AVANCAR >= 30) {
    P5_SERVO_ROT.write(30 + P1_ROT_RECUAR);
  }
}

// Voltar para posicao inicial
void initialPosition() {
  dir = 0;
  P1_SINC = LOW;
  P2_SINC = LOW;
  // Perna 1
  P1_SERVO_LEV.write(60);
  P1_SERVO_ROT.write(100);
  // Perna 3
  P3_SERVO_LEV.write(50);
  P3_SERVO_ROT.write(80);
  // Perna 5
  P5_SERVO_LEV.write(80);
  P5_SERVO_ROT.write(25);


  // Zerar parametros
  P1_LEV_SUBIR = 0;
  P1_ROT_AVANCAR = 0;
  P1_LEV_DESCER = 0;
  P1_ROT_RECUAR = 0;

}
