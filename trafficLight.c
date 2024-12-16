// These lines define the bits for the traffic light.
#define NS_RED     (1 << 0)
#define NS_YELLOW  (1 << 1)
#define NS_GREEN   (1 << 2)
#define EW_RED     (1 << 3)
#define EW_YELLOW  (1 << 4)
#define EW_GREEN   (1 << 5)

// These lines define the PORTD register.
// volatile is used to prevent the compiler from optimizing the code.
// We use volatile because the PORTD register is a memory-mapped I/O register. which it can change at any time.
volatile unsigned char PORTD = 0;

// These lines define the functions to turn on and off the bits.
#define TURN_ON(port, bit)  ((port) |= (bit))
#define TURN_OFF(port, bit) ((port) &= ~(bit))

// This function creates a delay in milliseconds.
void delay_ms(unsigned int milliseconds) { // milliseconds is the number of milliseconds to delay.
    volatile unsigned int outerCounter, innerCounter; // outerCounter and innerCounter are used as counters.
    for (outerCounter = 0; outerCounter < milliseconds; outerCounter++) { // outerCounter is the outer loop counter.
        for (innerCounter = 0; innerCounter < 1000; innerCounter++) { // innerCounter is the inner loop counter.
        }
    }
}
// the outer loop counter counts from 0 to milliseconds.
// the inner loop counter counts from 0 to 1000.

// These lines define the functions to set the traffic light.
//-------------------------------------------------------------------//
// This sets NS_RED on and NS_YELLOW and NS_GREEN off.
#define SET_NS_RED() { TURN_ON(PORTD, NS_RED); TURN_OFF(PORTD, NS_YELLOW | NS_GREEN); }
// This sets NS_YELLOW on and NS_RED and NS_GREEN off.
#define SET_NS_YELLOW() { TURN_ON(PORTD, NS_YELLOW); TURN_OFF(PORTD, NS_GREEN); }
// This sets NS_GREEN on and NS_RED and NS_YELLOW off.
#define SET_NS_GREEN()  { TURN_ON(PORTD, NS_GREEN); TURN_OFF(PORTD, NS_RED | NS_YELLOW); }

// This sets EW_RED on and EW_YELLOW and EW_GREEN off.
#define SET_EW_RED()    { TURN_ON(PORTD, EW_RED); TURN_OFF(PORTD, EW_YELLOW | EW_GREEN); }
// This sets EW_YELLOW on and EW_RED and EW_GREEN off.
#define SET_EW_YELLOW() { TURN_ON(PORTD, EW_YELLOW); TURN_OFF(PORTD, EW_GREEN); }
// This sets EW_GREEN on and EW_RED and EW_YELLOW off.
#define SET_EW_GREEN()  { TURN_ON(PORTD, EW_GREEN); TURN_OFF(PORTD, EW_RED | EW_YELLOW); }

// This is the main function.
void main() {
    // Both NS and EW are red.
    SET_NS_RED();
    SET_EW_RED();
    delay_ms(5000); // Wait for 5 seconds.

    while (1) { // means while loop is true. and run forever.
        SET_NS_YELLOW(); // NS is yellow.
        delay_ms(2000); // Wait for 2 seconds.

        SET_NS_GREEN(); // NS is green.
        delay_ms(5000); // Wait for 5 seconds.

        SET_NS_YELLOW(); // NS is yellow.
        delay_ms(2000); // Wait for 2 seconds.

        SET_NS_RED(); // NS is red.
        delay_ms(2000);

        SET_EW_YELLOW(); // now EW is yellow.
        delay_ms(2000);

        SET_EW_GREEN(); // now EW is green.
        SET_NS_RED(); // NS is red.
        delay_ms(5000);

        SET_EW_YELLOW(); // now EW is yellow.
        delay_ms(2000);

        SET_NS_RED();// NS is red.
        SET_EW_RED();// EW is red.
        delay_ms(2000);
    }
}
