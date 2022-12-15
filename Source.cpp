#include "Library.h"

using namespace sf;

int main() {

	Event event;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Agar.io", Style::Default);
	window.setFramerateLimit(100);
	srand(time(NULL));

	Font font;
	font.loadFromFile("resources\\impact2.ttf");
	Text text("", font, 30);

	bool isTheEndOfGame;

Begin:

	isTheEndOfGame = false;

	view.reset(FloatRect(0, 0, windowWidth/4, windowHeight/4));
	drawingMap();

	zoom = 0;
	lineWidth = 0.2;
	view.setSize(windowWidth / 4, windowHeight / 4);

	lines.setFillColor(Color(192, 192, 192));
	columns.setFillColor(Color(192, 192, 192));

	Player player;
	player.x = rand() % 900 + 50;
	player.y = rand() % 900 + 50;
	player.size = startSize;
	player.pl_form.setRadius(player.size);
	player.speed = speedP;
	player.pl_form.setFillColor(colorArray[rand() % 5]);
	player.life = true;

	for (int i = 0; i < enemyAmount; i++) {
		enemyArr[i].x = rand() % 900 + 50;
		enemyArr[i].y = rand() % 900 + 50;
		enemyArr[i].size = rand() % 10 + 5;
		enemyArr[i].speed = speedE * 5;
		enemyArr[i].pl_form.setRadius(enemyArr[i].size);
		enemyArr[i].pl_form.setFillColor(colorArray[rand() % 5]);
		enemyArr[i].pl_form.setPosition(Vector2f(enemyArr[i].x, enemyArr[i].y));
		enemyArr[i].life = true;
	}

	for (int i = 0; i < foodAmount; i++) {
		foodArr[i].life = true;
		foodArr[i].x = rand() % 900 + 50;
		foodArr[i].y = rand() % 900 + 50;
		foodArr[i].color = colorArray[rand() % 5];

	}

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (!isTheEndOfGame) {

			window.clear();
			window.setView(view);
			changeZoom(player);
			player.move();
			window.draw(background);

			for (int i = 0; i < enemyAmount; i++) {
				if (enemyArr[i].life == true)
					enemyArr[i].move(player, enemyArr[i], foodArr);
			}

			for (int i = 0; i < enemyAmount; i++) {
				eatingEnemy(player, enemyArr[i]);
			}

			player.eatingFood(player);
			for (int i = 0; i < enemyAmount; i++) {
				if (enemyArr[i].life == true)
					enemyArr[i].eatingFood(enemyArr[i]);
			}

			for (int i = 0; i < mapHeight; i += 10 + zoom) {
				if (isItVisible(player, player.getPlayerCoordX() + 130, i)) {
					window.draw(lines);
					lines.setPosition(0, i);
					lines.setSize(Vector2f(mapWidth, lineWidth));
				}
			}

			for (int i = 0; i < mapWidth; i += 10 + zoom) {
				if (isItVisible(player, i, player.getPlayerCoordY() + 130)) {
					window.draw(columns);
					columns.setPosition(i, 0);
					columns.setSize(Vector2f(lineWidth, mapHeight));
				}
			}

			for (int i = 0; i < foodAmount; i++) {
				if (isItVisible(player, foodArr[i].x, foodArr[i].y)) {
					if (foodArr[i].life == true) {
						foodCircle.setPosition(foodArr[i].x, foodArr[i].y);
						foodCircle.setRadius(2);
						foodCircle.setFillColor(foodArr[i].color);
						window.draw(foodCircle);
					}
				}
			}

			for (int i = 0; i < enemyAmount; i++) {
				if (enemyArr[i].life == true)
					window.draw(enemyArr[i].pl_form);
			}

			window.draw(player.pl_form);
			window.display();

			if (!player.life) isTheEndOfGame = true;

			if (!enemyArr[0].life && !enemyArr[1].life && !enemyArr[2].life && !enemyArr[3].life && !enemyArr[4].life &&
				!enemyArr[5].life && !enemyArr[6].life && !enemyArr[7].life && !enemyArr[8].life) isTheEndOfGame = true;
		}

		if (!player.life && isTheEndOfGame)
		{
			window.clear();
			view.reset(FloatRect(0, 0, windowWidth, windowHeight));
			window.setView(view);
			resultsBackground.setFillColor(Color(240, 128, 128));
			window.draw(resultsBackground);

			text.setString(L"Вас съели!");
			text.setCharacterSize(150);
			text.setFillColor(Color::Red);
			text.setOutlineThickness(7);
			text.setPosition(view.getCenter().x - 340, view.getCenter().y - 280);
			window.draw(text);

			text.setString(L"Нажмите ""R"" чтобы начать новую игру");
			text.setCharacterSize(40);
			text.setFillColor(Color::Black);
			text.setOutlineThickness(0);
			text.setPosition(view.getCenter().x - 300, view.getCenter().y - 70);
			window.draw(text);

			text.setString(L"Нажмите Esc чтобы выйти");
			text.setPosition(view.getCenter().x - 300, view.getCenter().y);
			window.draw(text);

			window.display();
			if (Keyboard::isKeyPressed(Keyboard::R))
				goto Begin;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		if ((!enemyArr[0].life && !enemyArr[1].life && !enemyArr[2].life && !enemyArr[3].life && !enemyArr[4].life &&
			!enemyArr[5].life && !enemyArr[6].life && !enemyArr[7].life && !enemyArr[8].life) && isTheEndOfGame)
		{
			window.clear();
			view.reset(FloatRect(0, 0, 1000, 1000));
			window.setView(view);
			resultsBackground.setFillColor(Color(176, 224, 230));
			window.draw(resultsBackground);

			text.setString(L"Вы победили!");
			text.setCharacterSize(130);
			text.setFillColor(Color::Blue);
			text.setOutlineThickness(7);
			text.setPosition(view.getCenter().x - 380, view.getCenter().y - 280);
			window.draw(text);

			text.setString(L"Нажмите ""R"" чтобы начать новую игру");
			text.setCharacterSize(40);
			text.setFillColor(Color::Black);
			text.setOutlineThickness(0);
			text.setPosition(view.getCenter().x - 300, view.getCenter().y - 70);
			window.draw(text);

			text.setString(L"Нажмите Esc чтобы выйти");
			text.setPosition(view.getCenter().x - 300, view.getCenter().y);
			window.draw(text);

			window.display();
			if (Keyboard::isKeyPressed(Keyboard::R))
				goto Begin;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
	}

	return 0;
}
