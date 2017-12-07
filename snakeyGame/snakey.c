#include "snakey.h"

AbRect segmentShape = {abRectGetBounds, abRectCheck, {2,2}};

Layer tailLayer = {(AbShape *) &segmentShape, {(screenWidth / 2), (screenHeight / 2) + 5}, {0,0}, {0,0}, COLOR_BLACK, 0};

Layer headLayer = {(AbShape *) &segmentShape, {(screenWidth / 2), (screenHeight / 2)}, {(screenWidth / 2), (screenHeight / 2)}, {(screenWidth / 2), (screenHeight / 2)}, COLOR_WHITE, &tailLayer};

Vec2 dir = (Vec2){-1,0};
Vec2 parts[25];

Snakey s = {&headLayer, &tailLayer, &dir, 0, parts};

Snakey *snakey = &s;

void Initiate_Snakey() {
  snakey->headLayer->pos = (Vec2){(screenWidth / 2), (screenHeight / 2)};
  snakey->headLayer->posNext = (Vec2){(screenWidth / 2), (screenHeight / 2)};
  snakey->tailLayer->pos = (Vec2){(screenWidth / 2), (screenHeight / 2)};
  snakey->size = 0;
  for (int i = 0; i < 25; i++) {
    snakey->parts[i] = snakey->headLayer->pos;
  }
}

void Update_Snakey() {
  snakey->headLayer->posLast = snakey->headLayer->pos;
  snakey->headLayer->pos = snakey->headLayer->posNext;
  snakey->headLayer->posNext.axes[0] += 5*snakey->dir->axes[0];
  snakey->headLayer->posNext.axes[1] += 5*snakey->dir->axes[1];

  for (int i = 24; i > 0; i--) {
    snakey->parts[i] = snakey->parts[i - 1];
  }

  snakey->parts[0] = snakey->headLayer->posLast;
  snakey->tailLayer->posLast = snakey->tailLayer->pos;
  snakey->tailLayer->pos = snakey->parts[snakey->size];
}

void Change_Direction(char direction) {
  if (direction == 1 && snakey->dir->axes[0] == 0) {
    snakey->dir->axes[0] = -1;
    snakey->dir->axes[1] = 0;
  }

  else if (direction == 2 && snakey->dir->axes[1] == 0) {
    snakey->dir->axes[0] = 0;
    snakey->dir->axes[1] = -1;
  }

  else if (direction == 4 && snakey->dir->axes[1] == 0) {
    snakey->dir->axes[0] = 0;
    snakey->dir->axes[1] = 1;
  }

  else if (direction == 8 && snakey->dir->axes[0] == 0) {
    snakey->dir->axes[0] = 1;
    snakey->dir->axes[1] = 0;
  }

  snakey->headLayer->posNext.axes[0] = snakey->headLayer->pos.axes[0] + 5*snakey->dir->axes[0];
  snakey->headLayer->posNext.axes[1] = snakey->headLayer->pos.axes[1] + 5*snakey->dir->axes[1];
}

bool Snakey_Self_Hit() {
  for (int i = 0; i < snakey->size; i++) {
    if (snakey->headLayer->pos.axes[0] == snakey->parts[i].axes[0] && snakey->headLayer->pos.axes[1] == snakey->parts[i].axes[1]) {
      return true;
    }
  }

  return false;
}

bool Snakey_Ball_Hit() {
  Region bound;
  abShapeGetBounds(snakey->headLayer->abShape, &snakey->headLayer->pos, &bound);
  int row, column;
  for (row = bound.topLeft.axes[1]; row <= bound.botRight.axes[1]; row++) {
    for (column = bound.topLeft.axes[0]; column <= bound.botRight.axes[0]; column++) {
      Vec2 position = {column, row};
      if (abShapeCheck(ball->ballLayer->abShape, &ball->ballLayer->pos, &position)) {
	return true;
      }
    }
  }
  return false;
}

bool Snakey_Wall_Hit(Region* bound) {
  if (bound != 0) {
    Region snakeyBound;
    abShapeGetBounds(snakey->headLayer->abShape, &snakey->headLayer->posNext, &snakeyBound);

    for (int axis = 0; axis < 2; axis++) {
      if ((snakeyBound.topLeft.axes[axis] < bound->topLeft.axes[axis]) || (snakeyBound.botRight.axes[axis] > bound->botRight.axes[axis])) {
	  return true;
	}
    }
  }
  return false;
}

void Growing_Snakey() {
  if (snakey->size < 24) {
    snakey->size++;
  }
}

void Draw_Snakey() {
  int row, column;
  Region bound;
  layerGetBounds(snakey->headLayer, &bound);
  lcd_setArea(bound.topLeft.axes[0], bound.topLeft.axes[1], bound.botRight.axes[0], bound.botRight.axes[1]);

  for (row = bound.topLeft.axes[1]; row <= bound.botRight.axes[1]; row++) {
    for (column = bound.topLeft.axes[0]; column <= bound.botRight.axes[0]; column++) {
      lcd_writeColor(snakey->headLayer->color);
    }
  }

  layerGetBounds(snakey->tailLayer, &bound);
  lcd_setArea(bound.topLeft.axes[0], bound.topLeft.axes[1], bound.botRight.axes[0], bound.botRight.axes[1]);

  for (row = bound.topLeft.axes[1]; row <= bound.botRight.axes[1]; row++) {
    for (column = bound.topLeft.axes[0]; column <= bound.botRight.axes[0]; column++) {
      Vec2 position = {column, row};
      u_int color = snakey->tailLayer->color;
      if (abShapeCheck(ball->ballLayer->abShape, &ball->ballLayer->pos, &position)) {
	color = ball->ballLayer->color;
      }
      lcd_writeColor(color);
    }
  }
}

  
