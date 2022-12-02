#include "Functions.h"

View changeZoom() {
	if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
		view.zoom(1.0100f);
		zoom += 0.05;
		lineWidth += 0.008;
	}
	if (Keyboard::isKeyPressed(Keyboard::Add)) {
		view.zoom(0.9900f);
		if (zoom > 1) {
			zoom -= 0.05;
			lineWidth -= 0.008;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
		zoom = 0;
		lineWidth = 0.2;
		view.setSize(250, 250);
	}

	return view;
}

void drawingMap() {
	background.setFillColor(Color(247, 247, 247));
	background.setOutlineThickness(5);
	background.setOutlineColor(Color(70, 130, 180));

	lines.setFillColor(Color::Red);
	lines.move(10, 90);

}

bool isItVisible(Player p, float X, float Y) {
	if (((X >= p.getPlayerCoordX() - 130 && X <= p.getPlayerCoordX()) || (X <= p.getPlayerCoordX() + 130 && X >= p.getPlayerCoordX()))
		&& ((Y >= p.getPlayerCoordY() - 130 && Y <= p.getPlayerCoordY()) || (Y <= p.getPlayerCoordY() + 130 && Y >= p.getPlayerCoordY()))) return true;
	else return false;
}

void eatingEnemy(Player &p, Enemy &e) {

	float X1 = p.getPlayerCoordX();
	float Y1 = p.getPlayerCoordY();
	float X2 = e.getPlayerCoordX();
	float Y2 = e.getPlayerCoordY();
	float S1 = p.getPlayerSize();
	float S2 = e.getPlayerSize();

	if (S1 > S2) {
		if ((((X2 >= X1 - S1) && (X2 <= X1)) || ((X2 <= X1 + S1) && (X2 >= X1))) && 
			(((Y2 >= Y1 - S1) && (Y2 <= Y1)) || ((Y2 <= Y1 + S1) && (Y2 >= Y1))))
			e.life = false;
	}
}
