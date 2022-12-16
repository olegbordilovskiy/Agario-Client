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

void drawingMenu() {
	int menuMode;
	bool flag = false;
	Text startText("", font, 50);;
	Text rulesText("", font, 80);;
	Text exitText("", font, 80);;
	Texture menuBackgroundT;
	Texture menuT;
	Sprite menuBackground;
	Sprite menu;
	RectangleShape startButton(Vector2f(400, 100));
	RectangleShape rulesButton(Vector2f(400, 100));
	RectangleShape exitButton(Vector2f(400, 100));

	menuBackgroundT.loadFromFile("resources\\menu.png");
	menuT.loadFromFile("resources\\menuRect.png");
	menuBackground.setTexture(menuBackgroundT);
	menu.setTexture(menuT);
	menuBackground.setScale(0.5, 0.5);
	menu.setScale(1.3, 1.3);
	menu.setColor(Color(255, 255, 255, 230));
	menu.setPosition(windowWidth/4,windowHeight/10);
	
	text.setString("Agar.io");
	text.setFillColor(Color(51, 255, 153));
	text.setCharacterSize(170);
	text.setOutlineThickness(10);
	text.setLetterSpacing(1.5);
	text.setPosition(windowWidth / 3, windowHeight / 6);

	startButton.setPosition(560, 500);
	rulesButton.setPosition(615, 600);
	exitButton.setPosition(648, 700);

	startButton.setFillColor(Color(0, 0, 0, 0));
	rulesButton.setFillColor(Color(0, 0, 0, 0));
	exitButton.setFillColor(Color(0, 0, 0, 0));

	startText.setString(L"Начать игру");
	startText.setFillColor(Color(51, 255, 153));
	startText.setCharacterSize(75);
	startText.setOutlineThickness(5);
	startText.setPosition(startButton.getPosition());

	rulesText.setString(L"Правила");
	rulesText.setFillColor(Color(51, 255, 153));
	rulesText.setCharacterSize(75);
	rulesText.setOutlineThickness(5);
	rulesText.setPosition(rulesButton.getPosition());

	exitText.setString(L"Выход");
	exitText.setFillColor(Color(51, 255, 153));
	exitText.setCharacterSize(75);
	exitText.setOutlineThickness(5);
	exitText.setPosition(exitButton.getPosition());

	while (!flag) {
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		//startText.setFillColor(Color(51, 255, 153));
		window.draw(menuBackground);
		window.draw(menu);
		window.draw(text);
		window.draw(startButton);
		window.draw(startText);
		window.draw(rulesButton);
		window.draw(rulesText);
		window.draw(exitButton);
		window.draw(exitText);
		

		if (IntRect(560, 500, 400, 100).contains(Mouse::getPosition(window))) 
		{
			startText.setFillColor(Color(102, 178, 255));
			startText.setCharacterSize(90);
			startText.setPosition(560 - 35, 500 - 10);
		}
		else
		{
			startText.setFillColor(Color(51, 255, 153));
			startText.setCharacterSize(75);
			startText.setPosition(startButton.getPosition());
		}

		if (IntRect(560, 600, 400, 100).contains(Mouse::getPosition(window)))
		{
			rulesText.setFillColor(Color(102, 178, 255));
			rulesText.setCharacterSize(90);
			rulesText.setPosition(615 - 35, 600 - 10);
		}
		else
		{
			rulesText.setFillColor(Color(51, 255, 153));
			rulesText.setCharacterSize(75);
			rulesText.setPosition(rulesButton.getPosition());
		}

		if (IntRect(560, 700, 400, 100).contains(Mouse::getPosition(window)))
		{
			exitText.setFillColor(Color(255, 51, 51));
			exitText.setCharacterSize(90);
			exitText.setPosition(648 - 25, 700 - 10);
		}
		else
		{
			exitText.setFillColor(Color(51, 255, 153));
			exitText.setCharacterSize(75);
			exitText.setPosition(exitButton.getPosition());
		}

		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Escape)) flag = true;
		
	}

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
