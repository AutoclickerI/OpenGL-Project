#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
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
enum SOUND { BGM, SHOOT, BOOMSOUND, STAGECLEAR, STAGEFAILED };
enum MODE { MAINMENU1, MAINMENU2, HIGHSCORE, SETTING, DEVELOPERS, GAMEMENU, MOVING, BOOM, CHAIN_BOOM, DRAG, CHAIN_DRAG, PAUSE, CLEAR, GAMEOVER, SCORESAVE };
enum STAGE { STAGE1, STAGE2, STAGE3, STAGE4, STAGE5 };
enum MANUAL { KEYBOARD1, KEYBOARD2, MOUSE };
enum DIFFICULTY { EASY, NORMAL, HARD };

using namespace std;

MODE mode;
Theme theme;
MANUAL manual;
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
Texture background, Pause, canon, clear, gameover, mainmenu1_1, mainmenu1_2, mainmenu2_1, mainmenu2_2, arrow, developers, highscore, scoresave, blackhole, whitehole;
Stage stage;
Sphere sphere1(30, 20, 20);
Sphere sphere2(sphere1);
int delete_probability;
float angle;
float moving_speed;// stage_sphere's moving speed
float speed;// cannon's shoot speed
STAGE STAGE_NOW;
DIFFICULTY difficulty;
unsigned long long score;
int MTL_num, f, ccw;
int merge_step;
int boom_pos, boom_pos_end, boom_mtl, boom_stack, boom_pos_end_end;
int arrow_pos, arrow_pos_2;
int pause = 0;
int level;
int Frame;
int color_num[3] = { 3,5,7 };
const float scaleFactor = 300.0f;
vector<string> ordnum{ " 1st"," 2nd"," 3rd"," 4th"," 5th"," 6th"," 7th"," 8th"," 9th","10th" };

fstream iscore("score/top10.ini");
string word;
int number;
vector<string> playername(20);
vector<string> difficultydata(20);
vector<int> scoredata(20);
bool scorechange = 0;
vector<char> currentplayer(100);
string fullname = "XXX";
int ranking;







Sound bgm("sound/BGM.wav", 1);
Sound shoot("sound/shoot1.wav", 0);
Sound boomsound("sound/boomsound.wav", 0);
Sound stageclear("sound/stageclear.wav", 0);
Sound stagefailed("sound/stagefailed.wav", 0);