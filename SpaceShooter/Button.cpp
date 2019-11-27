#include "Button.h"
#include "glut.h"
void Button::render() {
	//std::cout<<textureId<<std::endl;
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glColor3d(col.r, col.g, col.b);
	glBegin(GL_QUADS);

	//glNormal3f(0.0f, 1.0f, 0.0f);
	//glColor3d(00,0,0);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(location.x, location.y);
	glTexCoord2f(1.0, 1.0);
	glVertex2d(location.x + dim.width, location.y);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(location.x + dim.width, location.y + dim.height);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(location.x, location.y + dim.height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glColor3d(1, 1, 1);
	glRasterPos2f(location.x + dim.width / 2 - (text.size() * 10) + 30, location.y + dim.height / 2 + 5);
	char c;
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;
	for (int i = 0; i<text.size(); i++) {
		c = text.at(i);
		glutBitmapCharacter(font, c);
	}
	glPopMatrix();
	//glutSwapBuffers();
	//glDisable(GL_TEXTURE_2D);

}

bool Button::isClicked(int x, int y) {
	//std::cout<< location.x<<" "<< location.x + dim.width<< " "<< location.y<<" "<<
	return location.x <= x && x <= location.x + dim.width && location.y <= y && y <= location.y + dim.height;
}

Button::Button() {
}


Button::~Button() {
}
