#pragma once
#include<GL/freeglut.h>
#include<vector>
#include<string>
class color {
	GLfloat _red;
	GLfloat _green;
	GLfloat _blue;

public:
	color(float red, float green, float blue) : _red(red), _green(green), _blue(blue) {}
	GLfloat red() {
		return _red;
	}
	GLfloat green() {
		return _green;
	}
	GLfloat blue() {
		return _blue;
	}
};


float randomGenF();
int randomGeni();

void drawRectGrad(float x1, float y1, float x2, float y2, color startColor , color midColor);
void drawPoly(std::vector<float> x, std::vector<float> y, color givenColor, float alpha=1.0);
void drawString(float x, float y, float z, void* font, std::string string);
void semiCircle(float p1, float q1, float radius, float start, float end);
void Circle(float x1, float y1, float radius);
void buttonMake(float x1, float y1, float x2, float y2, std::string buttonText, color stringColor, int screenWidth);
float getBitmapLength(std::string, int screenWidth);