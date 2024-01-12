#include "../include/soundDriver.h"

void longLongTime()
{
    const int BPM = 120;
    const int TIME_SIGNATURE = 4; // 4 for 4/4, 3 for 3/4, etc
    double WN_LENGTH_MS = (double)60000/(double)BPM * (double)TIME_SIGNATURE;

    double WHOLE_NOTE     = WN_LENGTH_MS*Music::_WN;
    double HALF_NOTE      = WN_LENGTH_MS*Music::_HN;
    double QUARTER_NOTE   = WN_LENGTH_MS*Music::_QN;
    double EIGHT_NOTE     = WN_LENGTH_MS*Music::_EN;
    double SIXTEENTH_NOTE = WN_LENGTH_MS*Music::_SN;
    
    Music::playPWM(Music::B,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::AS,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::A,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::G,4,QUARTER_NOTE, PWM_PIN);
    Music::playPWM(Music::B,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::D,5,QUARTER_NOTE, PWM_PIN);
    Music::playPWM(Music::G,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::FS,4,QUARTER_NOTE, PWM_PIN);
    Music::playPWM(Music::B,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::D,5,QUARTER_NOTE, PWM_PIN);
    Music::playPWM(Music::FS,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::E,4,QUARTER_NOTE, PWM_PIN);
    Music::playPWM(Music::FS,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::E,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::FS,4,EIGHT_NOTE, PWM_PIN);
    Music::playPWM(Music::E,4,HALF_NOTE, PWM_PIN);
};

int main() 
{
    Utility::powerUpSound = false;
    Utility::powerOn();
    longLongTime();
    Utility::powerOff();
    return 0;
};
