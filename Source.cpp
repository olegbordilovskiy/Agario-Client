#include "Library.h"

using namespace sf;
using namespace std;

int main() {

	Text text("", font);
	window.setFramerateLimit(80);
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	font.loadFromFile("resources\\impact2.ttf");

	bool isThePlayerDied = false;
	volatile bool isAllEnemiesDied = false;
	bool isTheEndOfPlay = false;
	bool isTheEndOfProgram = false;

	int mode;
	int amountOfPlayers;

	Color colorTemp;
	Uint32 colorInteger;
	Packet playerCoordinatePacket;

	while (window.isOpen()) {

		while (!isTheEndOfProgram) {

			mode = drawingMenu();
			if (mode == 1) break;
			if (mode == 0) {

				Client client;
				vector<Player*> players;
				if (!DrawingConnection(client)) {
					client.DisconnectFromServer();
					continue;
				}

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
				player.playerBody.setRadius(player.size);
				player.speed = speedP;
				player.playerBody.setFillColor(colorArray[rand() % 9]);
				player.life = true;

				colorTemp = player.playerBody.getFillColor();

				Packet playerPacket;

				playerPacket << player.x << player.y << player.size
				<< player.speed << player.life << colorTemp.toInteger();

				client.SendPacketToServer(playerPacket);

				Packet amountOfPlayersPacket;
				amountOfPlayersPacket = client.GetServerPacket();
				amountOfPlayersPacket >> amountOfPlayers;

				for (int i = 0; i < amountOfPlayers - 1; i++) {
					Player* player = new Player;
					playerPacket.clear();
					playerPacket = client.GetServerPacket();
					playerPacket >> player->x >> player->y >> player->size >> player->speed >> player->life >> colorInteger;
					player->playerBody.setRadius(player->size);
					player->playerBody.setFillColor(Color(colorInteger));
					players.push_back(player);
				}


				Packet enemiesPacket;
				enemiesPacket = client.GetServerPacket();

				enemiesPacket >> enemyAmount;

				for (int i = 0; i < enemyAmount; i++) {
					enemiesPacket >> enemyArr[i].x;
					enemiesPacket >> enemyArr[i].y;
					enemiesPacket >> enemyArr[i].size;
					enemiesPacket >> enemyArr[i].speed;
					enemiesPacket >> enemyArr[i].life;
					enemiesPacket >> colorInteger;
					enemyArr[i].enemyBody.setRadius(enemyArr[i].size);
					enemyArr[i].enemyBody.setFillColor(Color(colorInteger));
					enemyArr[i].SetEnemyBody();
				}

				Packet foodPacket;
				foodPacket = client.GetServerPacket();
				foodPacket >> foodAmount;

				for (int i = 0; i < foodAmount; i++) {
					foodPacket >> foodArr[i].x;
					foodPacket >> foodArr[i].y;
					foodPacket >> foodArr[i].life;

					foodPacket >> colorInteger;
					foodArr[i].color = (Color(colorInteger));
				}


				while (!isThePlayerDied) {


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

					playerCoordinatePacket.clear();
					playerCoordinatePacket << player.getPlayerCoordX() << player.getPlayerCoordY();

					client.SendPacketToServer(playerCoordinatePacket);

					window.clear(Color(153, 153, 255));
					window.draw(background);

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

					playerPacket.clear();
					playerPacket = client.GetServerPacket();
					playerPacket >> player.life >> player.size;
					player.playerBody.setRadius(player.size);

					playerPacket.clear();

					for (Player* player : players) {
						playerPacket.clear();
						playerPacket = client.GetServerPacket();
						playerPacket >> player->x >> player->y >> player->size >> player->speed >> player->life >> colorInteger;
						player->playerBody.setRadius(player->size);
						player->SetPlayerBody();
					}


					enemiesPacket.clear();
					enemiesPacket = client.GetServerPacket();

					for (int i = 0; i < enemyAmount; i++) {
						enemiesPacket >> enemyArr[i].x;
						enemiesPacket >> enemyArr[i].y;
						enemiesPacket >> enemyArr[i].size;
						enemiesPacket >> enemyArr[i].speed;
						enemiesPacket >> enemyArr[i].life;
						enemyArr[i].enemyBody.setRadius(enemyArr[i].size);
						enemiesPacket >> colorInteger;
						enemyArr[i].enemyBody.setFillColor(Color(colorInteger));
						enemyArr[i].SetEnemyBody();
					}

					foodPacket.clear();
					foodPacket = client.GetServerPacket();

					for (int i = 0; i < foodAmount; i++) {
						foodPacket >> foodArr[i].x;
						foodPacket >> foodArr[i].y;
						foodPacket >> foodArr[i].life;

						foodPacket >> colorInteger;
						foodArr[i].color = (Color(colorInteger));
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

					for (Player* player : players) {
						if (player->life == true)
							window.draw(player->playerBody);
					}

					window.display();


					if (!player.life) {
						isThePlayerDied = true;
						isTheEndOfPlay = true;
						client.DisconnectFromServer();
						drawingWinOrLose(isThePlayerDied, isTheEndOfProgram);
						players.clear();
					}
					else {
						for (int i = 0; i < enemyAmount; i++) {
							if (enemyArr[i].life) {
								isAllEnemiesDied = false;
								break;
							}
							isAllEnemiesDied = true;
						}
						if (isAllEnemiesDied) {
							for (Player* player : players) {
								if (player->life) {
									isAllEnemiesDied = false;
									break;
								}
								isAllEnemiesDied = true;
							}

							if (isAllEnemiesDied) {
								isTheEndOfPlay = true;
								client.DisconnectFromServer();
								drawingWinOrLose(isThePlayerDied, isTheEndOfProgram);
								players.clear();
								isThePlayerDied = true;
							}
						}
					}

					if (window.isOpen() == false) {
						client.DisconnectFromServer();
						return 0;
					}
				}
			}
		}

		return 0;
	}
}
