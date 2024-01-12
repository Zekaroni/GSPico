#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <cmath>

#define GPIO_ON    1
#define GPIO_OFF   0
#define GPIO_OUT   1
#define GPIO_IN    0

#define PWM_PIN   10
#define LED_PIN   25

// First Octave (Thanks to MTU https://pages.mtu.edu/~suits/notefreqs.html)
const double C  = 16.35;
const double CS = 17.32;
const double D  = 18.35;
const double DS = 19.45;
const double E  = 20.60;
const double F  = 21.83;
const double FS = 23.12;
const double G  = 24.50;
const double GS = 25.96;
const double A  = 27.50;
const double AS = 29.14;
const double B  = 30.87;

const double* notes[] = {&C, &CS, &D, &DS, &E, &F, &FS, &G, &GS, &A, &AS, &B};


#define WN = 1.0000;
#define HN = 0.5000;
#define QN = 0.2500;
#define EN = 0.1250;
#define SN = 0.0625;

#define rest(time_ms){sleep_ns(time_ms);};

const int NULL_PIN = -1;
const uint8_t DAC_BIT_DEPTH = 5;
const uint8_t DAC_MAX_VALUE = 31;
const uint8_t DAC_PIN_0 = 5; // 0b00000001
const uint8_t DAC_PIN_1 = 6; // 0b00000010
const uint8_t DAC_PIN_2 = 7; // 0b00000100
const uint8_t DAC_PIN_3 = 8; // 0b00001000
const uint8_t DAC_PIN_4 = 9; // 0b00010000
// const uint8_t DAC_PIN_5 = 4; // 0b00100000
// const uint8_t DAC_PIN_6 = 3; // 0b01000000
// const uint8_t DAC_PIN_7 = 2; // 0b10000000

const uint8_t* DAC_PINS[] = {&DAC_PIN_0,&DAC_PIN_1,&DAC_PIN_2,&DAC_PIN_3,&DAC_PIN_4};

const double pi = 3.14159;

void sleep_ns(long duration)
{ // Will be in muliples of 8ns??
    // NOTE: This does not scale to clock of the CPU
    duration *= 1000; // convert ms to ns
    // TODO: Figure out this magic number
    int cycles = duration/39.8;
    for (int i = 0; i < cycles; i++)
    {
        __asm volatile ("nop\n");
    };
};

void initDAC()
{
    uint8_t pin;
    for (int i = 0; i < DAC_BIT_DEPTH; i++)
    {
        pin = *DAC_PINS[i];
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    };
};

void writeDACValue(int value)
{
    for (int o = 0; o < DAC_BIT_DEPTH; o++)
    {
        gpio_put(*DAC_PINS[o], ((int)value >> o) & 0b1);
    };
};


double calculateNoteFrequency(double baseFrequency, int octaveShift)
{
    double frequency = baseFrequency;
    for (int i = 0; i < octaveShift; i++)
    {
        frequency *= 2;
    };
    return frequency;
};

void playFrequency(double frequency, long duration, int pin)
{
    int period_us = static_cast<int>(1e6 / frequency);
    int half_period_us = period_us / 2;

    duration*=1000;

    int iterations = duration / period_us;

    for (int i = 0; i < iterations; i++)
    {
        gpio_put(pin, GPIO_ON);
        sleep_ns(half_period_us);
        gpio_put(pin, GPIO_OFF);
        sleep_ns(half_period_us);
    };
};

void playPWM(double note, int octave, long duration, int pin)
{
    double frequency = calculateNoteFrequency(note, octave);
    int period_us = static_cast<int>(1e6 / frequency);
    int half_period_us = period_us / 2;

    duration*=1000;

    int iterations = duration / period_us;

    for (int i = 0; i < iterations; i++)
    {
        gpio_put(pin, GPIO_ON);
        sleep_ns(half_period_us);
        gpio_put(pin, GPIO_OFF);
        sleep_ns(half_period_us);
    };
};


void playTriangle(double note, int octave, long duration, int pin)
{
    // NOTE:
    //  - ~2872Hz with 8-bit DAC using current methods
    //  - Offset by 90 degrees
    double frequency = calculateNoteFrequency(note,octave);
    int steps = std::pow(2, DAC_BIT_DEPTH)*2-2;
    double delay = (((double)1 /  frequency) * (1/(double)steps) * 1000000);
    int itterations = (duration * 1000)/(delay)/steps;
    for (int i = 0; i < itterations; i++)
    {
        for (int down_value = DAC_MAX_VALUE; down_value > 0; down_value--)
        {
            writeDACValue(down_value);
            sleep_ns(delay);
        };
        for (int up_value = 0; up_value < DAC_MAX_VALUE; up_value++)
        {
            writeDACValue(up_value);
            sleep_ns(delay);
        };
    };
};

