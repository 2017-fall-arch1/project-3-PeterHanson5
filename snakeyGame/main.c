#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include "snakey.h"
#include "ball.h"
#include "sound.h"

#define GREEN_LED BIT6
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void countTrack(short* counting);
void scoreTrack(char* scoringStr, short scoring);
u_int bgColor = COLOR_WHITE;
char redrawScreen = 1;

char scoring = 0;
char scoringStr[] = "0000";

AbRectOutline field = {abRectOutlineGetBounds, abRectOutlineCheck, {(screenWidth / 2) - 10, (screenHeight / 2) - 10}};

Region fence;

Layer fieldLayer = {(AbShape *) &field, {(screenWidth / 2), (screenHeight / 2)}, {0,0}, {0,0}, COLOR_BLACK, 0};

void Updating_Score() {
  scoringStr[0] = 48 + (scoring / 10);
  scoringStr[1] = 48 + (scoring % 10);
  //scoreTrack(scoringStr, scoring);
  drawString5x7(screenWidth - 32, 0, scoringStr, COLOR_BLACK, COLOR_WHITE);
}

void Update_Direction() {
  unsigned int switches = p2sw_read();
  char switchPositions = switches;
  char switchesChanged = switches >> 8;
  if (switchesChanged) {
    Turn_On_Sound();
    Sound_Of_Game(2000);
    if (!(switchPositions & SW1)) {
      Change_Direction(SW1);
    }
    else if (!(switchPositions & SW2)) {
      Change_Direction(SW2);
    }
    else if (!(switchPositions & SW3)) {
      Change_Direction(SW3);
    }

    else if (!(switchPositions & SW4)) {
      Change_Direction(SW4);
    }
  }
}

void Reset_Snakey() {
  clearScreen(COLOR_WHITE);
  Initiate_Snakey();

  abShapeGetBounds((AbShape *) &field, &fieldLayer.pos, &fence);

  layerInit(&fieldLayer);
  layerDraw(&fieldLayer);

  drawString5x7(10,0,"scoring:", COLOR_BLACK, COLOR_WHITE);

  scoring = 0;
  scoringStr[0] = '0';
  scoringStr[1] = '0';
  Updating_Score();
}

void main() {
  P1DIR |= GREEN_LED;
  P1OUT |= GREEN_LED;

  fieldLayer.next = ball->ballLayer;
  ball->ballLayer->next = snakey->headLayer;

  configureClocks();
  lcd_init();
  Initiate_Sound();
  p2sw_init(15);

  Reset_Snakey();
  enableWDTInterrupts();
  or_sr(0x8);
}

void wdt_c_handler() {
  static short counting = 0;
  static short cycles = 50;
  P1OUT |= GREEN_LED;

  if (counting % 10 == 0) {
    Update_Direction();
  }
  if (counting == cycles) {
    Turn_Off_Sound();
    if (Snakey_Wall_Hit(&fence) || Snakey_Self_Hit()) {
      Turn_On_Sound();
      Sound_Of_Game(9000);
      Reset_Snakey();
      cycles = 85;
    }
    else {
      if (Snakey_Ball_Hit()) {
	Turn_On_Sound();
	Sound_Of_Game(2000);
	scoring++;
	Updating_Score();

	if (scoring == 25) {
	  Turn_On_Sound();
	  Sound_Of_Game(3000);
	  Reset_Snakey();
	  cycles = 85;
	}

	else {
	  Growing_Snakey();
	  Update_Snakey();
	  ballReturn(&snakey->parts[snakey->size]);
	}

	if (scoring % 5 == 0) {
	  cycles -= 15;
	}
      }

	else {
	  Update_Snakey();
	}
    }
    Draw_Snakey();
    counting = 0;
  }
  //countTrack(&counting);
  counting++;
  P1OUT &= ~GREEN_LED;
}
