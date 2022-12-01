#pragma once
#include "Enemy.h"
using namespace sf;



//Enemy::Enemy(float X, float Y, float Size, float Speed, Color color) {
//	x = X;
//	y = Y;
//	size = Size;
//	speed = Speed;
//	pl_form.setRadius(size);
//	pl_form.setFillColor(color);
//}

void Enemy::pos(float X, float Y) {
	x = X;
	y = Y;
	pl_form.setPosition(x - size, y - size);
}

void Enemy::move(Player A, Enemy B) {

	float xA = A.getPlayerCoordX();
	float yA = A.getPlayerCoordY();
	float xB = B.getPlayerCoordX();
	float yB = B.getPlayerCoordY();
	float tmp;

	speed = 5 / size;

	if (B.getPlayerSize() > A.getPlayerSize())
	{
		if (abs(xA - xB) < 120 + size && abs(yA - yB) < 120 + size) {
			if (xA != xB) {
				tmp = abs(xA - xB);
				if (abs(xA - xB + 1) < tmp)
				{
					if (x - speed - size > 0)
					{
						xB -= speed;
						x = xB;
					}
				}
				tmp = abs(xA - xB);
				if (abs(xA - xB - 1) < tmp)
				{
					if (x + speed + size < map_width)
					{
						xB += speed;
						x = xB;
					}
				}
			}

			if (yA != yB)
			{
				tmp = abs(yA - yB);
				if (abs(yA - yB + 1) < tmp)
				{
					if (y - speed - size > 0)
					{
						yB -= speed;
						y = yB;
					}
				}
				tmp = abs(yA - yB);
				if (abs(yA - yB - 1) < tmp)
				{
					if (y + speed + size < map_height)
					{
						yB += speed;
						y = yB;
					}
				}
			}
		}
	}

	if (B.getPlayerSize() < A.getPlayerSize())
	{
		if (abs(xA - xB) < 120 + size && abs(yA - yB) < 120 + size)
		{
			tmp = abs(xA - xB);
			if (abs(xA - xB + 1) > tmp)
			{
				if (x - speed - size > 0)
				{
					xB -= speed;
					x = xB;
				}
			}
			tmp = abs(xA - xB);
			if (abs(xA - xB - 1) > tmp)
			{

				if (x + speed + size < map_width)
				{
					xB += speed;
					x = xB;
				}

			}
		}

		if (abs(xA - xB) < 100 && abs(yA - yB) < 100)
		{
			tmp = abs(yA - yB);
			if (abs(yA - yB + 1) > tmp)
			{
				if (y - speed - size > 0)
				{
					yB -= speed;
					y = yB;
				}
			}
			tmp = abs(yA - yB);
			if (abs(yA - yB - 1) > tmp)
			{
				if (y + speed + size < map_height)
				{
					yB += speed;
					y = yB;
				}
			}
		}
	}

	pl_form.setPosition(x - size, y - size);
}

float Enemy::getPlayerCoordX() {
	return x;
}

float Enemy::getPlayerCoordY() {
	return y;
}

float Enemy::getPlayerSize() {
	return size;
}

void Enemy::eatingFood(Enemy p) {
	for (int i = 0; i < foodAmount; i++) {
		if (((foodCoord[i].x >= (p.getPlayerCoordX() - p.getPlayerSize()) && foodCoord[i].x < p.getPlayerCoordX()) || (foodCoord[i].x <= (p.getPlayerCoordX() + p.getPlayerSize()) && foodCoord[i].x > p.getPlayerCoordX()))
			&& ((foodCoord[i].y >= (p.getPlayerCoordY() - p.getPlayerSize()) && foodCoord[i].y < p.getPlayerCoordY()) || (foodCoord[i].y <= (p.getPlayerCoordY() + p.getPlayerSize()) && foodCoord[i].y > p.getPlayerCoordY()))) {
			foodCoord[i].x = -100;
			foodCoord[i].y = -100;
			size += 0.1;
			pl_form.setRadius(size);

		}
	}
}


