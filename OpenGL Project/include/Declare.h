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
enum Theme { SNU, Theme1, Theme2 };
enum SOUND { BGM, SHOOT };
enum MODE { MAINMENU, MOVING, BOOM, CHAIN_BOOM, DRAG, PAUSE };

using namespace std;

MODE mode;
Theme theme;
clock_t start_t = clock();
clock_t end_t;

vector<Sphere> shootings;
vector<Sphere> cannon;
vector<Sphere> stage_Sphere;
vector<pair<Sphere, pair<int, int>>> merge;
vector<int> merge_prograss;
vector<double> stage_Location;
vector<Material> materials;
vector<Sound> sound;
Light light(0, 0, boundaryX / 2, GL_LIGHT0);
Texture background, canon;
Stage stage;
int delete_probability;
float angle;
float moving_speed;// stage_sphere's moving speed
float speed;// cannon's shoot speed
int MTL_num, f, ccw;
int merge_step;
int boom_pos, boom_pos_end, boom_mtl, boom_stack, boom_pos_end_end;
int Frame;
int color_num;


Sound bgm("sound/BGM.wav", 1);
Sound shoot("sound/shoot1.wav", 0);