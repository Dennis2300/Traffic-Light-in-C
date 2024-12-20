#include "traffic_lights.h"
#include "delay.h"

#define NS_RED    (1 << 5)
#define NS_YELLOW (1 << 4)
#define NS_GREEN  (1 << 3)
#define EW_RED    (1 << 2)
#define EW_YELLOW (1 << 1)
#define EW_GREEN  (1 << 0)

void setup_traffic_lights(void) {
    DDRB = 0xFF; // Set all PORTB pins as outputs
    PORTB = NS_RED | EW_RED; // Start with all red lights
}

void traffic_light_sequence(void) {
    // NS: RED | EW: GREEN
    PORTB = NS_RED | EW_GREEN;
    delay_ms(5000);

    // NS: GREEN | EW: RED
    PORTB = NS_GREEN | EW_RED;
    delay_ms(5000);

    // NS: YELLOW | EW: RED
    PORTB = NS_YELLOW | EW_RED;
    delay_ms(2000);

    // Back to NS: RED | EW: GREEN
    PORTB = NS_RED | EW_GREEN;
    delay_ms(5000);
}
