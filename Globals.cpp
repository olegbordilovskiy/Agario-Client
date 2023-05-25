#include "Globals.h" 

float speedP = 0.5;
//float speedE = 0.60;
float zoom = 0;
float lineWidth = 0.2;
float drawingDistance = 200;
bool WinOrLose;

int foodAmount = 300;
int enemyAmount = 9;


RectangleShape background(Vector2f(mapWidth, mapHeight));
RectangleShape resultsBackground(Vector2f(windowWidth, windowHeight));
RectangleShape lines(Vector2f(mapWidth, lineWidth));
RectangleShape columns(Vector2f(lineWidth, mapHeight));
CircleShape foodCircle;
Font font;

Food foodArr[300];

Color colorArray[10] = { Color(255, 0, 0), Color(0, 255, 0), Color(0, 255, 255), Color(255, 255, 0), Color(255, 180, 0), 
						 Color(51, 51, 255), Color(255, 153, 153), Color(127, 0, 255), Color(0, 255, 128), Color(0, 0, 150) };

RenderWindow window(VideoMode(windowWidth, windowHeight), "Agar.io client", Style::Default);
Event event;

Texture menuBackgroundT;
