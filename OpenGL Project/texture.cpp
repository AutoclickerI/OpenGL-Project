#include "Texture.h"

void Texture::setFilename(char const* filename) {
	Filename = filename;
}
void Texture::settextureID(GLuint tID) {
	textureID = tID;
}
FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) {
		cout << "Could not find image: " << filename << " - Aborting." << endl;
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) {
		cout << "Couldn't determine file format - attempting to get from file extension..." << endl;
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	return bitmap32;
}

void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void Texture::initTexture() {
	FIBITMAP* bitmap32 = createBitMap(Filename);
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();
}

void Texture::drawSquareWithTexture(float width, float height) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-width / 2, -height / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-width / 2, height / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(width / 2, height / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(width / 2, -height / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Texture::drawCircleWithTexture(float radius, int slices) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_POLYGON);
	for (int i = 0; i < slices; i++) {
		glTexCoord2f(cos(2 * pi * i / slices) / 2 + .5f, sin(2 * pi * i / slices) / 2 + .5f); glVertex2f(radius * cos(2 * pi * i / slices), radius * sin(2 * pi * i / slices));
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Texture::displayStrokeCharacters(void* font, string c, float lnWidth, float x, float y) {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(lnWidth);
	glTranslatef(x, y, 0.0f);
	glScalef(1 / scaleFactor, 1 / scaleFactor, 1 / scaleFactor);
	for (int i = 0; i < c.size(); i++)
		glutStrokeCharacter(font, c[i]);
	glPopMatrix();
}