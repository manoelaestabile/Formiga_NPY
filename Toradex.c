#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

void main(){
  int dir=0;
  char c;
  while(1){
    dir = leitura();
  
    // Enviar dir via CAN
    delay(3000)
  }
}

int leitura(void){
  scanf("%c", $c);
  if(c == "w"){
  dir = 2; //frente
  }
  else if(c == "a"){
  dir = 3; //esquerda
  }
  else if(c == "d"){
  dir = 4; //direita
  }
  else if(c == "s"){
  dir = 5; //tras
  }
return dir;

}
  
