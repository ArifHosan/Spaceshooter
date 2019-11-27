#pragma once

#include "glut.h"
#include "imageloader.h"

class GenerateTexture {
private:
	const char* ImagePath;
	GLuint _texId;
	GLUquadric* quadric;

public:
	
	GenerateTexture(const char* ImagePath) {
		this->ImagePath = ImagePath;


		TextureInitialize();
		
		bindTextureNow();

		initQuadricObject();
		//Draw();

	}

	GLuint getTexture() {
		return this->_texId;
	}

	GLUquadric* getQuadricObject() {
		return this->quadric;
	}

	void initQuadricObject() {
		this->quadric = gluNewQuadric();
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
		return textureId; //Returns the id of the texture
	}

	void TextureInitialize() {
		Image* image = loadBMP(ImagePath);

		this->_texId = loadTexture(image);

		delete image;

	}

	void bindTextureNow() {
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, this->_texId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}

	void Draw() {

		

		

		glPushMatrix();
		gluQuadricTexture(getQuadricObject(), 1);
		gluSphere(getQuadricObject(), 3.0, 100, 100);
		glPopMatrix();

		glutSwapBuffers();
	}
};

