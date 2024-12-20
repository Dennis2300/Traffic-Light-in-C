#include "pedestrian_lights.h"
#include "delay.h"

#define NS_PED_RED  (1 << 2)
#define NS_PED_GREEN (1 << 3)
#define EW_PED_RED (1 << 5)
#define EW_PED_GREEN (1 << 6)

#define NS_PED_BUTTON (1 << 4)
#define EW_PED_BUTTON (1 << 7)

volatile int ns_ped_request = 0;
volatile int ew_ped_request = 0;

void setup_pedestrian_lights(void) {
    DDRD |= (NS_PED_RED | NS_PED_GREEN | EW_PED_RED | EW_PED_GREEN); // Set pedestrian lights as outputs
    DDRD &= ~(NS_PED_BUTTON | EW_PED_BUTTON); // Set buttons as inputs
    PORTD |= (NS_PED_BUTTON | EW_PED_BUTTON); // Enable pull-ups for buttons

    // Start with all red lights
    PORTD |= (NS_PED_RED | EW_PED_RED);
}

void check_pedestrian_buttons(void) {
    if (!(PIND & NS_PED_BUTTON)) {
        ns_ped_request = 1;
    }
    if (!(PIND & EW_PED_BUTTON)) {
        ew_ped_request = 1;
    }
}

void handle_pedestrian_lights(void) {
    if (ns_ped_request) {
        ns_ped_request = 0;
        PORTD &= ~NS_PED_RED;
        PORTD |= NS_PED_GREEN;
        delay_ms(3000);
        PORTD &= ~NS_PED_GREEN;
        PORTD |= NS_PED_RED;
    }

    if (ew_ped_request) {
        ew_ped_request = 0;
        PORTD &= ~EW_PED_RED;
        PORTD |= EW_PED_GREEN;
        delay_ms(3000);
        PORTD &= ~EW_PED_GREEN;
        PORTD |= EW_PED_RED;
    }
}
