#pragma once
#include "Food.h"
#include "SFML/Graphics.hpp"

using namespace sf;

const int windowHeight = 1000;
const int windowWidth = 1500;
const int foodAmount = 300;
const int enemyAmount = 9;
const float startSize = 40;
const float mapWidth = 1000;
const float mapHeight = 1000;

extern float speedP;
extern float speedE;
extern float zoom;
extern float lineWidth;
extern float drawingDistance;

extern RectangleShape background;
extern RectangleShape resultsBackground;
extern RectangleShape lines;
extern RectangleShape columns;
extern CircleShape foodCircle;
extern Font font;
extern Text text;

extern Food foodArr[foodAmount];
extern Color colorArray[10];

extern RenderWindow window;
extern Event event;


