#ifndef Snakey_h_
#define Snakey_h_

#include <shape.h>
#include <stdbool.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "ball.h"

typedef struct Snakey {
  Layer* headLayer;
  Layer* tailLayer;
  Vec2* dir;
  char size;
  Vec2 parts[25];
} Snakey;

extern Snakey *snakey;

void Initiate_Snakey(void);
void Update_Snakey(void);
void Growing_Snakey(void);
void Change_Direction(char direction);
void Draw_Snakey(void);
bool Snakey_Self_Hit(void);
bool Snakey_Ball_Hit(void);
bool Snakey_Wall_Hit(Region *bound);

#endif
