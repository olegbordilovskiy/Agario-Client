#include "Player.h"

using namespace sf;

void Player::move() {

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (getPlayerCoordX() - speed - size > 0) x -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (getPlayerCoordX() + speed + size < mapWidth) x += speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (getPlayerCoordY() - speed - size > 0) y -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (getPlayerCoordY() + speed + size < mapHeight) y += speed;

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
		if (((foodArr[i].x >= p.getPlayerCoordX() - p.getPlayerSize() * 1.1 && foodArr[i].x <= p.getPlayerCoordX()) || (foodArr[i].x <= p.getPlayerCoordX() + p.getPlayerSize() / 1.1 && foodArr[i].x >= p.getPlayerCoordX()))
			&& ((foodArr[i].y >= p.getPlayerCoordY() - p.getPlayerSize() * 1.2 && foodArr[i].y <= p.getPlayerCoordY()) || (foodArr[i].y <= p.getPlayerCoordY() + p.getPlayerSize() / 1.2 && foodArr[i].y >= p.getPlayerCoordY())) && foodArr[i].life == true) 
		{
			foodArr[i].x = rand() % 900 + 50;
			foodArr[i].y = rand() % 900 + 50;
			foodArr[i].color = colorArray[rand() % 5];
			size += 0.15;
			pl_form.setRadius(size);
		}
	}
}
