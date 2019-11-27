#include<cstdlib>
#include<iostream>
#include<vector>
#include<random>
#include<sstream>
#include<string>
#include "Button.h"
#include "imageloader.h"
#include "FileConfig.h"
#include "soil\SOIL.h"
#include "Asteroid.h"
#include "Structs.h"
#include "Bullet.h"

#include "SpaceshipU1.h"
#include "SpaceshipU2.h"
#include "SpaceshipE1.h"
#include "GenerateTexture.h"

#include "glut.h"
#include "soundApi\irrKlang.h"
#if defined(_WIN32)
#include<conio.h>
#endif

#pragma comment(lib, "lib/irrKlang.lib") 
#pragma comment(lib, "lib/glut32.lib") 

#define WIDTH 1024
#define HEIGHT 576
#define SOUND_OFF 10
#define SOUND_ON 11

#define ASTEROID_TIME 2

#define GAME_MENU 1
#define GAME_CREDIT 2
#define GAME_OPTION 3
#define IN_GAME 4
#define PRE_GAME 5
#define GAME_OVER 6
using namespace std;

vector<Button>menuButtonList, optionButtonList;
vector<Asteroid*>asteroidList;
vector<Bullet>bulletList;
vector<pair<double, double> >starList;
Button creditButton;
GLuint _textureId, gameBackTexture, gameLifeTexture, asteroidTexture, menuBackTexture, preGameTexture, mainBackTexture;
GLuint gameOverTexture;
int gameState;
int soundState;
int lifeCount;
int score;
double alpha;
double playerX;
double playerZ = -20;
double minX=-10, maxX=10;
double playerY = -6;
long long time, lastAsteroidTime;
SpaceshipModel_U1* spaceship1;
irrklang::ISoundEngine* engine;
irrklang::ISoundSource* shootSound;
irrklang::ISoundSource* gameBackSound;
irrklang::ISoundSource* menuBackSound;
irrklang::ISoundSource* destroySound;
irrklang::ISoundSource* lifeLossSound;
GLuint numberTexture[10];
GLuint loadTexture(string file);
GLuint loadTexture(Image* image);
void menuButtons();
void mouseHandler(int button, int state, int x, int y);
void DrawCredit();
void creditButtons();
void printString(int x, int y, string text, void *, Color color = Color(1, 1, 1));
void optionButtons();
void lightSettings();
void update(int);
void drawBackground2D(int, int, GLuint);
void drawImage3D(double, double, double, double, double, GLuint);
void movePlayer(int key,int x,int y);
void playerFire(unsigned char key, int x, int y);

void EnableLights() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_COLOR_MATERIAL);
}

void DisableLights() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_COLOR_MATERIAL);
}

void loadGameOver() {
	drawImage3D(-4, -2, -8, 8, 4, gameOverTexture);
	gameState = GAME_OVER;
}

void Reset2D() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
}

