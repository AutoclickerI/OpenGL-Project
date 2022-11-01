#include "Material.h"
Material::Material(const Material& mtl) {
	setEmission(mtl.emission[0], mtl.emission[1], mtl.emission[2], mtl.emission[3]);
	setAmbient(mtl.ambient[0], mtl.ambient[1], mtl.ambient[2], mtl.ambient[3]);
	setDiffuse(mtl.diffuse[0], mtl.diffuse[1], mtl.diffuse[2], mtl.diffuse[3]);
	setSpecular(mtl.specular[0], mtl.specular[1], mtl.specular[2], mtl.specular[3]);
	setShininess(mtl.shininess[0]);
}
void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
};
void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void Material::setShininess(float sh) {
	shininess[0] = sh;
}