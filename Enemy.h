#pragma once
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Player.h"
using namespace sf;

class Enemy {
private:
	float x;
	float y;
	float size;
	float speed;
public:
	CircleShape pl_form;

	Enemy(float X, float Y, float Size, float Speed, Color color);

	void pos(float X, float Y);

	void move(Player A, Enemy B);

	float getPlayerCoordX();

	float getPlayerCoordY();

	float getPlayerSize();

	void eatingFood(Enemy p);



};