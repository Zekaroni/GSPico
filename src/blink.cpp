#include "pico/stdlib.h"

#define GPIO_ON    1
#define GPIO_OFF   0
#define GPIO_OUT   1

void initializeAllPins(int* pins[], int value)
{
    for (int i = 0; pins[i] != NULL; i++)
    {
        gpio_init(*(pins[i]));
        gpio_set_dir(*(pins[i]), value);
    };
};

void setAllPins(int* pins[], int value)
{
    for (int i = 0; pins[i] != NULL; i++)
    {
        gpio_put(*(pins[i]), value);
    };
};

int main()
{
    int LED_PIN   = 25;
    int RED_PIN   = 18;
    int GREEN_PIN = 19;
    int BLUE_PIN  = 20;
    int TEST_LED  = 21;

    int* PINS[] = {&LED_PIN, &RED_PIN, &GREEN_PIN, &BLUE_PIN, &TEST_LED, NULL};

    initializeAllPins(PINS, GPIO_OUT);

    while (true)
    {
        gpio_put(RED_PIN, GPIO_ON);
        sleep_ms(1000);
        gpio_put(RED_PIN, GPIO_OFF);
        gpio_put(GREEN_PIN, GPIO_ON);
        sleep_ms(1000);
        gpio_put(GREEN_PIN, GPIO_OFF);
        gpio_put(BLUE_PIN, GPIO_ON);
        sleep_ms(1000);
        gpio_put(BLUE_PIN, GPIO_OFF);
    };

    return 0;
}
