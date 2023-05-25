#pragma once
#include "Food.h"
#include <vector>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

const int windowHeight = 1000;
const int windowWidth = 1500;
const float startSize = 40;
const float mapWidth = 1000;
const float mapHeight = 1000;
const float speedCoeff = 0.85;

extern int enemyAmount;
extern int foodAmount;

extern float speedP;
extern float speedE;
extern float zoom;
extern float lineWidth;
extern float drawingDistance;
extern bool WinOrLose;

extern RectangleShape background;
extern RectangleShape resultsBackground;
extern RectangleShape lines;
extern RectangleShape columns;
extern CircleShape foodCircle;
extern Font font;

extern Food foodArr[300];
extern Color colorArray[10];

extern RenderWindow window;
extern Event event;
extern Texture menuBackgroundT;


