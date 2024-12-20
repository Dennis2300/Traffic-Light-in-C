// We assaign a bit to each pin on the arduino eg. pin D13 to pin D8
// That way we can control the traffic light with the bits
// Each pin has a 8 bit binary number
// To determine which pin on the Arduino we simply look at the order
// Since we start with the largest number first, 
// we now that the first pin is D13 which is the last pin on the Arduino
// and each binary we assign is the next pin in order eg. D12, D11, D10, D9, D8
#define NS_RED    (1 << 5) // 1 << 5 = 0b00100000 = 32
#define NS_YELLOW (1 << 4) // 1 << 4 = 0b00010000 = 16
#define NS_GREEN  (1 << 3) // 1 << 3 = 0b00001000 = 8
#define EW_RED    (1 << 2) // 1 << 2 = 0b00000100 = 4
#define EW_YELLOW (1 << 1) // 1 << 1 = 0b00000010 = 2
#define EW_GREEN  (1 << 0) // 1 << 0 = 0b00000001 = 1
// Where 0b is a prefix to indicate the following number is a binary number

#define NS_PED_RED  (1 << 2) // 1 << 2 = 0b00000100 = 4
#define NS_PED_GREEN (1 << 3) // 1 << 3 = 0b00001000 = 8
#define EW_PED_RED (1 << 5) // 1 << 6 = 0b01000000 = 64
#define EW_PED_GREEN (1 << 6) // 1 << 7 = 0b10000000 = 128

#define NS_PED_BUTTON (1 << 4) // 1 << 4 = 0b00010000 = 16
#define EW_PED_BUTTON (1 << 7) // 1 << 5 = 0b00100000 = 32

// The duration of each light
// We define the duration of each light in milliseconds
#define GREEN_DURATION 500
#define YELLOW_DURATION 200
#define RED_DURATION 500
#define RED_OVERLAP_DURATION 500
#define PED_DELAY 5000

// Here we define the name DDRB, if DDRB gets called with a value
// it will go to the address 0x24 and modify the 8 bits at that address
#define DDRB *((volatile unsigned char*)0x24)
// Here we define the name PORTB, if PORTB gets called with a value
// it will go to the address 0x25 and modify the 8 bits at that address
#define PORTB *((volatile unsigned char*)0x25)
#define PINB *((volatile unsigned char*)0x23)

#define DDRD *((volatile unsigned char*)0x2A)
#define PORTD *((volatile unsigned char*)0x2B)
#define PIND *((volatile unsigned char*)0x29)

// delay function in milliseconds
void delay_ms(unsigned long ms) {
    volatile unsigned long i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 800; j++) {
        }
    }
}

int main() {
    DDRB = 0xFF; // we set all pins to 11111111 which means all pins are output

	DDRD = NS_PED_RED | NS_PED_GREEN | EW_PED_RED | EW_PED_GREEN;

	DDRD = DDRD & ~(NS_PED_BUTTON | EW_PED_BUTTON);

	PORTD = NS_PED_BUTTON | EW_PED_BUTTON;

// The traffic light will run in an infinite loop
    while (1) { // where (1) is always true so the loop will run forever

	if (!(PIND & NS_PED_BUTTON)) {
		PORTD |= NS_PED_RED | NS_PED_GREEN;
	} else {
		PORTD &= ~(NS_PED_RED | NS_PED_GREEN);
	}

	if (!(PIND & EW_PED_BUTTON)) {
		PORTD |= EW_PED_RED | EW_PED_GREEN;
	} else {
		PORTD &= ~(EW_PED_RED | EW_PED_GREEN);
	}
      
      	//NS: RED | EW: RED
        // which will set D13 and D10 to HIGH
      	PORTB = NS_RED | EW_RED; // 32 + 4 = 36 (0b00100100)
        delay_ms(RED_DURATION);
      
      	//NS: RED & YELLOW | EW: RED
        // which will set D13, D12 and D10 to HIGH
      	PORTB = NS_RED | NS_YELLOW | EW_RED; // 32 + 16 + 4 = 52 (0b00110100)
      	delay_ms(YELLOW_DURATION);
      
      	//NS: GREEN | EW: RED
        // which will set D13 and D8 to HIGH
      	PORTB = NS_GREEN | EW_RED; // 32 + 8 = 40 (0b00101000)
        delay_ms(GREEN_DURATION);
      
      	//NS: GREEN & YELLOW | EW: RED
        // which will set D13, D12 and D10 to HIGH
      	PORTB = NS_GREEN | NS_YELLOW | EW_RED; // 32 + 16 + 8 = 56 (0b00111000)
        delay_ms(YELLOW_DURATION);
      
      	//NS: RED | EW: RED (OVERLAP DURATION)
        // which will set D13 and D10 to HIGH
      	PORTB = NS_RED | EW_RED; // 32 + 4 = 36 (0b00100100)
      	delay_ms(RED_OVERLAP_DURATION);
      
      	//NS: RED | EW: RED & YELLOW
        // which will set D13, D12 and D10 to HIGH
      	PORTB = NS_RED | EW_RED | EW_YELLOW; // 32 + 4 + 2 = 38 (0b00100110)
      	delay_ms(YELLOW_DURATION);
      
      	//NS: RED | EW: GREEN
        // which will set D13 and D8 to HIGH
      	PORTB = NS_RED | EW_GREEN; // 32 + 1 = 33 (0b00100001)
      	delay_ms(GREEN_DURATION);
      
      	//NS: RED | EW: GREEN & YELLOW // which will set D13, D12 and D10 to HIGH
      	PORTB = NS_RED | EW_GREEN | EW_YELLOW; // 32 + 1 + 2 = 35 (0b00100011)
      	delay_ms(YELLOW_DURATION);
      
    }
}
