#include "Player.h"

using namespace sf;

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

//void Player::eatingEnemy(Player& p, Enemy& e) {
//
//	float X1 = p.getPlayerCoordX();
//	float Y1 = p.getPlayerCoordY();
//	float X2 = e.getPlayerCoordX();
//	float Y2 = e.getPlayerCoordY();
//	float S1 = p.getPlayerSize();
//	float S2 = e.getPlayerSize();
//
//	if (S1 > S2) {
//		if ((((X2 >= X1 - S1) && (X2 <= X1)) || ((X2 <= X1 + S1) && (X2 >= X1))) &&
//			(((Y2 >= Y1 - S1) && (Y2 <= Y1)) || ((Y2 <= Y1 + S1) && (Y2 >= Y1))))
//			e.life = false;
//	}
//
//	if (S2 > S1) {
//		if ((((X2 >= X1 - S1) && (X2 <= X1)) || ((X2 <= X1 + S1) && (X2 >= X1))) &&
//			(((Y2 >= Y1 - S1) && (Y2 <= Y1)) || ((Y2 <= Y1 + S1) && (Y2 >= Y1))))
//			p.life = false;
//	}
//}