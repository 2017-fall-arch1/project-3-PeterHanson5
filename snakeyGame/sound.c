#include <msp430.h>
#include "libTimer.h"
#include "sound.h"

void Initiate_Sound() {
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  Turn_On_Sound();
}

//allows the sound to be played
void Turn_On_Sound() {
  P2DIR |= BIT6;
}

//allows the sound to turn off
void Turn_Off_Sound() {
  P2DIR &= ~BIT6;
}

//this will tell the system what type of sound
void Sound_Of_Game(short sound) {
  CCR0 = sound;
  CCR1 = sound >> 1;
}

