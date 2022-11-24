#pragma once
#include "fmod.h"
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

	void initsound(bool run);
	void updatesound();
	void playsound();
	void pausesound();
	void resumesound();
	void releasesound();

	const char* path;
	bool loop;

	unsigned int version;
	void* extradriverdata; 

	static FMOD_SYSTEM* g_sound_system;
	FMOD_SOUND* m_sound;
	FMOD_CHANNEL* m_channel;

	float m_volume;
	FMOD_BOOL m_bool;
	FMOD_RESULT result;
};