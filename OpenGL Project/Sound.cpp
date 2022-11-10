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
    //FMOD_System_Create(&g_sound_system, 00020210);
    //FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, extradriverdata);


    result = FMOD::System_Create(&system);
    result = system->getVersion(&version);
    printf("FMOD version %08x\n", version);

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    if (loop) {
        result = system->createSound(path, FMOD_LOOP_NORMAL, 0, &soundfile); // wav 파일로부터 sound 생성 , LOOP_NORMAL은 반복재생
    }
    else {
        result = system->createSound(path, FMOD_LOOP_OFF, 0, &soundfile); // wav 파일로부터 sound 생성 , LOOP_NORMAL은 반복재생

    }
    if (run)
        result = system->playSound(soundfile, 0, false, &channel); // 재생. 단 이때 딱 한번만 실행되므로 제대로 사운드가 끝까지 재생되지 않는다.  무한루프 안에서 시스템 객체를 계~~속 업데이트 시켜줘야 함.



}
/*
const char* Sound::getpath() const{
    return path;
}

void Sound::setpath(const char* p) {
    path = p;
}

*/

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