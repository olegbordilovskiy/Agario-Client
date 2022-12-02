#include "Library.h"

using namespace sf;
Enemy enemyArr[9];

int main() {

	Event event;
	RenderWindow window(VideoMode(1000, 1000), "Agar.io", Style::Default);
	window.setFramerateLimit(100);
	srand(time(NULL));
	view.reset(FloatRect(0, 0, 250, 250));

	drawingMap();

	lines.setFillColor(Color(192, 192, 192));
	columns.setFillColor(Color(192, 192, 192));


	for (int i = 0; i < 200; i++) {
		foodCoord[i].x = rand() % 900 + 50;
		foodCoord[i].y = rand() % 900 + 50;
		foodCoord[i].color = colorArray[rand() % 5];
	}

	Player player(rand() % 900 + 50, rand() % 900, start_size, speedP, colorArray[rand() % 5]);

	for (int i = 0; i <= 8; i++) {
		enemyArr[i].x = rand() % 900 + 50;
		enemyArr[i].y = rand() % 900 + 50;
		enemyArr[i].size = rand() % 10 + 1;
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

	return 0;
}
