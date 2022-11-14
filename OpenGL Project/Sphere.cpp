#include "Sphere.h"
Sphere::Sphere(float r, int sl, int st) {
	setRadius(r);
	setSlice(sl);
	setStack(st);
}
Sphere::Sphere(const Sphere& shape) {
	setRadius(shape.radius);
	setSlice(shape.slice);
	setStack(shape.stack);
	setCenter(shape.center[0], shape.center[1], shape.center[2]);
	setVelocity(shape.velocity[0], shape.velocity[1], shape.velocity[2]);
	setMTL(shape.mtl, shape.num);
}
void Sphere::setRadius(float r) {
	radius = r;
}
float Sphere::getRadius() const {
	return radius;
}
float Sphere::getdistance(const Sphere& shape) const {
	return sqrt(((shape.center[0] - center[0]) * (shape.center[0] - center[0]) + (shape.center[1] - center[1]) * (shape.center[1] - center[1])));
}
void Sphere::setSlice(int sl) {
	slice = sl;
}
void Sphere::setStack(int st) {
	stack = st;
}
void Sphere::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}
const float* Sphere::getCenter() const {
	return center;
}
void Sphere::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}
float* Sphere::getVelocity() const {
	return velocity;
}
int Sphere::getnum() const {
	return num;
}
void Sphere::setMTL(const Material& m, int n) {
	mtl = m;
	num = n;
}
void Sphere::move() {
	for (int i = 0; i < 3; i++)
		center[i] += velocity[i];
}
void Sphere::showSphere(bool s) {
	show = s;
}
Material Sphere::getMTL() {
	return mtl;
}
void Sphere::draw() const {
	if (show) {
		glMaterialfv(GL_FRONT, GL_EMISSION, mtl.emission);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mtl.shininess);
		glPushMatrix();
		glTranslatef(center[0], center[1], center[2]);
		glutSolidSphere(radius, slice, stack);
		glPopMatrix();
	}
}