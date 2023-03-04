#include "stdio.h"
#include "stdint.h"

#ifndef AVATAR_H
#define AVATAR_H

#define AVATAR_POSY_START 90
#define AVATAR_POSX 30
#define AVATAR_WIDTH 30
#define AVATAR_LENGTH 30

#define COLOR_BACKGROUND 0x0000 // BLACK

struct Avatar {
	int posy;
	int previous_posy;
	
	int posx;
	int length;
	int width;
	int color;
	
	int step;
};

struct Obstacle {
	int posy;
	int posx;
	int length;
	int width;
	int color;
	
	int counter;
};

void initGame(struct Avatar *avatar, struct Obstacle *obstacle, int s);
void drawAvatar(struct Avatar *avatar, int s);
void moveAvatar(struct Avatar *avatar, int s);
void moveObstacle(struct Obstacle *obstacle, int a);
int lookColision(struct Avatar *avatar, struct Obstacle *obstacle);


#endif //AVATAR_H
