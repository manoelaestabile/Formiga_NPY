
#include "math.h"
#include "Servo.h"

// Criacao dos servos

// Perna 1
Servo P2_SERVO_LEV; // servo elevacao
Servo P2_SERVO_ROT; // servo rotacao
// Perna 3  
Servo P4_SERVO_LEV; // servo elevacao
Servo P4_SERVO_ROT; // servo rotacao
// Perna 5
Servo P6_SERVO_LEV; // servo elevacao
Servo P6_SERVO_ROT; // servo rotacao

// Angulos para controlar os movimentos das pernas (incrementos)

int P1_LEV_SUBIR = 0;
int P1_ROT_AVANCAR = 0;
int P1_LEV_DESCER = 0;
int P1_ROT_RECUAR = 0;

int P2_LEV_SUBIR = 0;
int P2_ROT_AVANCAR = 0;
int P2_LEV_DESCER = 0;
int P2_ROT_RECUAR = 0;

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

  // Perna 2
  Servo P2_SERVO_LEV(p21);
  Servo P2_SERVO_ROT(p22);
  // Perna 4
  Servo P4_SERVO_LEV(p23);
  Servo P4_SERVO_ROT(p24);
  // Perna 6
  Servo P6_SERVO_LEV(p25);
  Servo P6_SERVO_RO(p26);

//
//Deslocamento para Posicao Inicial
//
  // Perna 2
  P2_SERVO_LEV.write(50);
  P2_SERVO_ROT.write(75);
  // Perna 4
  P4_SERVO_LEV.write(65);
  P4_SERVO_ROT.write(40);
  // Perna 6
  P6_SERVO_LEV.write(90);
  P6_SERVO_ROT.write(60);

  delay(3000);
}
void loop() {
// 
// Buscar pela Comunicação CAN
//
  if (1)
    // Para frente
    if (dir == 2) {
      moveLeg1();
      if (P1_SINC == HIGH) {
        moveLeg2();
        moveLeg4();
        moveLeg6();
      }
    }
    // Girar para esquerda
    if (dir == 3) {
      moveLeg1();
      if (P1_SINC == HIGH) {
        moveLeg2();
        moveLeg4Left();
        moveLeg6Left();
      }
    }
    // Girar para direita
    if (dir == 4) {
      moveLeg1Right();
      if (P1_SINC == HIGH) {
        moveLeg2Right();
        moveLeg4();
        moveLeg6();
      }
    }
    // Para tras
    if (dir == 5) {
      moveLeg1Rev();
      if (P1_SINC == HIGH) {
        moveLeg2Rev();
        moveLeg4Rev();
        moveLeg6Rev();
      }
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
    P1_LEV_SUBIR++;
  }
  // Girar a perna
  if (P1_ROT_AVANCAR <= 30) {
    P1_ROT_AVANCAR++;

  }
  // Descer a perna e continuar avancando
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_LEV_DESCER++;
  }
