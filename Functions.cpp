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