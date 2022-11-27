#pragma once
#include "SFML/Graphics.hpp"
#include "View.h"
#include "Globals.h"

class Player {
private:
	float x;
	float y;
	float size;
	float speed;

public:

	Player(float X, float Y, float Size, float Speed, Color color);

	CircleShape pl_form;

	void move();

	float getPlayerCoordX();

	float getPlayerCoordY();

	float getPlayerSize();

	void eatingFood(Player p);

};
