#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define Led_vermelho 13
#define Led_Amarelo 12
#define Led_Verde 11

volatile int state = 0;

bool repeating_timer_callback(struct repeating_timer *t)
{
    gpio_put(Led_vermelho, state == 0);
    gpio_put(Led_Amarelo, state == 1);
    gpio_put(Led_Verde, state == 2);

    state = (state +1) % 3;
    return true;
};

int main()
{
    stdio_init_all();

    gpio_init(Led_vermelho);
    gpio_set_dir(Led_vermelho, GPIO_OUT);
        gpio_init(Led_Amarelo);
    gpio_set_dir(Led_Amarelo, GPIO_OUT);
        gpio_init(Led_Verde);
    gpio_set_dir(Led_Verde, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Semaforo Funcionando...\n");
        sleep_ms(1000);
    }
}