//    
// Movimentos com a perna no solo
//  
  // Voltar para posição inicial
  if (P1_ROT_AVANCAR >= 30) {
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
// Analogia Perna 2
void moveLeg2() {
  if (P2_LEV_SUBIR <= 10) {
    P2_SERVO_LEV.write(50 - P2_LEV_SUBIR * 2);
    P2_LEV_SUBIR++;
  }
  if (P2_ROT_AVANCAR <= 30) {
    P2_SERVO_ROT.write(75 - P2_ROT_AVANCAR);
    P2_ROT_AVANCAR++;

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P2_SERVO_LEV.write(30 + P2_LEV_DESCER * 2);
    P2_LEV_DESCER++;
  }
  if (P2_ROT_AVANCAR >= 30) {
    P2_SERVO_ROT.write(45 + P2_ROT_RECUAR);
    P2_ROT_RECUAR++;
  }
  if (P2_ROT_RECUAR >= 30) {
    P2_LEV_SUBIR = 0;
    P2_ROT_AVANCAR = 0;
    P2_LEV_DESCER = 0;
    P2_ROT_RECUAR = 0;
  }
}
// Analogia Perna 4
void moveLeg4() {
  if (P2_LEV_SUBIR <= 10) {
    P4_SERVO_LEV.write(65 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P4_SERVO_ROT.write(35 + P2_ROT_AVANCAR);

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P4_SERVO_LEV.write(85 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P4_SERVO_ROT.write(65 - P2_ROT_RECUAR);
  }
}
// Analogia Perna 6
void moveLeg6() {
  if (P2_LEV_SUBIR <= 10) {
    P6_SERVO_LEV.write(90 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P6_SERVO_ROT.write(60 + P2_ROT_AVANCAR);
  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P6_SERVO_LEV.write(110 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P6_SERVO_ROT.write(90 - P2_ROT_RECUAR);
  }
}
// Analogia Perna 1 Reverso
void moveLeg1Rev() {
  if (P1_LEV_SUBIR <= 10) {
    P1_LEV_SUBIR++;
  }
  if (P1_ROT_AVANCAR <= 30) {
    P1_ROT_AVANCAR++;

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_LEV_DESCER++;
  }
  if (P1_ROT_AVANCAR >= 30) {
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
// Analogia Perna 2 Reverso
void moveLeg2Rev() {
  if (P2_LEV_SUBIR <= 10) {
    P2_SERVO_LEV.write(50 - P2_LEV_SUBIR * 2);
    P2_LEV_SUBIR++;
  }
  if (P2_ROT_AVANCAR <= 30) {
    P2_SERVO_ROT.write(45 + P2_ROT_AVANCAR);
    P2_ROT_AVANCAR++;

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P2_SERVO_LEV.write(30 + P2_LEV_DESCER * 2);
    P2_LEV_DESCER++;
  }
  if (P2_ROT_AVANCAR >= 30) {
    P2_SERVO_ROT.write(75 - P2_ROT_RECUAR);
    P2_ROT_RECUAR++;
  }
  if (P2_ROT_RECUAR >= 30) {
    P2_LEV_SUBIR = 0;
    P2_ROT_AVANCAR = 0;
    P2_LEV_DESCER = 0;
    P2_ROT_RECUAR = 0;
  }
}
// Analogia Perna 4 Reverso
void moveLeg4Rev() {
  if (P2_LEV_SUBIR <= 10) {
    P4_SERVO_LEV.write(65 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P4_SERVO_ROT.write(65 - P2_ROT_AVANCAR);

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P4_SERVO_LEV.write(85 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P4_SERVO_ROT.write(35 + P2_ROT_RECUAR);
  }
}
// Analogia Perna 6 Reverso
void moveLeg6Rev() {
  if (P2_LEV_SUBIR <= 10) {
    P6_SERVO_LEV.write(90 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P6_SERVO_ROT.write(90 - P2_ROT_AVANCAR);
  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P6_SERVO_LEV.write(110 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P6_SERVO_ROT.write(60 + P2_ROT_RECUAR);
  }
}
// Analogia Perna 1 Direita
void moveLeg1Right() {
  if (P1_LEV_SUBIR <= 10) {
    P1_LEV_SUBIR++;
  }
  if (P1_ROT_AVANCAR <= 30) {
    P1_ROT_AVANCAR++;

  }
  if (P1_ROT_AVANCAR > 20 & P1_LEV_DESCER <= 10) {
    P1_LEV_DESCER++;
  }
  if (P1_ROT_AVANCAR >= 30) {
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
// Analogia Perna 2 Direita
void moveLeg2Right() {
  if (P2_LEV_SUBIR <= 10) {
    P2_SERVO_LEV.write(50 - P2_LEV_SUBIR * 2);
    P2_LEV_SUBIR++;
  }
  if (P2_ROT_AVANCAR <= 30) {
    P2_SERVO_ROT.write(45 + P2_ROT_AVANCAR);
    P2_ROT_AVANCAR++;

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P2_SERVO_LEV.write(30 + P2_LEV_DESCER * 2);
    P2_LEV_DESCER++;
  }
  if (P2_ROT_AVANCAR >= 30) {
    P2_SERVO_ROT.write(75 - P2_ROT_RECUAR);
    P2_ROT_RECUAR++;
  }
  if (P2_ROT_RECUAR >= 30) {
    P2_LEV_SUBIR = 0;
    P2_ROT_AVANCAR = 0;
    P2_LEV_DESCER = 0;
    P2_ROT_RECUAR = 0;
  }
}
// Analogia Perna 4 Esquerda
void moveLeg4Left() {
  if (P2_LEV_SUBIR <= 10) {
    P4_SERVO_LEV.write(65 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P4_SERVO_ROT.write(60 - P2_ROT_AVANCAR);

  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P4_SERVO_LEV.write(85 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P4_SERVO_ROT.write(30 + P2_ROT_RECUAR);
  }
}
// Analogia Perna 6 Esquerda
void moveLeg6Left() {
  if (P2_LEV_SUBIR <= 10) {
    P6_SERVO_LEV.write(90 + P2_LEV_SUBIR * 2);
  }
  if (P2_ROT_AVANCAR <= 30) {
    P6_SERVO_ROT.write(90 - P2_ROT_AVANCAR);
  }
  if (P2_ROT_AVANCAR > 20 & P2_LEV_DESCER <= 10) {
    P6_SERVO_LEV.write(110 - P2_LEV_DESCER * 2);
  }
  if (P2_ROT_AVANCAR >= 30) {
    P6_SERVO_ROT.write(60 + P2_ROT_RECUAR);
  }
}

// Voltar para posicao inicial
void initialPosition() {
  dir = 0;
  P1_SINC = LOW;
  P2_SINC = LOW;
  
  // Perna 2
  P2_SERVO_LEV.write(50);
  P2_SERVO_ROT.write(75);  
  // Perna 4
  P4_SERVO_LEV.write(65);
  P4_SERVO_ROT.write(40);
  // Perna 6
  P6_SERVO_LEV.write(90);
  P6_SERVO_ROT.write(60);

  // Zerar parametros
  P1_LEV_SUBIR = 0;
  P1_ROT_AVANCAR = 0;
  P1_LEV_DESCER = 0;
  P1_ROT_RECUAR = 0;

  P2_LEV_SUBIR = 0;
  P2_ROT_AVANCAR = 0;
  P2_LEV_DESCER = 0;
  P2_ROT_RECUAR = 0;
}
