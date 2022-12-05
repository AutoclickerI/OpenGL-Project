#include "Sound.h"

FMOD_SYSTEM* Sound::g_sound_system;


Sound::Sound(const char* p, bool l) {

    if (loop) {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
    }
    else {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_OFF, 0, &m_sound);
    }

    loop = l;
    path = p;

    m_channel = nullptr;
    m_volume = SOUND_DEFAULT;
}



void Sound::initsound(bool run) {

    result = FMOD::System_Create(&system);
    result = system->getVersion(&version);

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    if (loop) {
        result = system->createSound(path, FMOD_LOOP_NORMAL, 0, &soundfile);
    }
    else {
        result = system->createSound(path, FMOD_LOOP_OFF, 0, &soundfile);

    }
    if (run)
        result = system->playSound(soundfile, 0, false, &channel);

}


void Sound::updatesound() {
    result = system->update();
}

void Sound::playsound() {
    result = system->playSound(soundfile, 0, false, &channel);
}

void Sound::pausesound() {
    result = channel->setPaused(true);

}
void Sound::resumesound() {
    result = channel->setPaused(false);

}


void Sound::releasesound() {
    system->release();
}