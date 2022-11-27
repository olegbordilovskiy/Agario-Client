#include "Library.h"

using namespace sf;

RectangleShape columns(Vector2f(lineWidth, map_height));
CircleShape foodCircle;

Event event;
ContextSettings settings;

int main() {

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

	Enemy e1(rand() % 900 + 50, rand() % 900 + 50, rand() % 20 + 1, speedE, Color::Red);
	Enemy e2(rand() % 900 + 50, rand() % 900 + 50, rand() % 20 + 1, speedE, Color::Yellow);
	Enemy e3(rand() % 900 + 50, rand() % 900 + 50, rand() % 1 + 1, speedE, Color::Green);
	Enemy e4(rand() % 900 + 50, rand() % 900 + 50, rand() % 20 + 1, speedE, Color::Magenta);
	Enemy e5(rand() % 900 + 50, rand() % 900 + 50, rand() % 20 + 1, speedE, Color::Cyan);
	Enemy e6(rand() % 900 + 50, rand() % 900 + 50, rand() % 20 + 1, speedE, Color::Transparent);

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
		e1.move(player, e1);
		e2.move(player, e2);
		e3.move(player, e3);
		e4.move(player, e4);
		e5.move(player, e5);
		e6.move(player, e6);

		player.eatingFood(player);
		e1.eatingFood(e1);
		e2.eatingFood(e2);
		e3.eatingFood(e3);
		e4.eatingFood(e4);
		e5.eatingFood(e5);
		e6.eatingFood(e6);

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


		window.draw(e1.pl_form);
		window.draw(e2.pl_form);
		window.draw(e3.pl_form);
		window.draw(e4.pl_form);
		window.draw(e5.pl_form);
		window.draw(e6.pl_form);


		window.draw(player.pl_form);


		window.display();

	}

	return 0;
}
