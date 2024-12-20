#include "traffic_lights.h"
#include "pedestrian_lights.h"
#include "delay.h"

int main() {
    setup_traffic_lights();
    setup_pedestrian_lights();

    while (1) {
        check_pedestrian_buttons();
        handle_pedestrian_lights();
        traffic_light_sequence();
    }

    return 0;
}
