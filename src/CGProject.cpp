#include <GL/freeglut.h>
#include <time.h>
#include <stdio.h>
#include <random>

#include "Utility.hpp"
#include "aeroplane.hpp"
#include "Foreground.hpp"
#include "Background.hpp"
#include "Objects.hpp"
#define BLOCKSPEED 0.9f;

int SCREENH = 600, SCREENW = 800;

//-------------------declarations---------------
float bspd = BLOCKSPEED;																	 // block speed
bool pause = false, lflag = true, welcome_flag = true, gameEndStatus = false, start = false; //flags
float plane_mvmt = 0.0;																		 //jet movement up or down
char score_Str[20], slevel[20];																 //score string and levelstring

float score = 1;
int level = 1; //Level and Score Counter

bool jetisUp = false;

color buildColor(randomGenF(), randomGenF(), randomGenF());
building building_state; // building struct
Cloud cloud_state;		 // cloud struct

//-------------function prototypes------------------
void keyPressed(unsigned char, int, int);
void mouse(int button, int state, int x, int y);
void buildingBlock();
void CloudBlock();
void init();
void gameEnd();
void welcome();
bool cloudHit();
bool buildingHit();
void printScore();
void display();
void moveJetU();
void moveJetD();

//------------------ Object Makers:

void buildingBlock()
{
	building_state.block_x = 50.0;
	srand(time(0));
	building_state.no_floors = rand() % 3 + 4;
	buildColor = color(randomGenF(), randomGenF(), randomGenF());
	building_state.block_y = building_state.no_floors * 10 + 15; // generate block y cordinate depending on no of floors
	building_state.state = true;
	cloud_state.state = false;
}

void CloudBlock()
{
	cloud_state.block_x = 50.0;
	srand(time(0));
	cloud_state.block_y = (rand() % 30) + 50; //randomly generate block y cordinate
	cloud_state.state = true;
	building_state.state = false;
}

//------------------- Drawing Functions:

void gameEnd()
{
	drawBackground();
	color white(1.0, 1.0, 1.0);

	glColor3f(0.196, 0.196, 0.8); // disp box
	glRectf(20.0, 20.0, 80.0, 80.0);
	glColor3f(0.0, 0.0, 0.0);
	glRectf(21.0, 21.0, 79.0, 79.0);

	buttonMake(40, 5, 60, 10, "RESTART", white, SCREENW);

	drawString(41, 71, 0, GLUT_BITMAP_HELVETICA_18, "GAME OVER");
	drawString(23, 61, 0, GLUT_BITMAP_HELVETICA_18, "DISTANCE :" + std::string(score_Str));
	drawString(23, 56, 0, GLUT_BITMAP_HELVETICA_18, "LEVEL :" + std::string(slevel));
	glutPostRedisplay();
}

void welcome()
{
	color white(1.0, 1.0, 1.0);

	drawBackground();
	buttonMake(39.5, 39.5, 60.5, 45.5, "PLAY", white, SCREENW);
	buttonMake(40, 10, 60, 15, "EXIT", white, SCREENW);

	drawString(29.5, 92, 0, GLUT_BITMAP_HELVETICA_18, "COMPUTER GRAPHICS PROJECT");
	drawString(35.5, 80, 0, GLUT_BITMAP_HELVETICA_18, "AIRPLANE CRASH");
}

void PlayScreen()
{
	if ((int)score % 100 == 0 && lflag == true) // l-level
	{
		lflag = false;
		level++;
	}
	else if ((int)score % 100 != 0 && lflag == false)
	{
		lflag = true;
	}

	glPushMatrix();
	drawGameBackground();

	glPushMatrix();
	glTranslatef(0.0, plane_mvmt, 0.0);
	drawAeroplane(); //code for jet
	glPopMatrix();

	score += bspd;
	if ((building_state.state == true && building_state.block_x < -10) || (cloud_state.state == true && cloud_state.block_x < -10)) // If Building or Could has gone outside the area.
	{
		srand(time(NULL));
		int random = rand() % 2; //for random building or cloud
		if (random == 0)
		{
			buildingBlock();
		}
		else
		{
			CloudBlock();
		}
	}

	else if (building_state.state == true)
	{
		building_state.block_x -= bspd;
		glTranslatef(building_state.block_x, 0.0, 0.0);
		drawBuilding(building_state, buildColor);
	}
	else if (cloud_state.state == true)
	{
		cloud_state.block_x -= bspd;
		glTranslatef(cloud_state.block_x, 0.0, 0.0);
		drawCloud(cloud_state, buildColor);
	}

	glPopMatrix();

	printScore();
}

void printScore()
{
	sprintf_s(slevel, "%d", (int)level);
	sprintf_s(score_Str, "%d m", (int)score);

	glColor3f(1.0, 1.0, 1.0); //score
	drawString(58, 1.8, 0, GLUT_BITMAP_HELVETICA_10, const_cast<char *>("Level"));
	drawString(58, 3.5, 0, GLUT_BITMAP_HELVETICA_18, slevel);

	drawString(38, 1.5, 0, GLUT_BITMAP_HELVETICA_10, const_cast<char *>("Distance"));
	drawString(38, 3, 0, GLUT_BITMAP_HELVETICA_18, score_Str);
}

