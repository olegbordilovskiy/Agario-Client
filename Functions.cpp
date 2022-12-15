#include "Functions.h"

//View changeZoom(Player p) {
//	if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
//		view.zoom(1.0100f);
//		//if (zoom <= 0)
//		{
//			zoom += 0.05;
//			lineWidth += 0.0060;
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Add)) {
//		view.zoom(0.9900f);
//		if (zoom > 1) {
//			zoom -= 0.05;
//			lineWidth -= 0.006;
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
//		zoom = 0;
//		lineWidth = 0.2;
//		view.setSize(windowWidth / 4, windowHeight / 4);
//	}
//
//	return view;
//}

void drawingMap() {
	background.setFillColor(Color(247, 247, 247));
	background.setOutlineThickness(5);
	background.setOutlineColor(Color(70, 130, 180));

	lines.setFillColor(Color::Red);
	lines.move(10, 90);

}

void drawingResults() {

	resultsBackground.setFillColor(Color(240, 128, 128));
}

bool isItVisible(Player p, float X, float Y) {
	float pX = p.getPlayerCoordX();
	float pY = p.getPlayerCoordY();

	if (((X >= pX - drawingDistance && X <= pX) || (X <= pX + drawingDistance && X >= pX))
		&& ((Y >= pY - drawingDistance * 0.65 && Y <= pY) || (Y <= pY + drawingDistance * 0.65 && Y >= pY))) return true;
	else return false;
}

void eatingEnemy(Player& p, Enemy& e) {

	float X1 = p.getPlayerCoordX();
	float Y1 = p.getPlayerCoordY();
	float X2 = e.getPlayerCoordX();
	float Y2 = e.getPlayerCoordY();
	float S1 = p.getPlayerSize();
	float S2 = e.getPlayerSize();

	if (S1 > S2) {
		if ((((X2 <= X1) && (X2 >= X1 - S1)) || ((X2 >= X1) && (X2 <= X1 + S1))) &&
			(((Y2 <= Y1) && (Y2 >= Y1 - S1)) || ((Y2 >= Y1) && (Y2 <= Y1 + S1))))
		{
			if (e.life == true) p.size += e.size / 3;
			p.pl_form.setRadius(p.size);
			e.life = false;
		}
	}

	if (S1 < S2) {
		if ((((X1 <= X2) && (X1 >= X2 - S2)) || ((X1 >= X2) && (X1 <= X2 + S2))) &&
			(((Y1 <= Y2) && (Y1 >= Y2 - S2)) || ((Y1 >= Y2) && (Y1 <= Y2 + S2))))
			p.life = false;
	}
}
