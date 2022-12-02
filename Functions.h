#pragma once
#include "View.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;

sf::View changeZoom();

void drawingMap();

bool isItVisible(Player p, float X, float Y);

void eatingEnemy(Player &p, Enemy &e);
