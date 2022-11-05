#pragma once
#include <ctime>
#include <vector>
#include <cstdlib>
#include "Sound.h"
#include "Light.h"
#include "Stage.h"
#include "Sphere.h"
#include "Texture.h"

#define WINDOW_X 0
#define WINDOW_Y 0

#define WINDOW_WIDTH 1280		// window's width
#define WINDOW_HEIGHT 720		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2

const double PI = 3.141592653589793;
enum Theme { SNU, theme1, theme2 };

using namespace std;

Theme theme;
clock_t start_t = clock();
clock_t end_t;

vector<Sphere> shootings;
vector<Sphere> cannon;
vector<Sphere> stage_Sphere;
vector<pair<Sphere,int>> merge;
vector<int> merge_prograss;
vector<double> stage_Location;
vector<Material> materials;
vector<Sound> sound;
Light light(0, 0, boundaryX / 2, GL_LIGHT0);
Texture background, canon;
Stage stage;
int delete_probability;
float angle;
float speed;
int MTL_num;

Sound sound1("sound/BGM.wav", 1);
Sound sound2("sound/shoot.wav", 0);