#include "Globals.h" 

float speedP = 0.5;
float speedE = 0.5;
float zoom = 0;
float lineWidth = 0.2;


RectangleShape background(Vector2f(mapWidth, mapHeight));
RectangleShape resultsBackground(Vector2f(windowWidth, windowHeight));
RectangleShape lines(Vector2f(mapWidth, lineWidth));
RectangleShape columns(Vector2f(lineWidth, mapHeight));
CircleShape foodCircle;

Food foodArr[foodAmount];
Color colorArray[5] = { Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan };


