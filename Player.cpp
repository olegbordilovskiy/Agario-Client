#include "Player.h"

using namespace sf;

Player::Player(float X, float Y, float Size, float Speed, Color color)
{
	x = X;
	y = Y;
	size = Size;
	speed = Speed;
	pl_form.setRadius(size);
	pl_form.setFillColor(color);
}

void Player::move() {

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (getPlayerCoordX() - speed - size > 0) x -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (getPlayerCoordX() + speed + size < map_width) x += speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (getPlayerCoordY() - speed - size > 0) y -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (getPlayerCoordY() + speed + size < map_height) y += speed;

	}
	getPlayerCoordForView(getPlayerCoordX(), getPlayerCoordY());
	pl_form.setPosition(x - size, y - size);
}

float Player::getPlayerCoordX() {
	return x;
}

float Player::getPlayerCoordY() {
	return y;
}

float Player::getPlayerSize() {
	return size;
}

void Player::eatingFood(Player p) {
	for (int i = 0; i < foodAmount; i++) {
		if (((foodCoord[i].x >= p.getPlayerCoordX() - p.getPlayerSize() * 1.1 && foodCoord[i].x <= p.getPlayerCoordX()) || (foodCoord[i].x <= p.getPlayerCoordX() + p.getPlayerSize() / 1.1 && foodCoord[i].x >= p.getPlayerCoordX()))
			&& ((foodCoord[i].y >= p.getPlayerCoordY() - p.getPlayerSize() * 1.2 && foodCoord[i].y <= p.getPlayerCoordY()) || (foodCoord[i].y <= p.getPlayerCoordY() + p.getPlayerSize() / 1.2 && foodCoord[i].y >= p.getPlayerCoordY()))) {
			foodCoord[i].x = -100;
			foodCoord[i].y = -100;
			size += 0.1;
			pl_form.setRadius(size);

		}
	}
}