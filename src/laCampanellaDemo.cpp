#include "../include/soundDriver.h"

void laCampanella()
{
    const int BPM = 150;
    const int TIME_SIGNATURE = 4; // 4 for 4/4, 3 for 3/4, etc
    double WN_LENGTH_MS = (double)60000/(double)BPM * (double)TIME_SIGNATURE;

    double WHOLE_NOTE     = WN_LENGTH_MS*Music::_WN;
    double HALF_NOTE      = WN_LENGTH_MS*Music::_HN;
    double QUARTER_NOTE   = WN_LENGTH_MS*Music::_QN;
    double EIGHT_NOTE     = WN_LENGTH_MS*Music::_EN;
    double SIXTEENTH_NOTE = WN_LENGTH_MS*Music::_SN;

    auto _DS =  [](int octave, double length)
    {
        Music::playPWM(Music::DS,octave,length, PWM_PIN);
    };
    
    while (1)
    {
        _DS(6,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
        _DS(6,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::CS,5,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::B,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::B,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::AS,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::GS,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::G,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::GS,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);
        Music::playPWM(Music::AS,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(6,SIXTEENTH_NOTE);

        _DS(5,SIXTEENTH_NOTE);
        _DS(4,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
        _DS(4,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::E,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        _DS(4,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::CS,4,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::B,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::B,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::AS,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::GS,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::G,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::GS,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        Music::playPWM(Music::AS,3,SIXTEENTH_NOTE, PWM_PIN);
        _DS(5,SIXTEENTH_NOTE);
        _DS(4,SIXTEENTH_NOTE);
        _DS(5,SIXTEENTH_NOTE);
    };
};

int main() 
{
    Utility::powerUpSound = false;
    Utility::powerOn();
    laCampanella();
    Utility::powerOff();
    return 0;
};
