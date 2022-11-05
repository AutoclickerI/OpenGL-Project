#pragma once
#include "fmod.hpp"
#include <iostream>
#include <conio.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

//using namespace FMOD;

class Sound {
public:
	Sound(const char* p, bool l);
	FMOD::System* system;
	FMOD::Sound* soundfile;
	FMOD::Channel* channel;

	/*
	void setpath(const char* p);
	const char* getpath() const;
	*/
	void initsound(bool run);
	void updatesound();
	void playsound();
	void releasesound();

	const char* path;
	bool loop;

	unsigned int version;
	void* extradriverdata;  // 본 예제에서는 사용 x

	static FMOD_SYSTEM* g_sound_system;
	FMOD_SOUND* m_sound;
	FMOD_CHANNEL* m_channel;

	float m_volume;
	FMOD_BOOL m_bool;
	FMOD_RESULT result;
};


/*


FMOD::System* system1(nullptr);
FMOD::System* system2(nullptr);
FMOD::Sound* bgm(nullptr);
FMOD::Sound* shoot(nullptr);

FMOD::Channel* channel1(nullptr);
FMOD::Channel* channel2(nullptr);

FMOD_RESULT result1;
FMOD_RESULT	result2;

unsigned int version;
void* extradriverdata(nullptr);  // 본 예제에서는 사용 x

void initsound() {
	result1 = FMOD::System_Create(&system1);
	result2 = FMOD::System_Create(&system2);


	result1 = system1->getVersion(&version);
	result2 = system2->getVersion(&version);

	printf("FMOD version %08x\n", version);


	result1 = system1->init(32, FMOD_INIT_NORMAL, extradriverdata);  // 시스템 초기화 : chaneel 32개까지 사용하겠다.
	result2 = system2->init(32, FMOD_INIT_NORMAL, extradriverdata);

	result1 = system1->createSound("sound/BGM.wav", FMOD_LOOP_NORMAL, 0, &bgm); // wav 파일로부터 sound 생성 , LOOP_NORMAL은 반복재생
	result2 = system2->createSound("sound/shoot1.wav", FMOD_LOOP_OFF, 0, &shoot); // wav 파일로부터 sound 생성, LOOP_OFF는 한번만재생

	result1 = system1->playSound(bgm, 0, false, &channel1); // 재생. 단 이때 딱 한번만 실행되므로 제대로 사운드가 끝까지 재생되지 않는다.  무한루프 안에서 시스템 객체를 계~~속 업데이트 시켜줘야 함.
	result2 = system2->playSound(shoot, 0, false, &channel2); // 재생. 단 이때 딱 한번만 실행되므로 제대로 사운드가 끝까지 재생되지 않는다.  무한루프 안에서 시스템 객체를 계~~속 업데이트 시켜줘야 함.
}

void updatesound() {
	result1 = system1->update();
	result2 = system2->update();
}

void playsound() {
	result2 = system2->playSound(shoot, 0, false, &channel2); // 재생. 단 이때 딱 한번만 실행되므로 제대로 사운드가 끝까지 재생되지 않는다.  무한루프 안에서 시스템 객체를 계~~속 업데이트 시켜줘야 함.

}

void releasesound() {
	system1->release();	// 프로그램이 끝난 후에는 리소스 릴리즈. 시스템 객체 해제.
	system2->release();
}


*/