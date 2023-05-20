#include "Library.h"

using namespace sf;
using namespace std;

int main() {

	Text text("", font);
	window.setFramerateLimit(100);
	srand(time(NULL));
	font.loadFromFile("resources\\impact2.ttf");

	bool isThePlayerDied = false;
	//bool isAllEnemiesDied = false;
	//bool isTheEndOfPlay = false;
	bool isTheEndOfProgram = false;

	int mode;
	Color colorTemp;
	Uint8 r, g, b;
	//int sock;

	/*struct GameState
	{
		Enemy enemies_arr[9];
		Food food_arr[300];
	};
	GameState packet;*/
	//stringstream ss;
	//string buffer;

	Client client;

	while (window.isOpen()) {

		while (!isTheEndOfProgram) {

			mode = drawingMenu();
			if (mode == 1) break;
			if (mode == 0) {
				//if ((sock = DrawingConnection()) == NULL) continue;

			//isTheEndOfPlay = false;

			//while (!isTheEndOfPlay) {

				client.ConnectToServer();
				client.GetMessageTest();

				Player player;
				player.x = rand() % 900 + 50;
				player.y = rand() % 900 + 50;
				player.size = 10;
				player.playerBody.setRadius(player.size);
				player.speed = speedP;
				player.playerBody.setFillColor(colorArray[rand() % 9]);
				player.life = true;

				colorTemp = player.playerBody.getFillColor();

				Packet PlayerPacket;

				PlayerPacket << player.x << player.y << player.size << player.speed << player.life
				<< player.playerBody.getRadius() << colorTemp.r << colorTemp.g << colorTemp.b;

				client.SendPlayerCondition(PlayerPacket);

				Packet packetEnemies;
				packetEnemies = client.GetServerPacket();

				packetEnemies >> enemyAmount;

				for (int i = 0; i < enemyAmount; i++) {
					enemyArr[i].x >> packetEnemies;
					enemyArr[i].y >> packetEnemies;
					enemyArr[i].size >> packetEnemies;
					enemyArr[i].speed >> packetEnemies;
					enemyArr[i].life >> packetEnemies;
					enemyArr[i].enemyBody.setRadius(enemyArr[i].size);
					packetEnemies >> r >> g >> b;
					colorTemp = Color(r, g, b);
					enemyArr[i].enemyBody.setFillColor(colorTemp);
					enemyArr[i].enemyBody.setPosition(Vector2f(enemyArr[i].x, enemyArr[i].y));
				}

				view.reset(FloatRect(0, 0, windowWidth / 4, windowHeight / 4));
				drawingMap();
					
				zoom = 0;
				lineWidth = 0.2;
				view.setSize(windowWidth / 4, windowHeight / 4);
				drawingDistance = 200;

				lines.setFillColor(Color(192, 192, 192));
				columns.setFillColor(Color(192, 192, 192));

				

				/*for (int i = 0; i < enemyAmount; i++) {
					enemyArr[i].x = rand() % 900 + 50;
					enemyArr[i].y = rand() % 900 + 50;
					enemyArr[i].size = rand() % 1 + 5;
					enemyArr[i].speed = speedCoeff / sqrt(sqrt(enemyArr[i].size));
					enemyArr[i].enemyBody.setRadius(enemyArr[i].size);
					enemyArr[i].enemyBody.setFillColor(colorArray[rand() % 9]);
					enemyArr[i].enemyBody.setPosition(Vector2f(enemyArr[i].x, enemyArr[i].y));
					enemyArr[i].life = true;
				}

				for (int i = 0; i < foodAmount; i++) {
					foodArr[i].life = true;
					foodArr[i].x = rand() % 900 + 50;
					foodArr[i].y = rand() % 900 + 50;
					foodArr[i].color = colorArray[rand() % 9];

				}*/

				//while (!isThePlayerDied) {

					//isAllEnemiesDied = false;

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
						window.draw(enemyArr[i].enemyBody);
				}

				window.draw(player.playerBody);
				window.display();

				///////////////////////////////////////////////////////////////////////////////////////////
				//for (int i = 0; i < enemyAmount; i++) {
				//	packet.enemies_arr[i].life = enemyArr[i].life;
				//	packet.enemies_arr[i].x = enemyArr[i].getPlayerCoordX();
				//	packet.enemies_arr[i].y = enemyArr[i].getPlayerCoordY();
				//	packet.enemies_arr[i].size = enemyArr[i].getPlayerSize();
				//	packet.enemies_arr[i].enemyBody.setFillColor(enemyArr[i].enemyBody.getFillColor());
				//}
				//for (int i = 0; i < foodAmount; i++) {
				//	packet.food_arr[i].life = foodArr[i].life;
				//	packet.food_arr[i].color = foodArr[i].color;
				//	packet.food_arr[i].x = foodArr[i].x;
				//	packet.food_arr[i].y = foodArr[i].y;
				//}
				//ss.write(reinterpret_cast<const char*>(&packet), sizeof(GameState));
				//buffer = ss.str();


				/////////////////////////////////////////////////////////////////////////////////////////
				if (!player.life) isThePlayerDied = true;

				/*if (!enemyArr[0].life && !enemyArr[1].life && !enemyArr[2].life && !enemyArr[3].life && !enemyArr[4].life &&
					!enemyArr[5].life && !enemyArr[6].life && !enemyArr[7].life && !enemyArr[8].life)
				{
					isAllEnemiesDied = true;
					isThePlayerDied = true;
				}*/


				/*if (isThePlayerDied && !isAllEnemiesDied)
				{
					drawingWinOrLose(isTheEndOfPlay, isThePlayerDied, isTheEndOfProgram, player.life);
				}

				if (isThePlayerDied && isAllEnemiesDied)
				{
					drawingWinOrLose(isTheEndOfPlay, isThePlayerDied, isTheEndOfProgram, player.life);
				}*/
				if (window.isOpen() == false) return 0;
			}
				//}
			//}
		}

		window.close();
	}

	return 0;
}
