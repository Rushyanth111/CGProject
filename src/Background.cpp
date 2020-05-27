#include "Background.hpp"
#include "Utility.hpp"


void drawGameBackground()
{
	color darkGrass(0.0, 0.48, 0.047), lightGrass(0.0, 0.3, 0.03);
	color lightGrey(44.0 / 255, 62.0 / 255, 80.0 / 255), sunset(1.0, 1.0, 1.0);

	drawRectGrad(0.0, 0.9, 100.0, 10.0, darkGrass, lightGrass); //Grass
	drawRectGrad(0.0, 100.0, 100.0, 10.0, lightGrey, sunset); //Skybox.
}

void drawBackground() {
	color lightGrey(44.0 / 255, 62.0 / 255, 80.0 / 255), sunset(253.0 / 255, 116.0 / 255, 108.0 / 255);
	drawRectGrad(0.0, 0.0, 100.0, 100.0, sunset, lightGrey); //Skybox.
}
