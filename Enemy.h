#pragma once
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Player.h"
//#include "PlayerAndEnemy.h"
using namespace sf;


class Enemy {
public:
	float x;
	float y;
	float size;
	float speed;
	bool life;
	CircleShape pl_form;

	void pos(float X, float Y);

	void move(Player A, Enemy B);

	float getPlayerCoordX();

	float getPlayerCoordY();

	float getPlayerSize();

	void eatingFood(Enemy p);

};

extern Enemy enemyArr[9];