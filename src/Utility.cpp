#include "Utility.hpp"
#include <math.h>
#include <string>

void drawRectGrad(float x1, float y1, float x2, float y2, color startColor, color midColor) {


	glColor3f(startColor.red(), startColor.green(), startColor.blue());

	glBegin(GL_POLYGON);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glColor3f(midColor.red(), midColor.green(), midColor.blue());
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);

	glEnd();
}

void drawPoly(std::vector<float> x, std::vector<float> y, color givenColor, float alpha)
{

	glColor4f(givenColor.red(), givenColor.green(), givenColor.blue(), alpha);
	glBegin(GL_POLYGON);
	for (int i = 0; i < x.size(); i++) {
		glVertex2f(x.at(i), y.at(i));
	}
	glEnd();
}

void drawString(float x, float y, float z, void* font, std::string string)
{
	unsigned char* str= reinterpret_cast<unsigned char*>(const_cast<char *>(string.c_str()));

	glRasterPos3f(x, y, z);
	glutBitmapString(font, const_cast<const unsigned char*>(str));
}

void semiCircle(float p1, float q1, float radius, float start, float end)
{
	float p, q;
	float angle;
	glBegin(GL_POLYGON);

	for (angle = start; fabsf(angle - end) < 0.1; angle = fmodf(angle + 1.0f,360.0f))
	{
		p = p1 + sin(angle) * radius;
		q = q1 + cos(angle) * radius;
		glVertex2f(p, q);
	}
	glEnd();

}

void Circle(float x1, float y1, float radius)
{
	float x2, y2;
	float angle;
	glBegin(GL_POLYGON);

	for (angle = 1.0f; angle < 360.0f; angle++)
	{
		x2 = x1 + sin(angle) * radius;
		y2 = y1 + cos(angle) * radius;
		glVertex2f(x2, y2);
	}
	glEnd();

}

float randomGenF()
{
	return (float)rand() / (RAND_MAX);
}



float getBitmapLength(std::string string, int screenWidth) {
	unsigned char* str = reinterpret_cast<unsigned char*>(const_cast<char*>(string.c_str()));
	int pix = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, str);
	return pix * 100 / (screenWidth);
}


void buttonMake(float x1, float y1, float x2, float y2, std::string buttonText, color stringColor, int screenWidth)
{
	int lenButton = x2 - x1;
	int lenText = getBitmapLength(buttonText, screenWidth);

	float xShift = (lenButton - lenText) / 2;
	color ButtonColor(0.5, 0.0, 0.5);
	color ButtonColorblack(0.0, 0.0, 0.0);
	drawRectGrad(x1, y1, x2, y2, ButtonColor, ButtonColor);
	drawRectGrad(x1 + 1, y1 + 1, x2 - 1, y2 - 1, ButtonColorblack, ButtonColorblack);
	glColor3f(stringColor.red(), stringColor.green(), stringColor.blue());
	drawString(x1 + xShift, y1 + 1.5, 0, GLUT_BITMAP_HELVETICA_18, buttonText);
}