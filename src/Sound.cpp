#include "Sound.h"

    void Sound::SetState(Sound::States s){
        if(s == Sound::ON){
            State = true;
        }
        else{
            State = false;
        }
    }

   Sound::States Sound::GetState(){
        if(State == true){
            return ON;
        }
        else{
            return OFF;
        }
    }