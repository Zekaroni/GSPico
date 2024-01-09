#include <cmath>
#include <iostream>

int main()
{
    int DAC_BIT_DEPTH = 8;
    int DAC_MAX_VALUE = 255;
    double frequency = 440.00;
    int duration = 1000;
    int steps = std::pow(2, DAC_BIT_DEPTH)*2-2;
    double delay = (((double)1 /  frequency) * (1/(double)steps) * 1000000);
    int itterations = (duration * 1000)/(delay)/steps;
    for (int i = 0; i < 1; i++)
    {
        for (int down_value = DAC_MAX_VALUE; down_value > 0; down_value--)
        {
            std::cout << down_value << std::endl;
        };
        for (int up_value = 0; up_value < DAC_MAX_VALUE; up_value++)
        {
            std::cout << up_value <<std::endl;
        };
    };
    return 0; 
};