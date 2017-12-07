#include "ball.h"

Layer ballLayer = {(AbShape *) &circle2, {(screenWidth / 2) + 10, (screenHeight / 2) + 5}, {0,0}, {0,0}, COLOR_YELLOW, 0};

Ball b = {&ballLayer};

Ball *ball = &b;

void ballDraw() {
  int row, column;
  Region bound;

  abShapeGetBounds(ball->ballLayer->abShape, &ball->ballLayer->pos, &bound);
  lcd_setArea(bound.topLeft.axes[0], bound.topLeft.axes[1], bound.botRight.axes[0], bound.botRight.axes[1]);

  for (row = bound.topLeft.axes[1]; row <= bound.botRight.axes[1]; row++) {
    for (column = bound.topLeft.axes[0]; column <= bound.botRight.axes[0]; column++) {
      lcd_writeColor(ball->ballLayer->color);
    }
  }
}

void ballReturn(Vec2* newPos) {
  ball->ballLayer->pos.axes[0] = newPos->axes[0];
  ball->ballLayer->pos.axes[1] = newPos->axes[1];
  ballDraw();
}

