#include "Globals.h" 

float speedP = 0.5;
float speedE = 0.5;
float zoom = 0;
float lineWidth = 0.2;

RectangleShape background(Vector2f(map_width, map_height));
RectangleShape results_background(Vector2f(map_width, map_height));
RectangleShape lines(Vector2f(map_width, lineWidth));
RectangleShape columns(Vector2f(lineWidth, map_height));
CircleShape foodCircle;

Food foodCoord[foodAmount];
Color colorArray[5] = { Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan };


