#include "aeroplane.hpp"
#include <GL/freeglut.h>
#include "Utility.hpp"

void drawAeroplane(){
    color aeroGrey(0.8, 0.8, 0.8);
	color dome(0.0, 0.0, 0.0);

	std::vector<float> leftTailX({ 13.0, 17.0, 13.0, 11.0});
	std::vector<float> leftTailY({ 47.0, 47.0, 49.0, 49.0});
	drawPoly(leftTailX, leftTailY, aeroGrey);

	std::vector<float> tailX({ 2.7, 3.0, 5.0, 7.0, });
	std::vector<float> tailY({ 47.0, 51.0, 51.0, 47.0, });
	drawPoly(tailX, tailY, aeroGrey);


	//body -- Special, Hence, Use Normal Primitives.
	glColor3f(3/255, 0.0, 30/255);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 48.0);
	glVertex2f(6.0, 47.8);
	glColor3f(115 / 255, 3/255, 192 / 255);
	glVertex2f(7.0, 47.6);
	glVertex2f(8.0, 47.4);
	glColor3f(236 / 255, 56 / 255, 188/ 255);
	glVertex2f(11.0, 48.0);
	glVertex2f(22.0, 46.5);
	glColor3f(253 / 239, 56 / 255, 249 / 255);
	glVertex2f(22.0, 45.0);
	glColor3f(3 / 255, 0.0, 30 / 255);
	glVertex2f(2.5, 46.0);
	glEnd();

	std::vector<float> rightFrontWingX({ 13.0, 18.0, 13.0, 11.0, });
	std::vector<float> rightFrontWingY({ 46.0, 46.0, 44.0, 44.0, });
	drawPoly(rightFrontWingX, rightFrontWingY, aeroGrey);

	std::vector<float> domeX({ 13.0, 15.0, 17.0, 19.0, 21.0, 17.0, 15.0, 13.0, });
	std::vector<float> domeY({ 47.0, 48.5, 49.0, 48.0, 46.0, 46.0, 47.5, 47.0, });
	drawPoly(domeX, domeY, dome, 0.3);


	std::vector<float> rightTailX({ 2.5, 5.5, 2.5, 1.5, });
	std::vector<float> rightTailY({ 47.0, 47.0, 45.0, 45.0, });
	drawPoly(rightTailX, rightTailY, aeroGrey);
}