//---------------------Calculating Functions.

bool cloudHit()
{
	if (cloud_state.block_x < 13 && cloud_state.block_x > -5)
		if (plane_mvmt - 3 + 50 > cloud_state.block_y - 3 && plane_mvmt - 3 + 50 < cloud_state.block_y + 3) // plane front to cloud mid box1
			return true;

	if (cloud_state.block_x < 12 && cloud_state.block_x > -4)
		if (plane_mvmt - 3 + 50 > cloud_state.block_y - 5 && plane_mvmt - 3 + 50 < cloud_state.block_y + 5) // plane front to cloud mib box2
			return true;

	if (cloud_state.block_x < 10 && cloud_state.block_x > -1)
		if (plane_mvmt - 3 + 50 > cloud_state.block_y - 6 && plane_mvmt - 3 + 50 < cloud_state.block_y - 2)
			return true;

	//for top wing and bottom wing
	if (cloud_state.block_x < 5 && cloud_state.block_x > -3)
		if (plane_mvmt - 3 + 50 > cloud_state.block_y - 11 && plane_mvmt - 3 + 50 < cloud_state.block_y + 13)
			return true;

	return false;
}

bool buildingHit()
{
	if (((int)building_state.block_x <= 8 && (int)building_state.block_x >= -7 && ((int)plane_mvmt + 50) - building_state.block_y <= 3)) //buildin back  body to tail
		return true;
	else if (((int)building_state.block_x <= 10 && (int)building_state.block_x >= -5 && ((int)plane_mvmt + 50) - building_state.block_y <= 0)) //body to tail
		return true;
	else if (((int)building_state.block_x <= 6 && (int)building_state.block_x >= -3 && ((int)plane_mvmt + 47) - building_state.block_y <= 0)) //right wing
		return true;
	else if (((int)building_state.block_x <= 4 && (int)building_state.block_x >= -4 && ((int)plane_mvmt + 47) - building_state.block_y <= 3)) //   building back right wing
		return true;
	else
		return false;
}

bool boundHit()
{
	if (plane_mvmt + 50 >= 100 || plane_mvmt + 50 <= 18) // top and bottom boundary
		return true;
	else
		return false;
}

void moveJetU() // jet moving up
{
	if (pause == false)
	{
		plane_mvmt = plane_mvmt + 1.0f;
	}
}

void moveJetD() // jet moving down
{
	if (pause == false && gameEndStatus == false && welcome_flag == false)
	{
		plane_mvmt -= 0.5f;
	}
}

void mouse(int button, int state, int x, int y) // takes input from mouse
{
	int mx = x * 100 / SCREENW, my = (SCREENH - y) * 100 / SCREENH; // m = mouse cordinate to graphics

	/*		mouse calculation//converting to screen coordinates-ortho values
	SCREENSIZE  ---->  ORTHO
	x(reqd val) ---->  ???
	*/
	if (gameEndStatus == true)
	{
		if (mx > 40 && mx < 60 && my > 5 && my < 10) //Co-ordinates for the Button.
		{
			welcome_flag = true;
			gameEndStatus = false;
			plane_mvmt = 0;
			start = false;
			init();
			bspd = BLOCKSPEED; //restarting the game
			score = 1;
			level = 1;
			glutPostRedisplay();
		}
	}
	else if (welcome_flag == true)
	{
		if (mx > 40 && mx < 60) //Line of Options:
		{
			if (my > 40 && my < 45) //Start
			{
				start = true;
				welcome_flag = false;
			}
			else if (my > 10 && my < 15) //Exit
			{
				glutLeaveMainLoop();
			}
		}
	}
	else // For Playing the game.
	{
		if (start == true)
		{
			if (button == GLUT_LEFT_BUTTON)
			{
				if (state == GLUT_DOWN)
					jetisUp = true;

				else if (state == GLUT_UP)
					jetisUp = false;
			}
		}
	}
}

void keyPressed(unsigned char key, int x, int y) // int x and y are mouse pos at time of press
{
	if (key == 27)
	{
		exit(0);
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	SCREENH = h, SCREENW = w;
	printf("width = %d\theight= %d", w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -5.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

//------------------------ Main Stuff
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
		(building_state.state == true && buildingHit() == true) || (boundHit() == true) ||
		(cloud_state.state == true && cloudHit() == true))
	*/
	if (gameEndStatus == true)
	{
		gameEnd();
	}
	else if (welcome_flag == true) //Welcome Screen
	{
		welcome();
	}
	else
	{
		PlayScreen();
	}
	//glFlush();
	glutSwapBuffers();
}

void init()
{
	srand(time(0));
	int random = rand() % 2;
	if (random == 0)
	{
		buildingBlock();
	}
	else
	{
		CloudBlock();
	}
}

void update(int value)
{
	//Timer Function to be called in 30s.

	if (start == true)
	{
		//Movement Functions.
		if (jetisUp)
			moveJetU();
		else
			moveJetD();

		if(cloudHit() || buildingHit() || boundHit() ){ //Check for Collision Every frame
			gameEndStatus = true;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, value);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREENW, SCREENH);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Airplane Crash");
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_FOG, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutTimerFunc(1000 / 30, update, 0);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}