void DrawU1() {
	
	// Collision Area
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/*glPushMatrix();
	glTranslatef(0.0, 1.50, -0.10);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glutWireSphere(3.0, 100, 100);
	glPopMatrix();*/

	//glClear(GL_COLOR_BUFFER_BIT);

	// Spaceship
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glColor3d(1, 1, 1);
	glPushMatrix();
	glTranslatef(-1.0, 1.50, 0.0);
	// 1st Part
	glPushMatrix();
		glTranslatef(-1, 0, 0);
		//glColor3f(0.0, 0.0, 1.0);
		//GenerateTexture* newTex = new GenerateTexture((this->PrePath += "U1_FireArm_Body.bmp").c_str());
		//GenerateTexture* newTex1 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Body1.bmp");

		//gluQuadricTexture(newTex1->getQuadricObject(), 1);
		gluCylinder(quadratico, 0.40, 0.50, 2.0, 10, 10);

		//glBindTexture(GL_TEXTURE_2D, 0);
		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		//delete newTex1;
	glPopMatrix();

	// 2nd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.0);
	//glColor3f(1.0, 0.0, 0.0);
	//GenerateTexture* newTex2 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Mid.bmp");

	//gluQuadricTexture(newTex2->getQuadricObject(), 1);
	gluCylinder(quadratico, 0.50, 0.40, 0.40, 10, 10);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//delete newTex2;
	glPopMatrix();


	// 3rd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.10);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(quadratico, 0.40, 0.40, 1.0, 10, 10);
	glPopMatrix();

	// 4th Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.90);
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(quadratico, 0.39, 0.39, 0.60, 10, 10);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 1.50, 0.0);
	// 1st Part
	glPushMatrix();
		glTranslatef(-1, 0, 0);
		//glColor3f(0.0, 0.0, 1.0);
		//GenerateTexture* newTex = new GenerateTexture((this->PrePath += "U1_FireArm_Body.bmp").c_str());
		//GenerateTexture* newTex1 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Body1.bmp");

		//gluQuadricTexture(newTex1->getQuadricObject(), 1);
		gluCylinder(quadratico, 0.40, 0.50, 2.0, 10, 10);

		//glBindTexture(GL_TEXTURE_2D, 0);
		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		//delete newTex1;
	glPopMatrix();

	// 2nd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.0);
	//glColor3f(1.0, 0.0, 0.0);
	//GenerateTexture* newTex2 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Mid.bmp");

	//gluQuadricTexture(newTex2->getQuadricObject(), 1);
	gluCylinder(quadratico, 0.50, 0.40, 0.40, 10, 10);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//delete newTex2;
	glPopMatrix();


	// 3rd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.10);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(quadratico, 0.40, 0.40, 1.0, 10, 10);
	glPopMatrix();

	// 4th Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.90);
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(quadratico, 0.39, 0.39, 0.60, 10, 10);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.50, 0.0);
	glPushMatrix();
	glTranslatef(0, 0, 0.90);
	glColor3f(1.50, 0.70, 0.0);
	glScalef(5.00, 6.0, 20.0);
	glutSolidTorus(0.02, 0.40, 100, 100);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 1.50, 0.0);
	glPushMatrix();
	glTranslatef(-2.0, 0, 0.90);
	glColor3f(1.50, 0.70, 0.0);
	gluCylinder(quadratico, 0.50, 0.50, 0.60, 100, 100);
	glPopMatrix();

	// right wings
	glPushMatrix();
	glTranslatef(-0.70, 0, 0.90);
	glScalef(1.00, 0.2, 0.50);
	glColor3f(1.50, 0.50, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// left wings
	glPushMatrix();
	glTranslatef(-3.30, 0, 0.90);
	glScalef(1.00, 0.2, 0.50);
	glColor3f(0.50, 0.50, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// Main Body
	// Back Part
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glScalef(1.75, 0.50, 2.0);
	glColor3f(0.75, 0.50, 1.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();

	// Back Part 2
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glRotatef(90.0f, 0.0, 0.0, 1.0);
	glScalef(1.75, 0.50, 2.0);
	glColor3f(0.75, 0.50, 1.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();

	// Front Part

	// Bottom Plate
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.0);
	glScalef(1.50, 0.20, 2.0);
	glColor3f(0.75, 0.50, 1.50);
	glutSolidCube(1.0);
	glPopMatrix();

	// Mid Plate
	glPushMatrix();
	glTranslatef(-2.00, 0.50, 0.0);
	glScalef(0.50, 1.00, 2.0);
	glColor3f(1.75, 0.50, 1.50);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// round plate
	glPushMatrix();
	glTranslatef(-2.00, 0.50, -0.10);
	glScalef(1.00, 1.00, 7.0);
	glColor3f(1.00, 1.00, 0.00);
	glutSolidTorus(0.20, 0.50, 100, 100);
	glPopMatrix();

	// Front Cone
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glRotatef(180.0f, 1.0, 0.0, 0.0);
	glScalef(1.75, 2.00, 2.0);
	glColor3f(0.75, 0.50, 1.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 1.50, 0.0);
	// right blocker
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(0.75, 0.75, 0.20);
	glColor3f(1.00, 0.50, 1.00);
	glutSolidTorus(0.20, 0.30, 100, 100);
	glPopMatrix();

	// left blocker
	glPushMatrix();
	glTranslatef(-4.0, 0.0, 0.0);
	glScalef(0.75, 0.75, 0.20);
	glColor3f(1.00, 0.50, 1.00);
	glutSolidTorus(0.20, 0.30, 100, 100);
	glPopMatrix();
	glPopMatrix();
}

void drawScore() {
	stringstream ss;
	ss << score;
	string text;
	ss >> text;
	while (text.size() <= 4) text = "0" + text;

	double x = -1.4;
	for (int i = 0; i < text.size(); i++) {
		int j = text[i] - 48;
		drawImage3D(x+i*0.1, 0.65, -2, 0.1, 0.1, numberTexture[j]);
	}
}

void drawStars() {
	/*glPointSize(20);
	glBegin(GL_POINTS);
	for (int i = 0; i < starList.size(); i++) {
		glVertex3d(starList[i].first, starList[i].second, -50);
	}
	glEnd();*/
	double axisX = 65, axisY=37;
	//glColor3d(1, 0, 1);
	glPushMatrix();
	//glColor3d(1, 1, 1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gameBackTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-axisX,-axisY,-90);
	glTexCoord2d(1, 0);
	glVertex3d(axisX, -axisY, -90);
	glTexCoord2d(1, 1);
	glVertex3d(axisX,axisY, -90);
	glTexCoord2d(0, 1);
	glVertex3d(-axisX,axisY, -90);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawLifes() {
	double x = 1.2;
	for (int i = 0; i < lifeCount; i++) {
		drawImage3D(x-0.17*i, 0.6, -2, 0.2, 0.2, gameLifeTexture);
	}
}

void drawPlayer() {
	glPushMatrix();
	glTranslatef(playerX, playerY, playerZ);
	glColor3f(1.0, 0.0, 0.0);
	//glutSolidSphere(2, 100, 100);
	DrawU1();
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
}

void drawEnemy() {
	if (time-lastAsteroidTime>=ASTEROID_TIME*1000 && rand()%2==0) {
		lastAsteroidTime = time;
		Asteroid *a = new Asteroid();
		a->radius = 2;
		a->location.x = minX + (rand() % (int)(2 * maxX));
		a->location.y = playerY+2;
		a->location.z = -90;
		a->textureId = asteroidTexture;
		asteroidList.push_back(a);
	}

	for (int i = 0; i < asteroidList.size();i++) {
		if (asteroidList[i]->shouldRemove()) {
			asteroidList.erase(asteroidList.begin() + i);
			i = 0;
		}
		else if (asteroidList[i]->hasCollide(playerX)) {
			asteroidList.erase(asteroidList.begin() + i);
			if(soundState==SOUND_ON)
				engine->play2D(lifeLossSound);
			i = 0;
			lifeCount--;
		}
		else asteroidList[i]->render();
	}
}

void drawBullets() {
	for (int i = 0; i < bulletList.size(); i++) {
		if (bulletList[i].location.z >= 50) {
			bulletList.erase(bulletList.begin() + i);
			i = 0;
			continue;
		}
		else{
			for (int j = 0; j < asteroidList.size(); j++) {
				if (bulletList[i].hasCollide(*asteroidList[j])) {
					asteroidList.erase(asteroidList.begin() + j);
					bulletList.erase(bulletList.begin() + i);
					if(soundState==SOUND_ON)
						engine->play2D(destroySound);
					score += 50;
					i = 0;
					break;
				}
			}
		}
	}
	for (int i = 0; i < bulletList.size(); i++) {
		bulletList[i].render();
	}
}

void DrawMenu() {
	glColor4f(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground2D(WIDTH, HEIGHT, mainBackTexture);
	for (int i = 0; i < menuButtonList.size(); i++)
		menuButtonList[i].render();
	glFlush();
}

void DrawOptions() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground2D(WIDTH, HEIGHT, menuBackTexture);
	for (int i = 0; i < optionButtonList.size(); i++)
		optionButtonList[i].render();
	glFlush();
}

void DrawGame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();
	//gluLookAt(0, 0, 0, 0, 0,-40, 0, 1, 0);
	glPushMatrix();
	drawStars();
	drawBullets();
	drawPlayer();

	drawLifes();
	drawScore();
	if(lifeCount>0) drawEnemy();

	if (lifeCount <= 0) {
		loadGameOver();
		/*glPopMatrix();
		gameState = GAME_OVER;
		Reset2D();
		DisableLights();
		//glutDisplayFunc(loadGameOver);
		glutDisplayFunc(DrawMenu);
		engine->stopAllSounds();
		glutPostRedisplay();
		gameState = GAME_MENU;
		return;*/
	}

	glPopMatrix();
	glutSwapBuffers();
	glFlush();
	//_ASSERT(glGetError() == GL_NO_ERROR);
}

void InitMenu() {
	//gluOrtho2D()
	asteroidList.clear();
	bulletList.clear();
	_textureId = loadTexture("images/button.png");
	menuBackTexture = loadTexture("images/background.jpg");
	mainBackTexture = loadTexture("images/menu_background.png");
	spaceship1 = new SpaceshipModel_U1(1, "G2 G2 G2", "Pluto");

	gameBackTexture = loadTexture("images/bcg1.jpg");
	gameLifeTexture = loadTexture("images/life.png");
	asteroidTexture = loadTexture("images/astr.bmp");
	gameOverTexture = loadTexture("images/gameover.png");

	for (int i = 0; i < 10; i++) {
		string path = "images\\digits\\numeral";
		path += (char)(i + 48);
		path += ".png";
		//cout << path << endl;
		numberTexture[i] = loadTexture(path);
		//cout << numberTexture[i] << endl;
	}

	/*Image* image = loadBMP("img_test.bmp");
	_textureId = loadTexture(image);
	delete image;*/
	//cout << _textureId << endl;
	//glutDisplayFunc(DrawMenu);
}

void initGame() {
	glClearColor(0, 0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.77, 1.0, 100.0);
	gameState = IN_GAME;
	time = 0;
	lastAsteroidTime = 0;

	engine->stopAllSounds();
	if(soundState==SOUND_ON)
		engine->play2D(gameBackSound,true);
	gameBackSound->setDefaultVolume(0.6f);

	lifeCount = 3;
	score = 0;
	playerX = 0;
	double axis = 35;
	/*for (int i = 0; i < 500; i++) {
		double xx = (axis- (-axis)) * ((double)rand() / (double)RAND_MAX) + (-axis);
		double yy= (axis - (-axis)) * ((double)rand() / (double)RAND_MAX) + (-axis);
		starList.push_back(make_pair(xx,yy));
		//cout << xx << ' ' << yy << endl;
	}*/

	/*Asteroid a;
	a.radius = 1;
	a.location = Location(0,0,-10);
	a.textureId = loadTexture("images/ast2.png");
	asteroidList.push_back(a);
	Asteroid a1;
	a1.radius = 1;
	a1.location = Location(0, 3, -10);
	a1.textureId = a.textureId;
	asteroidList.push_back(a1);
	lightSettings();*/
	//lightSettings();
	EnableLights();
	glutTimerFunc(30, update, 0);
	//glutDisplayFunc(DrawGame);
}

void PreGame() {
	glClear(GL_COLOR_BUFFER_BIT);

	double x = -110, y = 160;
	double width = 1227, height = 200;
	double z = 0;

	glPushMatrix();
	glColor4f(1, 1, 1, alpha);
	//glEnable(GL_NORMALIZE);
	//glNormal3f(0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, preGameTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2d(x, y+height);
	glTexCoord2d(1, 0);
	glVertex2d(x+width, y+height);
	glTexCoord2d(1, 1);
	glVertex2d(x+width, y);
	glTexCoord2d(0, 1);
	glVertex2d(x, y);

	glEnd();
	glPopMatrix();
	glFlush();
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Space Shooter");
	engine = irrklang::createIrrKlangDevice();
	shootSound = engine->addSoundSourceFromFile("Sounds/Bullet_Firing.wav");
	gameBackSound = engine->addSoundSourceFromFile("Sounds/Game_OnGoing_Background.wav");
	menuBackSound = engine->addSoundSourceFromFile("Sounds/Menu_Background.wav");
	destroySound = engine->addSoundSourceFromFile("Sounds/Bullet_Firing_2_Optional.wav");
	lifeLossSound = engine->addSoundSourceFromFile("Sounds/Bullet_Pain.wav");
	preGameTexture = loadTexture("images/logo.png");
	lightSettings();
	gameState = PRE_GAME;
	alpha = 1;
	Reset2D();
	InitMenu();
	menuButtons();
	creditButtons();
	optionButtons();
	if(soundState==SOUND_ON)
		engine->play2D(menuBackSound, true);
	glutDisplayFunc(PreGame);
	/*initGame();
	glutTimerFunc(30, update, 0);
	glutDisplayFunc(DrawGame);*/
	glutMouseFunc(mouseHandler);
	glutSpecialFunc(movePlayer);
	glutKeyboardFunc(playerFire);
	glutTimerFunc(50, update, 0);
	glutMainLoop();
	engine->drop();
	return 0;
}

void optionButtons() {
	FileConfig file;
	pair<string,string> c = file.getConfig();
	Button b;
	b.name = "sound";
	b.text = "Sound: ";
	if (c.first == "sound") {
		if (c.second == "off") {
			b.text += "ON";
			soundState = SOUND_OFF;
		}
		else { 
			b.text += "OFF"; 
			soundState = SOUND_ON;
		}
	}
	b.col = Color(0, 1, 0);
	b.dim = Dimension(200, 50);
	b.location = Location(150, 50, 0);
	b.textureId = _textureId;
	optionButtonList.push_back(b);
	
	Button b2;
	b2.name = "goHome";
	b2.text = "Go Home";
	b2.col = Color(0, 1, 0);
	b2.dim = Dimension(200, 50);
	b2.location = Location(150, 350, 0);
	b2.textureId = _textureId;
	optionButtonList.push_back(b2);
}

void toggleSound(Button &b) {
	if (soundState == SOUND_OFF) {
		FileConfig file;
		file.setConfig("sound","on");
		soundState = SOUND_ON;
		engine->play2D(menuBackSound,true);
		b.text = "Sound: OFF";
	}
	else if (soundState == SOUND_ON) {
		FileConfig file;
		file.setConfig("sound", "off");
		soundState = SOUND_OFF;
		engine->stopAllSounds();
		b.text = "Sound: ON";
	}
	glutPostRedisplay();
}

void creditButtons() {
	//Button b;
	creditButton.name = "goHome";
	creditButton.text = "Go Home";
	creditButton.col = Color(0, 1, 0);
	creditButton.dim = Dimension(200, 50);
	creditButton.location = Location(150, 350, 0);
	creditButton.textureId = _textureId;
}

void menuButtons() {
	Button b, b2, b3, b4;
	b.name = "startGame";
	b.text = "Start Game";
	b.col = Color(0, 1, 0);
	b.dim = Dimension(200, 50);
	b.location = Location(670, 70, 0);
	b.textureId = _textureId;

	b2.name = "options";
	b2.text = "Options";
	b2.col = Color(0, 1, 0);
	b2.dim = Dimension(200, 50);
	b2.location = Location(670, 160, 0);
	b2.textureId = _textureId;

	b3.name = "credits";
	b3.text = "Credits";
	b3.col = Color(0, 1, 0);
	b3.dim = Dimension(200, 50);
	b3.location = Location(670, 250, 0);
	b3.textureId = _textureId;

	b4.name = "exit";
	b4.text = "Exit Game";
	b4.col = Color(0, 1, 0);
	b4.dim = Dimension(200, 50);
	b4.location = Location(670, 340, 0);
	b4.textureId = _textureId;

	menuButtonList.push_back(b);
	menuButtonList.push_back(b2);
	menuButtonList.push_back(b3);
	menuButtonList.push_back(b4);
}

void DrawCredit() {
	glClear(GL_COLOR_BUFFER_BIT);
	string name = "3D Space Shooter";
	string version = "Version: Beta Version";
	string developers = "Developed By:";
	string fahim = "Fahim Uddin (raydvard@gmail.com)";
	string arif = "Arif Hosan (hosan.arif0@gmail.com)";
	string efrat = "Kazi Efrat Ara (efrat.kazi56@gmail.com)";
	string mentor = "Mentor: Imrul Jubair";
	string info[] = { "As part of a Group project","Computer Graphics Spring 2016-2017" };

	drawBackground2D(WIDTH, HEIGHT, menuBackTexture);
	printString(175, 50, name, GLUT_BITMAP_TIMES_ROMAN_24, Color(1, 0, 0));
	printString(165, 80, version, GLUT_BITMAP_HELVETICA_18);
	printString(185, 110, developers, GLUT_BITMAP_HELVETICA_18, Color(0,1,0));
	printString(95, 140, fahim, GLUT_BITMAP_HELVETICA_18);
	printString(95, 170, arif, GLUT_BITMAP_HELVETICA_18);
	printString(95, 200, efrat, GLUT_BITMAP_HELVETICA_18);
	printString(165, 230, mentor, GLUT_BITMAP_HELVETICA_18, Color(0, 1, 0));

	printString(155, 260, info[0], GLUT_BITMAP_HELVETICA_18);
	printString(100, 290, info[1], GLUT_BITMAP_HELVETICA_18);

	creditButton.render();
	glFlush();
}

void update(int val) {
	if (gameState == PRE_GAME) {
		time += 50;
		alpha -= 0.01;
	}
	else if (gameState == IN_GAME)time += 30;
	else return;
	if (time >= 5000 && gameState == PRE_GAME) {
		glutDisplayFunc(DrawMenu);
		gameState = GAME_MENU;
		glutPostRedisplay();
		return;
	}

	for (int i = 0; i < asteroidList.size(); i++)
		asteroidList[i]->move();
	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].move();
	//cout << time << endl;
	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

void printString(int x, int y, string text, void *font, Color color) {
	glColor3d(color.r, color.g, color.b);
	
	glDisable(GL_LIGHTING);
	glRasterPos2f(x, y);
	//glColor3d(1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	char c;
	for (int i = 0; i<text.size(); i++) {
		c = text.at(i);
		glutBitmapCharacter(font, c);
	}
	glColor3d(1, 1, 1);
}

void mouseHandler(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) return;
	if (state != GLUT_DOWN) return;
	cout << x << ' ' << y << endl;
	if (gameState == GAME_MENU) {
		for (int i = 0; i < menuButtonList.size(); i++) {
			if (menuButtonList[i].isClicked(x, y)) {
				if (menuButtonList[i].name == "exit") exit(0);
				else if (menuButtonList[i].name == "credits") {
					gameState = GAME_CREDIT;
					glutDisplayFunc(DrawCredit);
					glutPostRedisplay();
				}
				else if (menuButtonList[i].name == "options") {
					gameState = GAME_OPTION;
					glutDisplayFunc(DrawOptions);
					glutPostRedisplay();
				}
				else if (menuButtonList[i].name == "startGame") {
					gameState = IN_GAME;
					initGame();
					glutDisplayFunc(DrawGame);
					glutPostRedisplay();
				}
			}
		}
	}
	else if (gameState == GAME_CREDIT) {
		if (creditButton.isClicked(x, y)) {
			glutDisplayFunc(DrawMenu);
			gameState = GAME_MENU;
			glutPostRedisplay();
		}
	}
	else if (gameState == GAME_OPTION) {
		for (int i = 0; i < optionButtonList.size(); i++) {
			if (optionButtonList[i].isClicked(x, y)) {
				if (optionButtonList[i].name == "sound") {
					toggleSound(optionButtonList[i]);
				}
				if (optionButtonList[i].name == "goHome") {
					glutDisplayFunc(DrawMenu);
					gameState = GAME_MENU;
					glutPostRedisplay();
				}
			}
		}
	}
	else if (gameState == GAME_OVER) {
		engine->stopAllSounds();
		if(soundState==SOUND_ON)
			engine->play2D(menuBackSound, true);
		DisableLights();
		Reset2D();
		gameState = GAME_MENU;
		glutDisplayFunc(DrawMenu);
		glutPostRedisplay();
	}
}

void movePlayer(int key, int x, int y) {
	if (gameState != IN_GAME) return;
	double speed = 2;
	switch(key) {
	case GLUT_KEY_LEFT:
		if(playerX-speed>=minX)
			playerX -= speed;

		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (playerX + speed <= maxX)
		playerX += speed;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	cout << playerX << endl;
}

void playerFire(unsigned char key,int x,int y) {
	if (gameState != IN_GAME) return;
	Bullet b;
	b.dim.width = 0.5;
	b.dim.height = 1;
	b.location.x = playerX+2;
	b.location.y = playerY+1.5;
	b.location.z = playerZ - 1;
	b.textureId = _textureId;
	bulletList.push_back(b);

	Bullet b2;
	b2.dim.width = 0.5;
	b2.dim.height = 1;
	b2.location.x = playerX -2;
	b2.location.y = playerY + 1.5;
	b2.location.z = playerZ - 1;
	b2.textureId = _textureId;
	bulletList.push_back(b2);
	if (soundState == SOUND_ON)
		engine->play2D(shootSound);;
}

GLuint loadTexture(string file) {
	return 
	SOIL_load_OGL_texture
	(
		file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
	);
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
									  //cout<<textureId<<endl;
	return textureId; //Returns the id of the texture
}

void lightSettings() {
	float lightAmbient[] = { 0,0,0,1.0 };
	float lightDiffuse[] = { 1,1,1,1 };
	float lightSpecular[] = { 1,1,1,1 };
	float lightPostion[4] = { 0,10,-20,1 };
	float lightPostion2[4] = { 0,0.6,-1,1 };
	float lightPostion3[4] = { 0,-10,-20,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPostion);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPostion2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPostion2);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	float materialSpecular[] = { 1,1,1,1 };
	float materialShine[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShine);
}

void drawBackground2D(int w, int h, GLuint file) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, file);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2d(0, h );
	glTexCoord2d(1, 0);
	glVertex2d(w, h);
	glTexCoord2d(1, 1);
	glVertex2d(w, 0);
	glTexCoord2d(0, 1);
	glVertex2d(0, 0 );
	
	glEnd();
	glPopMatrix();
}

void drawImage3D(double x,double y,double z,double width, double height,GLuint tid) {
	glPushMatrix();
	//glEnable(GL_NORMALIZE);
	//glNormal3f(0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(x, y, z);
	glTexCoord2d(1, 0);
	glVertex3d(x + width, y, z);
	glTexCoord2d(1, 1);
	glVertex3d(x + width, y + height, z);
	glTexCoord2d(0, 1);
	glVertex3d(x, y + height, z);

	glEnd();
	glPopMatrix();
}
