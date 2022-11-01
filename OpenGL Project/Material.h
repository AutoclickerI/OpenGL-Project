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
private:
	float emission[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess[1];
};