#pragma once
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
enum Theme { SNU, SPACE, CANDY };
enum SOUND { BGM, SHOOT, BOOMSOUND, STAGECLEAR, STAGEFAILED, BUTTON, ITEMSOUND };
enum MODE { PREMAINMENU, MAINMENU1, MAINMENU2, HIGHSCORE, SETTING, DEVELOPERS, GAMEMENU, MOVING, BOOM, CHAIN_BOOM, DRAG, CHAIN_DRAG, PAUSE, CLEAR, GAMEOVER, SCORESAVE };
enum STAGE { STAGE1, STAGE2, STAGE3, STAGE4, STAGE5 };
enum MANUAL { KEYBOARD1, KEYBOARD2, MOUSE };
enum COLORMODE { PRIMARY, COLORBLIND };
enum DIFFICULTY { EASY, NORMAL, HARD };

using namespace std;

MODE mode;
Theme theme;
MANUAL manual;
clock_t start_t = clock();
clock_t end_t;
clock_t item_t;

vector<Sphere> shootings;
vector<Sphere> cannon;
vector<Sphere> stage_Sphere;
vector<pair<Sphere, pair<int, int>>> merge;
vector<int> merge_prograss;
vector<double> stage_Location;
vector<Material> materials;
vector<Sound> sound;
Light light(0, 0, boundaryX / 2, GL_LIGHT0);
Texture background, Pause, canon, clear, gameover, premainmenu_1, premainmenu_2, mainmenu1_1, mainmenu1_2, mainmenu2_1, mainmenu2_2,
arrow, arrow_2, settings_1, settings_2, developers, highscore, scoresave, blackhole, whitehole;
Stage stage;
COLORMODE colormode;
Sphere sphere1(30, 20, 20);
Sphere sphere2(sphere1);
int delete_probability;
float angle;
float moving_speed;// stage_sphere's moving speed
STAGE STAGE_NOW;
DIFFICULTY difficulty;
unsigned long long score;
int MTL_num, f, ccw;
int boom_pos, boom_pos_end, boom_mtl, boom_stack, boom_pos_end_end;
int arrow_pos, arrow_pos_2;
pair<int, bool> arrow_pos_3;
bool pause = 0;
bool musicpause = 0;
int level;
int Frame;
int color_num[3] = { 3,5,7 };
vector<string> ordnum{ " 1st"," 2nd"," 3rd"," 4th"," 5th"," 6th"," 7th"," 8th"," 9th","10th" };
string word;
int number;
vector<string> playername(20);
vector<string> difficultydata(20);
vector<int> scoredata(20);
vector<char> currentplayer(10);
bool scorechange = 0;
string fullname = "XXX";
int ranking;
bool item = 1;
bool velocityrevert = 0;
ifstream iscore("config.ini");
string trash;

Sound bgm("sound/BGM.mp3", 1);
Sound shoot("sound/shoot.wav", 0);
Sound boomsound("sound/boomsound.wav", 0);
Sound stageclear("sound/stageclear.wav", 0);
Sound stagefailed("sound/stagefailed.wav", 0);
Sound button("sound/button.mp3", 0);
Sound itemsound("sound/itemsound.mp3", 0);