#include "Library.h"

using namespace sf;

int main() {

	Event event;
	RenderWindow window(VideoMode(1000, 1000), "Agar.io", Style::Default);
	window.setFramerateLimit(100);
	srand(time(NULL));
	Font font;
	font.loadFromFile("resources\\impact2.ttf");
	Text text("", font, 30);

Begin:

	view.reset(FloatRect(0, 0, 250, 250));
	drawingMap();

	lines.setFillColor(Color(192, 192, 192));
	columns.setFillColor(Color(192, 192, 192));


	for (int i = 0; i < 200; i++) {
		foodCoord[i].x = rand() % 900 + 50;
		foodCoord[i].y = rand() % 900 + 50;
		foodCoord[i].color = colorArray[rand() % 5];
	}

	Player player;
	player.x = rand() % 900 + 50;
	player.y = rand() % 900 + 50;
	player.size = start_size;
	player.pl_form.setRadius(player.size);
	player.speed = speedP;
	player.pl_form.setFillColor(colorArray[rand() % 5]);
	player.life = true;

	for (int i = 0; i <= 8; i++) {
		enemyArr[i].x = rand() % 900 + 50;
		enemyArr[i].y = rand() % 900 + 50;
		enemyArr[i].size =  20 + 1;
		enemyArr[i].speed = speedE;
		enemyArr[i].pl_form.setRadius(enemyArr[i].size);
		enemyArr[i].pl_form.setFillColor(colorArray[rand() % 5]);
		enemyArr[i].pl_form.setPosition(Vector2f(enemyArr[i].x, enemyArr[i].y));
		enemyArr[i].life = true;
	}

	bool flag = true;

	Vector2f optimization = view.getSize();

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (player.life) {

			changeZoom();

			player.move();

			for (int i = 0; i <= 8; i++) {
				eatingEnemy(player, enemyArr[i]);
			}

			for (int i = 0; i <= 8; i++) {
				if (enemyArr[i].life == true)
					enemyArr[i].move(player, enemyArr[i]);
			}

			player.eatingFood(player);
			for (int i = 0; i <= 8; i++) {
				if (enemyArr[i].life == true)
					enemyArr[i].eatingFood(enemyArr[i]);
			}

			window.setView(view);

			window.clear();

			window.draw(background);
			for (int i = 0; i < map_height; i += 10 + zoom) {
				if (isItVisible(player, player.getPlayerCoordX() + 130, i)) {
					window.draw(lines);
					lines.setPosition(0, i);
					lines.setSize(Vector2f(map_width, lineWidth));
				}

			}

			for (int i = 0; i < map_width; i += 10 + zoom) {
				if (isItVisible(player, i, player.getPlayerCoordY() + 130)) {
					window.draw(columns);
					columns.setPosition(i, 0);
					columns.setSize(Vector2f(lineWidth, map_height));
				}
			}


			for (int i = 0; i < foodAmount; i++) {

				if (isItVisible(player, foodCoord[i].x, foodCoord[i].y)) {
					if ((foodCoord[i].x != -100) && (foodCoord[i].y != -100)) {
						foodCircle.setPosition(foodCoord[i].x, foodCoord[i].y);
						foodCircle.setRadius(2);
						foodCircle.setFillColor(foodCoord[i].color);
						window.draw(foodCircle);
					}
				}

			}

			for (int i = 0; i <= 8; i++) {
				if (enemyArr[i].life == true)
					window.draw(enemyArr[i].pl_form);
			}
	
			window.draw(player.pl_form);
			window.display();

		}

		else 
		{
			window.clear();
			view.reset(FloatRect(0, 0, 1000, 1000));
			window.setView(view);
			drawingResults();
			window.draw(results_background);

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
			text.setCharacterSize(40);
			text.setFillColor(Color::Black);
			text.setOutlineThickness(0);
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
