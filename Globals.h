#pragma once
#include "Food.h"
#include "SFML/Graphics.hpp"

using namespace sf;

const int foodAmount = 200;
const float start_size = 10;
const float map_width = 1000;
const float map_height = 1000;

extern float speedP;
extern float speedE;
extern float zoom;
extern float lineWidth;

extern RectangleShape background;
extern RectangleShape lines;
extern RectangleShape columns;
extern CircleShape foodCircle;

extern Food foodCoord[foodAmount];
extern Color colorArray[5];

