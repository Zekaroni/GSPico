#include <stdio.h>
#include "../include/soundDriver.h"

namespace Tetris
{
    const int BPM = 149;
    const int TIME_SIGNATURE = 4; // 4 for 4/4, 3 for 3/4, etc
    double WN_LENGTH_MS = (double)60000/(double)BPM * (double)TIME_SIGNATURE;

    double WHOLE_NOTE     = WN_LENGTH_MS*Music::_WN;
    double HALF_NOTE      = WN_LENGTH_MS*Music::_HN;
    double QUARTER_NOTE   = WN_LENGTH_MS*Music::_QN;
    double EIGHTH_NOTE     = WN_LENGTH_MS*Music::_EN;
    double SIXTEENTH_NOTE = WN_LENGTH_MS*Music::_SN;
    double THIRTYSECOND_NOTE = WN_LENGTH_MS*Music::_TN;

    auto EE = []()
    {
        Music::playTriangle(Music::E,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
        Music::playTriangle(Music::E,3,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
    };
    auto AA = []()
    {
        Music::playTriangle(Music::A,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
        Music::playTriangle(Music::A,3,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
    };

    auto GSGS = []()
    {
        Music::playTriangle(Music::GS,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
        Music::playTriangle(Music::GS,3,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
    };
};

void tetris()
{
    auto PWM_CHANNEL = []()
    {
        // Bar 1
        Utility::pushData();
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::B,4,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::D,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::B,4,Tetris::EIGHTH_NOTE,PWM_PIN);
        
        // Bar 2
        Utility::pushData();
        Music::playPWM(Music::A,4,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,PWM_PIN);
        Music::rest(Tetris::THIRTYSECOND_NOTE);
        Music::playPWM(Music::A,4,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::D,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);

        // Bar 3
        Utility::pushData();
        Music::playPWM(Music::B,4,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,PWM_PIN);
        Music::rest(Tetris::THIRTYSECOND_NOTE);
        Music::playPWM(Music::B,4,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::D,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE,PWM_PIN);

        // Bar 4
        Utility::pushData();
        Music::playPWM(Music::C,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::A,4,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,PWM_PIN);
        Music::rest(Tetris::THIRTYSECOND_NOTE);
        Music::playPWM(Music::A,4,Tetris::HALF_NOTE,PWM_PIN);

        // Bar 5
        Utility::pushData();
        Music::rest(Tetris::EIGHTH_NOTE);
        Music::playPWM(Music::D,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::F,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::A,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::G,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::F,5,Tetris::EIGHTH_NOTE,PWM_PIN);

        // Bar 6
        Utility::pushData();
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE+Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::D,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);

        // Bar 7
        Utility::pushData();
        Music::playPWM(Music::B,4,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,PWM_PIN);
        Music::rest(Tetris::THIRTYSECOND_NOTE);
        Music::playPWM(Music::B,4,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::C,5,Tetris::EIGHTH_NOTE,PWM_PIN);
        Music::playPWM(Music::D,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::E,5,Tetris::QUARTER_NOTE,PWM_PIN);

        // Bar 8
        Utility::pushData();
        Music::playPWM(Music::C,5,Tetris::QUARTER_NOTE,PWM_PIN);
        Music::playPWM(Music::A,4,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,PWM_PIN);
        Music::rest(Tetris::THIRTYSECOND_NOTE);
        Music::playPWM(Music::A,4,Tetris::HALF_NOTE,PWM_PIN);
    };


    auto bass = []()
    {
        while (1)
        {
            // Bar 1
            Utility::waitForData();
            Tetris::EE();
            Tetris::EE();
            Tetris::EE();
            Tetris::EE();

            // Bar 2
            Utility::waitForData();
            Tetris::AA();
            Tetris::AA();
            Tetris::AA();
            Tetris::AA();

            // Bar 3
            Utility::waitForData();
            Tetris::GSGS();
            Tetris::GSGS();
            Tetris::EE();
            Tetris::EE();

            // Bar 4
            Utility::waitForData();
            Tetris::AA();
            Tetris::AA();
            Tetris::AA();
            Music::playTriangle(Music::B,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::C,3,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);

            // Bar 5
            Utility::waitForData();
            Music::playTriangle(Music::D,3,Tetris::EIGHTH_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::D,2,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::D,2,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::D,2,Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::D,2,Tetris::SIXTEENTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::A,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::F,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);

            // Bar 6
            Utility::waitForData();
            Music::playTriangle(Music::C,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::C,3,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::C,3,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::C,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::G,2,Tetris::EIGHTH_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::G,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::A,2,Tetris::EIGHTH_NOTE,DAC::NULL_PIN);

            // Bar 7
            Utility::waitForData();
            Music::playTriangle(Music::B,2,Tetris::HALF_NOTE,DAC::NULL_PIN);
            Music::playTriangle(Music::E,2,Tetris::HALF_NOTE,DAC::NULL_PIN);

            // Bar 8
            Utility::waitForData();
            Music::playTriangle(Music::A,2,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::A,2,Tetris::QUARTER_NOTE-Tetris::THIRTYSECOND_NOTE,DAC::NULL_PIN);
            Music::rest(Tetris::THIRTYSECOND_NOTE);
            Music::playTriangle(Music::A,2,Tetris::HALF_NOTE,DAC::NULL_PIN);
        };
    };

    multicore_launch_core1(bass);
    while (1)
    {
        PWM_CHANNEL();
        printf("Re-looping");
    };
};

int main() 
{
    stdio_init_all();
    Utility::powerUpSound = false;
    Utility::powerOn();
    tetris();
    Utility::powerOff();
    return 0;
};
