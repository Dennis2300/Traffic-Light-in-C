#define NS_RED     (1 << 0)
#define NS_YELLOW  (1 << 1)
#define NS_GREEN   (1 << 2)
#define EW_RED     (1 << 3)
#define EW_YELLOW  (1 << 4)
#define EW_GREEN   (1 << 5)

volatile unsigned char PORTD = 0;

#define TURN_ON(port, bit)  ((port) |= (bit))
#define TURN_OFF(port, bit) ((port) &= ~(bit))

void delay_ms(unsigned int ms) {
    volatile unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1000; j++) {
        }
    }
}

#define SET_NS_RED()    { TURN_ON(PORTD, NS_RED); TURN_OFF(PORTD, NS_YELLOW | NS_GREEN); }
#define SET_NS_YELLOW() { TURN_ON(PORTD, NS_YELLOW); TURN_OFF(PORTD, NS_GREEN); }
#define SET_NS_GREEN()  { TURN_ON(PORTD, NS_GREEN); TURN_OFF(PORTD, NS_RED | NS_YELLOW); }

#define SET_EW_RED()    { TURN_ON(PORTD, EW_RED); TURN_OFF(PORTD, EW_YELLOW | EW_GREEN); }
#define SET_EW_YELLOW() { TURN_ON(PORTD, EW_YELLOW); TURN_OFF(PORTD, EW_GREEN); }
#define SET_EW_GREEN()  { TURN_ON(PORTD, EW_GREEN); TURN_OFF(PORTD, EW_RED | EW_YELLOW); }

void main() {
    SET_NS_RED();
    SET_EW_RED();
    delay_ms(5000);

    while (1) {
        SET_NS_YELLOW();
        delay_ms(2000);

        SET_NS_GREEN();
        SET_EW_RED();
        delay_ms(5000);

        SET_NS_YELLOW();
        delay_ms(2000);

        SET_NS_RED();
        SET_EW_RED();
        delay_ms(2000);

        SET_EW_YELLOW();
        delay_ms(2000);

        SET_EW_GREEN();
        SET_NS_RED();
        delay_ms(5000);

        SET_EW_YELLOW();
        delay_ms(2000);

        SET_NS_RED();
        SET_EW_RED();
        delay_ms(2000);
    }
}
