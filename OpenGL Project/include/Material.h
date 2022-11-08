#pragma once
class Material {
public:
	Material() {};
	Material(const Material& mtl);
	void setEmission(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setShininess(float sh);
	friend class Sphere;
	friend class Stage;
private:
	float emission[4] = { 0,0,0,0 };
	float ambient[4] = { 0,0,0,0 };
	float diffuse[4] = { 0,0,0,0 };
	float specular[4] = { 0,0,0,0 };
	float shininess[1] = { 0 };
};