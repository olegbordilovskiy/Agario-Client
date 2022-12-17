#include "Library.h"

using namespace sf;

int main() {

	Text text("", font);
	window.setFramerateLimit(100);
	srand(time(NULL));
	font.loadFromFile("resources\\impact2.ttf");

	bool isThePlayerDied = false;
	bool isAllEnemiesDied = false;
	bool isTheEndOfPlay = false;
	bool isTheEndOfProgram = false;

	while (window.isOpen()) {

		while (!isTheEndOfProgram) {

			if (drawingMenu(isTheEndOfProgram) == 1) break;
			isTheEndOfPlay = false;

			while (!isTheEndOfPlay) {

				isThePlayerDied = false;
				isAllEnemiesDied = false;

				view.reset(FloatRect(0, 0, windowWidth / 4, windowHeight / 4));
				drawingMap();

				zoom = 0;
				lineWidth = 0.2;
				view.setSize(windowWidth / 4, windowHeight / 4);
				drawingDistance = 200;

				lines.setFillColor(Color(192, 192, 192));
				columns.setFillColor(Color(192, 192, 192));

				Player player;
				player.x = rand() % 900 + 50;
				player.y = rand() % 900 + 50;
				player.size = 10;
				player.pl_form.setRadius(player.size);
				player.speed = speedP;
				player.pl_form.setFillColor(colorArray[rand() % 9]);
				player.life = true;

				for (int i = 0; i < enemyAmount; i++) {
					enemyArr[i].x = rand() % 900 + 50;
					enemyArr[i].y = rand() % 900 + 50;
					enemyArr[i].size = rand() % 10 + 5;
					enemyArr[i].speed = speedE * 5;
					enemyArr[i].pl_form.setRadius(enemyArr[i].size);
					enemyArr[i].pl_form.setFillColor(colorArray[rand() % 9]);
					enemyArr[i].pl_form.setPosition(Vector2f(enemyArr[i].x, enemyArr[i].y));
					enemyArr[i].life = false;
				}
				//enemyArr[8].life = true;

				for (int i = 0; i < foodAmount; i++) {
					foodArr[i].life = true;
					foodArr[i].x = rand() % 900 + 50;
					foodArr[i].y = rand() % 900 + 50;
					foodArr[i].color = colorArray[rand() % 9];

				}

				while (!isThePlayerDied) {

					isAllEnemiesDied = false;

					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();
					}

					window.setView(view);
					if (player.size > 40)
					{
						view.setSize(windowWidth / 2, windowHeight / 2);
						zoom = 8;
						lineWidth = 0.4;
						drawingDistance = 380;

					}

					player.move();
					window.clear(Color(153, 153, 255));
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
								foodCircle.setPosition(foodArr[i].x - 2, foodArr[i].y - 2);
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

					if (!player.life) isThePlayerDied = true;

					if (!enemyArr[0].life && !enemyArr[1].life && !enemyArr[2].life && !enemyArr[3].life && !enemyArr[4].life &&
						!enemyArr[5].life && !enemyArr[6].life && !enemyArr[7].life && !enemyArr[8].life)
					{
						isAllEnemiesDied = true;
						isThePlayerDied = true;
					}


					if (isThePlayerDied && !isAllEnemiesDied)
					{
						drawingWinOrLose(isTheEndOfPlay, isThePlayerDied, isTheEndOfProgram, player.life);
					}

					if (isThePlayerDied && isAllEnemiesDied)
					{
						drawingWinOrLose(isTheEndOfPlay, isThePlayerDied, isTheEndOfProgram, player.life);
					}
				}
			}
		}

		window.close();
	}

	return 0;
}
