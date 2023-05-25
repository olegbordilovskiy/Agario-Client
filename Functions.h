#pragma once
#include "View.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Client.h"

using namespace sf;

void drawingMap();

bool isItVisible(Player p, float X, float Y);

void eatingEnemy(Player &p, Enemy &e);

void drawingResults();

int drawingMenu();

void drawingRules(Sprite menuBackground);

void drawingWinOrLose(bool & is_the_death_of_player, bool & is_the_end_of_program);

void createButton(Text &text, RectangleShape &button);

void buttonNotSelected(Text &text, RectangleShape &button);

bool DrawingConnection(Client &client);