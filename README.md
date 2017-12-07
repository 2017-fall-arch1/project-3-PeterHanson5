# Project 3: Snakey
## Introduction

The company ACME asked for a designed game and I have presented to
them a version of snake called snakey(fun for the whole family). It follows the same rules as the classic snake game, eat as many dots as you can and grow bigger. If you hit the wall or any part of yourself, the game will end with a loss. Reach 25 points to win.

## Running
1. Run make
2. Run make load to install the game on the msp430

## Method Snakey

Initiate_Snakey();
Update_Snakey();
Growing_Snakey();
Change_Direction();
Draw_Snakey();
Snakey_Self_Hit();
Snakey_Ball_Hit();
Snakey_Wall_Hit();

## Method ball

ballReturn(Vec2* newPos);

## Method sound

Inititiate_Sound();
Turn_On_Sound();
Turn_Off_Sound();
Sound_Of_Game();