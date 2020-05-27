#include "Foreground.hpp"
#include "Utility.hpp"
#include "Objects.hpp"
void drawBuilding(building building_state, color buildColor)
{

	color window(1.0, 1.0, 1.0);
	for (int i = 1; i <= building_state.no_floors; i++)
	{
		glPushMatrix();
		glTranslatef(building_state.block_x, 10.0 * i, 0.0);		//base
		drawRectGrad(0.0, 0.0, 15.0, 10.0, buildColor, buildColor); //The Building Itself.
		drawRectGrad(2.5, 5.0, 5.5, 8.0, window, window);			//Left Window
		drawRectGrad(12.5, 5.0, 9.5, 8.0, window, window);			//Right Window
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(building_state.block_x, 10.0, 0.0); //base
	drawRectGrad(0.0, 0.0, 15.0, 10.0, buildColor, buildColor);
	drawRectGrad(5.5, 0.0, 9.5, 6.0, window, window);
	glPopMatrix();
}

void drawCloud(Cloud cloud_state, color buildColor)
{
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(cloud_state.block_x, cloud_state.block_y, 0.0);
	glutSolidSphere(5, 100, 10);
	glTranslatef(6, -3.0, 0.0);
	glutSolidSphere(5, 100, 10);
	glTranslatef(0, 6.0, 0.0);
	glutSolidSphere(5, 100, 10);
	glTranslatef(6, -3.0, 0.0);
	glutSolidSphere(5, 100, 10);
}
