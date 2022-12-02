#pragma once
#include "SFML/Graphics.hpp"
#include "View.h"
#include "Globals.h"
//#include "Enemy.h"

class Player {
private:
	float x;
	float y;
	float size;
	float speed;
	bool life;

public:
	Player(float X, float Y, float Size, float Speed, Color color);

	CircleShape pl_form;

	void move();

	float getPlayerCoordX();

	float getPlayerCoordY();

	float getPlayerSize();

	void eatingFood(Player p);

	void eatingEnemy();

};
