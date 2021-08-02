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

int main(){
  int dir=0;
  while(1){
    dir = leitura();
  
    // Enviar dir via CAN
    delay(3000);
  }
}

int leitura(void){
char ca;
int a; 
  scanf("%c", &ca);
  if(ca == "w"){
  a = 2; //frente
  }
  else if(ca == "a"){
  a = 3; //esquerda
  }
  else if(ca == "d"){
  a = 4; //direita
  }
  else if(ca == "s"){
  a = 5; //tras
  }
return a;

}
  