void playSawtooth(double note, int octave, long duration, int pin)
{
    double frequency = calculateNoteFrequency(note,octave);
    int steps = std::pow(2, DAC_BIT_DEPTH)*2-2;
    double delay = (((double)1 /  frequency) * (1/(double)steps) * 1000000);
    int itterations = (duration * 1000)/(delay)/steps;
    for (int i = 0; i < itterations; i++)
    {
        for (int down_value = DAC_MAX_VALUE; down_value > 0; down_value--)
        {
            writeDACValue(down_value);
            sleep_ns(delay);
        };
        for (int up_value = 0; up_value < DAC_MAX_VALUE; up_value++)
        {
            writeDACValue(up_value);
            sleep_ns(delay);
        };
    };
};


void arpegiateTriad(void (&func)(double, int, long, int),double note1, double note2, double note3, int start_octave, int end_octave, int rate, int pin)
{
    // NOTE: Add logic if note 2 and/or 3 wrap around to +1 or -1 octave
    int octave = start_octave;
    while (octave < end_octave)
    {
        func(note1, octave, rate, pin);
        func(note2, octave, rate, pin);
        func(note3, octave, rate, pin);
        octave++;
    };
    while (octave > start_octave)
    {
        func(note3, octave, rate, pin);
        func(note2, octave, rate, pin);
        func(note1, octave, rate, pin);
        octave--;
    };
};

void climbScales(int start_octave, int end_octave)
{
    int octave = start_octave;
    while (1)
    {
        for (int i = 0; i < 12; i++)
        {
            playTriangle(*notes[i], octave,20,DAC_PIN_0);
        };
        if (octave < end_octave)
        {
            octave++;
        } else
        {
            octave = 0;
        };
    };
};

void powerOnSound(int pin, void (&func)(double, int, long, int) = playPWM)
{
    arpegiateTriad(func,D,F,GS,2,5,60, pin);
    arpegiateTriad(func,G,C,D,2,5,60, pin);
    arpegiateTriad(func,C,E,G,2,5,60, pin);
};



// void generateSine(double frequency, int duration)
// {
//     double sine;
//     int value;
//     const int sample_rate = 13000;
//     int num_samples = duration * sample_rate / 1000;
//     for (int i = 0; i < num_samples; i++)
//     {
//         sine = std::sin(i * (pi/ 180) * (2 * pi * frequency / sample_rate));
//         value = std::round(((sine+1)/2)*DAC_MAX_VALUE);
//         writeDACValue(value);
//     };
//     writeDACValue(0);
// };

void risingSaw()
{
    int itterations = 1000; // TODO: Calc
    for (int i = 0; i < itterations; i++)
    {
        // Skip storing to reduce clock cycles
        writeDACValue(i % 32);
    };
};

void sinkingSaw()
{
    int value = DAC_MAX_VALUE;
    int itterations = 1000; // TODO: Calc
    for (int i = 0; i < itterations; i++)
    {
        if (value < 0)
        {
            value = DAC_MAX_VALUE;
        };
        writeDACValue(value);
        value--;
    };
};

void secondCoreStartup()
{
    playPWM(A,4,1000,PWM_PIN);
};

void powerOn()
{
    initDAC();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, GPIO_ON);
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_OUT);
    gpio_put(PWM_PIN, GPIO_OFF);
    // powerOnSound(PWM_PIN);
    // powerOnSound(NULL_PIN, playTriangle);
    writeDACValue(0);
};

void powerOff()
{
    gpio_put(LED_PIN, GPIO_OFF);
    writeDACValue(0);
};

int main() 
{
    powerOn();
    const int BPM = 120;
    const int TIME_SIGNATURE = 4; // 4 for 4/4, 3 for 3/4, etc
    double WN_LENGTH_MS = (double)60000/(double)BPM * (double)TIME_SIGNATURE;

    for (int i = 0; i < 20; i++)
    {
        playPWM(C,4,WN_LENGTH_MS,PWM_PIN);
        rest(WN_LENGTH_MS);
        playPWM(G,4,WN_LENGTH_MS,PWM_PIN);
        rest(WN_LENGTH_MS);
    };

    // multicore_launch_core1(secondCoreStartup);
    // writeDACValue(0);

    powerOff();
    return 0;
};
